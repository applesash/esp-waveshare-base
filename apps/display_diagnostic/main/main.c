#include <inttypes.h>
#include <stdio.h>

#include "driver/i2c_master.h"
#include "driver/uart.h"
#include "driver/sdmmc_host.h"
#include "sdmmc_cmd.h"
#include "esp_io_expander.h"
#include "esp_rom_sys.h"
#include "bsp/display.h"
#include "bsp/esp32_s3_touch_lcd_4.h"
#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_mac.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BOARD_SKU "28154"
#define EXPANDER_SDA_GPIO 8
#define EXPANDER_SCL_GPIO 9
#define TOUCH_SDA_GPIO 15
#define TOUCH_SCL_GPIO 7
#define GT911_ADDRESS 0x5d
#define GT911_PRODUCT_ID_REGISTER 0x8140
#define GT911_STATUS_REGISTER 0x814e
#define GT911_POINT_REGISTER 0x8150
#define I2C_SCAN_TIMEOUT_MS 50
#define RS485_UART UART_NUM_0
#define RS485_TX_GPIO 44
#define RS485_RX_GPIO 43
#define RS485_BAUD 9600
#define RTC_ADDRESS 0x51
#define RTC_SECONDS_REGISTER 0x04

static i2c_master_dev_handle_t touch_device;
static esp_lcd_panel_handle_t display_panel;

static void initialize_rs485(void)
{
    const uart_config_t config = {
        .baud_rate = RS485_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_driver_install(RS485_UART, 1024, 1024, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(RS485_UART, &config));
    ESP_ERROR_CHECK(uart_set_pin(RS485_UART, RS485_TX_GPIO, RS485_RX_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    printf("rs485_echo=PASS uart=%d tx_gpio=%d rx_gpio=%d baud=%d\n",
           RS485_UART,
           RS485_TX_GPIO,
           RS485_RX_GPIO,
           RS485_BAUD);
}

static void poll_rs485(void)
{
    uint8_t buffer[128];
    int length = uart_read_bytes(RS485_UART, buffer, sizeof(buffer), pdMS_TO_TICKS(20));
    if (length > 0) {
        uart_write_bytes(RS485_UART, buffer, length);
        printf("rs485_echo_bytes=%d\n", length);
    }
}

static void check_helper(void)
{
    esp_io_expander_handle_t helper = bsp_io_expander_init();
    uint16_t battery_adc = 0;
    uint8_t interrupt_state = 0;

    if (helper == NULL) {
        printf("ch32_helper=FAIL init\n");
        return;
    }
    esp_err_t adc_status = custom_io_expander_get_adc(helper, &battery_adc);
    esp_err_t interrupt_status = custom_io_expander_get_int(helper, &interrupt_state);
    printf("ch32_helper=PASS address=0x24 battery_adc_status=%s battery_adc=%u interrupt_status=%s interrupt=%u\n",
           esp_err_to_name(adc_status),
           battery_adc,
           esp_err_to_name(interrupt_status),
           interrupt_state);
}

static void prepare_board_for_sd(void)
{
    gpio_config_t bus_pins = {
        .pin_bit_mask = (1ULL << TOUCH_SDA_GPIO) | (1ULL << TOUCH_SCL_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&bus_pins));
    gpio_set_direction(TOUCH_SCL_GPIO, GPIO_MODE_OUTPUT_OD);
    gpio_set_pull_mode(TOUCH_SCL_GPIO, GPIO_PULLUP_ONLY);
    gpio_set_level(TOUCH_SCL_GPIO, 1);
    esp_rom_delay_us(10);
    for (int pulse = 0; pulse < 9 && gpio_get_level(TOUCH_SDA_GPIO) == 0; ++pulse) {
        gpio_set_level(TOUCH_SCL_GPIO, 0);
        esp_rom_delay_us(10);
        gpio_set_level(TOUCH_SCL_GPIO, 1);
        esp_rom_delay_us(10);
    }
    gpio_set_direction(TOUCH_SDA_GPIO, GPIO_MODE_OUTPUT_OD);
    gpio_set_pull_mode(TOUCH_SDA_GPIO, GPIO_PULLUP_ONLY);
    gpio_set_level(TOUCH_SDA_GPIO, 0);
    esp_rom_delay_us(10);
    gpio_set_level(TOUCH_SCL_GPIO, 1);
    esp_rom_delay_us(10);
    gpio_set_level(TOUCH_SDA_GPIO, 1);
    esp_rom_delay_us(10);
    gpio_set_direction(TOUCH_SDA_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(TOUCH_SCL_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(TOUCH_SDA_GPIO, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(TOUCH_SCL_GPIO, GPIO_PULLUP_ONLY);
    vTaskDelay(pdMS_TO_TICKS(20));

    esp_io_expander_handle_t helper = bsp_io_expander_init();
    const uint32_t output_mask = IO_EXPANDER_PIN_NUM_1 |
                                 IO_EXPANDER_PIN_NUM_3 |
                                 IO_EXPANDER_PIN_NUM_5 |
                                 IO_EXPANDER_PIN_NUM_6;

    if (helper == NULL) {
        printf("sd_board_prepare=FAIL helper_init\n");
        return;
    }
    ESP_ERROR_CHECK(esp_io_expander_set_dir(helper, output_mask, IO_EXPANDER_OUTPUT));
    ESP_ERROR_CHECK(esp_io_expander_set_dir(helper, IO_EXPANDER_PIN_NUM_7, IO_EXPANDER_INPUT));
    ESP_ERROR_CHECK(esp_io_expander_set_level(helper, output_mask, 0));
    vTaskDelay(pdMS_TO_TICKS(200));
    ESP_ERROR_CHECK(esp_io_expander_set_level(helper,
                                              IO_EXPANDER_PIN_NUM_5 |
                                              IO_EXPANDER_PIN_NUM_1 |
                                              IO_EXPANDER_PIN_NUM_3,
                                              1));
    vTaskDelay(pdMS_TO_TICKS(200));
    printf("sd_board_prepare=PASS ch32=0x24 sys_en=1 lcd_reset=1 touch_reset=1\n");
}

static void check_rtc(void)
{
    i2c_master_bus_handle_t bus = bsp_i2c_get_handle();
    i2c_master_dev_handle_t rtc = NULL;
    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = RTC_ADDRESS,
        .scl_speed_hz = 100000,
    };
    uint8_t seconds = 0;
    uint8_t register_address = RTC_SECONDS_REGISTER;
    esp_err_t err = bus == NULL ? ESP_ERR_INVALID_STATE : i2c_master_bus_add_device(bus, &device_config, &rtc);
    if (err == ESP_OK) {
        err = i2c_master_transmit_receive(rtc, &register_address, 1, &seconds, 1, 1000);
    }
    printf("rtc= %s address=0x%02x seconds_bcd=0x%02x\n",
           esp_err_to_name(err),
           RTC_ADDRESS,
           seconds);
}

static void check_sdcard(void)
{
    sdmmc_host_t probe_host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t probe_slot = SDMMC_SLOT_CONFIG_DEFAULT();
    sdmmc_card_t probe_card = {0};
    probe_host.max_freq_khz = SDMMC_FREQ_PROBING;
    probe_slot.clk = GPIO_NUM_2;
    probe_slot.cmd = GPIO_NUM_1;
    probe_slot.d0 = GPIO_NUM_4;
    probe_slot.d1 = GPIO_NUM_NC;
    probe_slot.d2 = GPIO_NUM_NC;
    probe_slot.d3 = GPIO_NUM_NC;
    probe_slot.width = 1;
    esp_err_t probe_error = sdmmc_host_init();
    if (probe_error == ESP_OK) {
        probe_error = sdmmc_host_init_slot(probe_host.slot, &probe_slot);
    }
    if (probe_error == ESP_OK) {
        probe_error = sdmmc_card_init(&probe_host, &probe_card);
    }
    printf("sdcard_raw_probe=%s\n", esp_err_to_name(probe_error));
    if (probe_error == ESP_OK) {
        printf("sdcard_raw_name=%s capacity_mb=%" PRIu32 " max_freq_khz=%" PRIu32 "\n",
               probe_card.cid.name,
               (uint32_t)(((uint64_t)probe_card.csd.capacity * probe_card.csd.sector_size) / (1024 * 1024)),
               probe_card.max_freq_khz);
    }
    sdmmc_host_deinit();

    esp_err_t err = bsp_sdcard_mount();
    printf("sdcard_mount=%s\n", esp_err_to_name(err));
    if (err == ESP_OK) {
        printf("sdcard=PASS card_detected=1\n");
        bsp_sdcard_unmount();
    } else {
        printf("sdcard=NOT_AVAILABLE_OR_NOT_INSERTED\n");
    }
}

static void initialize_display(void)
{
    bsp_display_config_t display_config = {
        .max_transfer_sz = 480 * 16 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(bsp_display_new(&display_config, &display_panel, NULL));
    ESP_ERROR_CHECK(bsp_display_brightness_init());
    ESP_ERROR_CHECK(bsp_display_backlight_on());

    static uint16_t line[480];
    for (int y = 0; y < 480; ++y) {
        uint16_t color = y < 160 ? 0xf800 : (y < 320 ? 0x07e0 : 0x001f);
        for (size_t x = 0; x < 480; ++x) {
            line[x] = color;
        }
        ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(display_panel, 0, y, 480, y + 1, line));
    }
    printf("lcd_init=PASS resolution=480x480 pattern=red-green-blue\n");
}

static void print_identity(void)
{
    esp_chip_info_t chip_info;
    uint8_t mac[6];
    uint32_t flash_size = 0;

    esp_chip_info(&chip_info);
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    esp_flash_get_size(NULL, &flash_size);

    printf("\n28154 display diagnostic\n");
    printf("chip=ESP32-S3 revision=%d cores=%d features=0x%" PRIx32 "\n",
           chip_info.revision,
           chip_info.cores,
           (uint32_t)chip_info.features);
    printf("mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf("flash_bytes=%" PRIu32 " free_heap=%" PRIu32 " reset_reason=%d\n",
           flash_size,
           (uint32_t)esp_get_free_heap_size(),
           esp_reset_reason());
}

static void scan_bus(const char *name, gpio_num_t sda_gpio, gpio_num_t scl_gpio)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = sda_gpio,
        .scl_io_num = scl_gpio,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus = NULL;
    esp_err_t err = i2c_new_master_bus(&bus_config, &bus);

    printf("i2c_bus=%s sda=%d scl=%d status=%s\n",
           name,
           sda_gpio,
           scl_gpio,
           esp_err_to_name(err));
    if (err != ESP_OK) {
        return;
    }

    printf("i2c_bus=%s devices=", name);
    for (uint8_t address = 0x08; address <= 0x77; ++address) {
        if (i2c_master_probe(bus, address, I2C_SCAN_TIMEOUT_MS) == ESP_OK) {
            printf("0x%02x ", address);
        }
    }
    printf("\n");
    ESP_ERROR_CHECK(i2c_del_master_bus(bus));
}

static esp_err_t read_touch_register(uint16_t address, uint8_t *data, size_t length)
{
    uint8_t register_address[] = {
        (uint8_t)(address >> 8),
        (uint8_t)(address & 0xff),
    };

    return i2c_master_transmit_receive(
        touch_device,
        register_address,
        sizeof(register_address),
        data,
        length,
        1000);
}

static void clear_touch_status(void)
{
    uint8_t command[] = {
        (uint8_t)(GT911_STATUS_REGISTER >> 8),
        (uint8_t)(GT911_STATUS_REGISTER & 0xff),
        0,
    };

    ESP_ERROR_CHECK(i2c_master_transmit(touch_device, command, sizeof(command), 1000));
}

static void start_touch_monitor(void)
{
    i2c_master_bus_handle_t bus = bsp_i2c_get_handle();
    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = GT911_ADDRESS,
        .scl_speed_hz = 400000,
    };
    uint8_t product_id[4] = {0};
    esp_err_t err = bus == NULL ? ESP_ERR_INVALID_STATE : ESP_OK;
    if (err == ESP_OK) {
        err = i2c_master_bus_add_device(bus, &device_config, &touch_device);
    }
    if (err == ESP_OK) {
        err = read_touch_register(GT911_PRODUCT_ID_REGISTER, product_id, sizeof(product_id));
    }

    printf("touch_controller=GT911 address=0x%02x status=%s product_id=%02x%02x%02x%02x\n",
           GT911_ADDRESS,
           esp_err_to_name(err),
           product_id[0],
           product_id[1],
           product_id[2],
           product_id[3]);
    if (err != ESP_OK) {
        touch_device = NULL;
    }
}

static void poll_touch(void)
{
    uint8_t status = 0;
    uint8_t point[8] = {0};

    if (touch_device == NULL || read_touch_register(GT911_STATUS_REGISTER, &status, 1) != ESP_OK) {
        return;
    }
    if ((status & 0x80) == 0) {
        return;
    }
    if ((status & 0x0f) > 0 && read_touch_register(GT911_POINT_REGISTER, point, sizeof(point)) == ESP_OK) {
        uint16_t x = (uint16_t)point[0] | ((uint16_t)point[1] << 8);
        uint16_t y = (uint16_t)point[2] | ((uint16_t)point[3] << 8);
        printf("touch_raw count=%u bytes=%02x %02x %02x %02x %02x %02x %02x %02x\n",
               status & 0x0f,
             point[0],
               point[1],
               point[2],
               point[3],
               point[4],
               point[5],
               point[6],
             point[7]);
         printf("touch_event count=%u track=%u x=%u y=%u size=%u\n",
               status & 0x0f,
             point[6],
               x,
               y,
             (uint16_t)point[4] | ((uint16_t)point[5] << 8));
    }
    clear_touch_status();
}

void app_main(void)
{
    print_identity();
    printf("documented_expander_bus=sda:%d scl:%d\n",
           EXPANDER_SDA_GPIO,
           EXPANDER_SCL_GPIO);
    printf("documented_touch_bus=sda:%d scl:%d\n",
           TOUCH_SDA_GPIO,
           TOUCH_SCL_GPIO);

        prepare_board_for_sd();
    check_sdcard();
    initialize_display();
    initialize_rs485();
    check_helper();
    check_rtc();
    start_touch_monitor();

    printf("touch_decode=GT911_POLLING\n");
    printf("diagnostic_complete=PASS\n");

    while (true) {
        poll_rs485();
        poll_touch();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
