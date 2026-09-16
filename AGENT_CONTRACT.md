# Industrial HMI and Automation Platform
# AGENT CONTRACT

**Document ID:** IHAP-AGENT-CONTRACT  
**Version:** 3.1.0  
**Status:** Authoritative Baseline  
**Owner:** Sascha Hlubek  
**ESP-IDF baseline:** 5.5.5  
**Target:** esp32s3

## 0. Contract authority and terminology

### RS-GOV-001
This repository shall be developed as one reusable Industrial HMI and Automation Platform, not as three unrelated firmware projects.

### RS-GOV-002
The words **shall** and **must** are mandatory. **Should** is a recommendation. **May** is optional.

### RS-GOV-003
Contract changes require a requirement change, an ADR, a contract version update, traceability update, and changelog entry.

### RS-GOV-004
The agent shall maintain a Requirements Traceability Matrix covering requirements, implementation, tests, boards, status, and evidence.

### RS-GOV-005
The agent shall prefer reuse, abstraction, portability, simulation, shared workflows, shared data models, and small focused changes.

### RS-GOV-006
Duplicate services, workflows, view models, business rules, or screen definitions are prohibited.

### RS-GOV-007
The agent shall not advance past a mandatory phase gate until its acceptance criteria pass and evidence is recorded.

### RS-GOV-008
Source modules shall identify the requirement IDs they implement in `REQUIREMENTS.md` or source-header comments.

## 1. Supported hardware

### RS-HW-001
The authoritative initial devices are:

1. Waveshare ESP32-S3-Touch-LCD-4, SKU 28154.
2. Waveshare ESP32-S3-Touch-LCD-4.3B-BOX, SKU 28141.
3. Waveshare ESP32-S3 WiFi 8CH Relay Module RS485, SKU 30838.

### RS-HW-002
Capabilities shall be derived and verified for each exact SKU. No capability, GPIO, expander channel, bus assignment, timing value, reset sequence, or safe state may be copied from a different SKU merely because the boards look similar.

### RS-HW-003
Every board shall have a capability manifest with status values: `NOT_PRESENT`, `UNVERIFIED`, `VERIFIED`, `IMPLEMENTED`, and `PHYSICALLY_TESTED`.

### RS-HW-004
Every device shall expose device name, device ID, serial number, hardware revision, firmware version, platform version, application version, and Git commit.

### RS-HW-005
Hardware validation evidence shall be stored under `docs/devices/<sku>/evidence/`.

### RS-HW-006
A GPIO or peripheral mapping is not `VERIFIED` until its exact source is identified. It is not `PHYSICALLY_TESTED` until a test has run on that exact SKU and evidence is recorded.

### RS-HW-007
Before a hardware phase can close, each supported SKU shall have a source-backed peripheral inventory covering display, touch, I2C, RS485, CAN/TWAI, storage, RTC, audio/buzzer, backlight, power/battery, network, USB, GPIO/helper channels, and explicitly not-present blocks. The inventory check shall be run with `scripts/hardware/check-peripheral-inventory.sh <SKU>`.

## 2. Approved sources and prohibited source use

### RS-SRC-001
Approved factual hardware sources, in order of authority, are:

1. Official Waveshare documentation for the exact SKU and revision.
2. Official schematic for the exact SKU and revision.
3. Official Waveshare example package for the exact SKU.
4. Official component and panel manufacturer data sheets.
5. Official Espressif documentation and components.

### RS-SRC-002
Official example code may be inspected only to extract hardware facts such as GPIO assignments, timing, I2C addresses, power sequencing, reset sequencing, expander mapping, and peripheral enable logic. Its architecture shall not be copied automatically.

### RS-SRC-003
The agent shall not use Arduino, `Arduino.h`, `Wire.h`, TFT_eSPI, LovyanGFX, `lvgl_esp32_drivers`, unofficial GT911 drivers, random forum code, code for another SKU, or untraceable generated values.

### RS-SRC-004
Every hardware fact shall be recorded in `SOURCE_REGISTER.md` and `GPIO_REGISTER.md` with source, revision, page/line/macro, verification date, and status.

### RS-SRC-005
When official sources disagree, the agent shall document the discrepancy, create an ADR, test the exact hardware, and use the physically proven result. It shall not silently choose one value.

## 3. Workspace and toolchain

### RS-WORK-001
Before code generation, the agent shall validate Git, GitHub CLI, Python, ESP-IDF 5.5.5, CMake, Ninja, the ESP32-S3 toolchain, serial-port access, and required USB drivers.

### RS-WORK-002
The approved target is `esp32s3`. The approved initial SDK baseline is ESP-IDF 5.5.5. Upgrades require an ADR and explicit authorization.

### RS-WORK-003
Workspace paths shall contain no spaces. Build, flash, test, and deployment scripts shall stop on failed mandatory checks.

### RS-WORK-004
The agent shall reuse a valid installed environment and cached dependencies. It shall not repeatedly reinstall working tools.

### RS-WORK-005
Exact managed-component versions shall be locked after the combination compiles and passes applicable hardware tests. Unverified versions shall be marked `UNRESOLVED`, not guessed.

## 4. Repository ownership and layered architecture

### RS-ARCH-001
The dependency direction shall be:

`Applications -> UI composition/ViewModels -> Application Services -> Runtime/Domain Services -> Provider Interfaces -> Hardware or Simulation Providers -> BSP -> ESP-IDF`

### RS-ARCH-002
Operational or business logic is prohibited in GUI controls, screen definitions, renderers, BSPs, and hardware drivers.

### RS-ARCH-003
UI may display data, collect input, validate presentation constraints, and raise commands. Application/domain services shall perform operations and decisions.

### RS-ARCH-004
Hardware access shall occur only in hardware providers and BSP/driver code. Applications shall not directly access GPIO, UART, RS485, CAN, I2C, LVGL, HTML, NVS, FATFS, or SD-card files.

### RS-ARCH-005
The BSP shall only expose hardware, map pins/expanders, initialize hardware, define safe states, and describe capabilities. It shall contain no UI, tag, alarm, workflow, or business logic.

### RS-ARCH-006
Applications may contain application-specific screen composition, workflow composition, configuration, and business rules. They shall not contain reusable infrastructure, shared workflows, common controls, drivers, or providers.

### RS-RUNTIME-001
`platform_runtime` shall coordinate lifecycle, module and service registration, event bus, tag registry, alarm engine, scheduler, and diagnostics collection.

## 5. Shared UI and browser-first development

### RS-UI-001
There shall be one authoritative screen model, ViewModel, workflow, navigation model, permission model, validation model, and theme for each feature.

### RS-UI-002
The platform shall provide LVGL, embedded Web, and local browser-preview renderers.

### RS-UI-003
Web and device UI shall have equivalent information, state, actions, validation, permissions, and workflow. Pixel identity is not required; responsive layout differences are permitted.

### RS-UI-004
The local Web preview is the primary design and simulation environment and shall be startable by script without flashing hardware.

### RS-UI-005
Renderers may contain platform-specific rendering only. They shall not contain business logic or fork workflows.

### RS-UI-006
New UI functionality shall first be designed as a reusable, parameterized component that works on every capable device and all applicable renderers.

### RS-UI-007
Direct LVGL calls outside `renderer_lvgl` and direct HTML/DOM implementation outside `renderer_web` are prohibited.

### RS-UI-008
Minimum common navigation is Overview, Diagnostics, Logging/Trends, Settings, and Application. Unsupported sections shall be capability-aware without changing shared workflow definitions.

### RS-UI-009
User operations shall expose `idle`, `running`, `success`, `failed`, and where applicable `cancelled` states.

### RS-UI-010
Displayed text shall use localization keys rather than hard-coded application strings, except diagnostic/developer-only output explicitly marked non-localized.

## 6. Domain objects, tags, events, and providers

### RS-DATA-001
Core objects shall include Tag, Measurement, Alarm, AuditRecord, NetworkStatus, TimeStatus, StorageStatus, DeviceStatus, RelayState, DigitalInputState, DigitalOutputState, TrendQuery, SettingDefinition, SettingValue, and UserSession.

### RS-TAG-001
Process and platform data points shall be represented as typed Tags with ID, value, data type, units, timestamp, quality, description, limits, logging policy, and read-only state.

### RS-TAG-002
Quality shall include `GOOD`, `BAD`, `UNCERTAIN`, `DISCONNECTED`, `SIMULATED`, and `UNKNOWN`.

### RS-EVT-001
Cross-component communication shall use typed commands and events. Direct component coupling is prohibited.

### RS-EVT-002
Events shall include network, time, settings, alarm, OTA, relay, DIO, storage, and lifecycle changes as applicable.

### RS-PROV-001
Every external capability shall define a provider interface. Hardware-dependent providers shall have simulation equivalents wherever practical.

### RS-PROV-002
Replacing a simulator with hardware shall not require changes to the screen model, ViewModel, workflow, or domain service.

## 7. Initial Hello World acceptance application

### RS-HELLO-001
One shared acceptance application shall show `Hello World`, an `Increment` button, and `Count: 0`.

### RS-HELLO-002
Activating the button shall increment the shared counter state.

### RS-HELLO-003
SKU 28154 and SKU 28141 shall render the same model through LVGL and Web. SKU 30838 shall render it through Web only. Local preview shall use the same model and workflow.

### RS-HELLO-004
The counter domain object, service, ViewModel, components, workflow, and tests shall exist once.

## 8. Display and touch bring-up

### RS-DISP-001
Display GPIOs and RGB timing shall be extracted only from approved exact-SKU sources and recorded before display driver implementation.

### RS-DISP-002
Display bring-up order is power/enable, backlight, RGB colour bars, static label, LVGL renderer, and shared application.

### RS-TOUCH-001
GT911 shall be brought up independently of LVGL using Espressif's `esp_lcd_touch_gt911` managed component and the applicable ESP-IDF 5.5 I2C master API.

### RS-TOUCH-002
Mandatory touch sequence is power/enable validation, I2C initialization, bus scan, expected-address confirmation, GT911 initialization, raw polling, coordinate logging, press/release validation, range validation, transform validation, LVGL input adapter, and button acceptance.

### RS-TOUCH-003
I2C acknowledgement alone is not proof of working touch.

### RS-TOUCH-004
Touch acceptance requires stable full-screen coordinates, correct press/release, correct transform, valid button activation, no phantom presses, no repeated I2C errors, and no LVGL threading violations.

### RS-TOUCH-005
Permanent `display_diagnostic` and `touch_diagnostic` applications shall remain in the repository.

## 9. Networking and provisioning

### RS-NET-001
All three devices shall support WiFi station, access-point, and AP+STA modes where supported by the selected ESP-IDF configuration.

### RS-NET-002
When no valid station configuration exists, the device shall offer provisioning through a SoftAP and local setup Web UI. Touch devices shall also expose the same setup workflow on-device.

### RS-NET-003
Provisioning workflow is scan, select SSID, enter credentials, attempt connection, report result, and save only upon successful policy-compliant completion.

### RS-NET-004
WiFi credentials shall never be logged or displayed after entry and shall use protected persistent storage appropriate to the build's security configuration.

### RS-NET-005
NetworkStatus shall identify mode, connected SSID when in station mode, provided AP SSID when in AP mode, address information for each active interface, RSSI/channel where applicable, gateway, DNS, internet reachability, and Web/OTA service state.

## 10. Settings and authentication

### RS-SET-001
Settings shall be schema-driven with ID, description, type, default, validation, permissions, schema version, and migration rules.

### RS-SET-002
Configuration shall support validated JSON export, import, backup, and restore without exporting secret values in plaintext.

### RS-AUTH-001
Authentication shall be centralized in `platform_auth` and shared by LVGL, Web, and preview workflows.

### RS-AUTH-002
The initial commissioning password is `12345`. It is for development and commissioning only.

### RS-AUTH-003
Production access to protected configuration shall require replacement of the commissioning password. The system shall visibly warn while it is active.

### RS-AUTH-004
Passwords shall never be stored in plaintext. Use a cryptographically suitable salted password derivation/hash supported by the approved platform design and document parameters in the security ADR without storing the secret.

### RS-AUTH-005
Protected settings include network, password, OTA, logging, alarm, time, and system configuration.

### RS-AUTH-006
Initial roles are User, Engineer, and Administrator, with permissions defined in the settings/auth schema.

### RS-AUTH-007
Login success/failure, logout, and password change shall produce rate-limited audit records without logging credentials.

### RS-AUTH-008
Development builds may permit continued commissioning-password use with a visible warning. Production builds shall block protected operation until replacement.

## 11. Build modes and security

### RS-BUILD-001
Supported modes are Development and Production and shall be mutually exclusive.

### RS-BUILD-002
Development mode may enable simulators, verbose diagnostics, development OTA policy, and commissioning-password use.

### RS-BUILD-003
Production mode shall require password replacement, firmware authenticity checks, rollback, audit logging, reduced debug exposure, and reviewed security configuration.

### RS-SEC-001
Credentials, tokens, private keys, WiFi passwords, and administrator passwords shall not appear in source, Git history, documentation, command arguments, screenshots, logs, fixtures, or chat.

### RS-SEC-002
Interactive credentials may be entered only into trusted OS, browser, GitHub CLI, identity-provider, or approved credential-manager prompts.

### RS-SEC-003
Signing private keys shall not be stored in the repository. Public verification material may be stored when required by the approved design.

## 12. Time and scheduler

### RS-TIME-001
All devices shall maintain UTC internally and convert to configured local time only for presentation and local schedule interpretation.

### RS-TIME-002
SNTP/NTP shall be the normal online source. RTC-capable boards may provide fallback/holdover. Manual time, if supported, shall be explicitly identified as the source.

### RS-TIME-003
Default configurable servers are `ie.pool.ntp.org`, `europe.pool.ntp.org`, and `pool.ntp.org`. Default timezone is `Europe/Dublin` unless deployment configuration states otherwise.

### RS-TIME-004
Time settings shall include enablement, primary/secondary/fallback servers, timezone, and synchronization interval.

### RS-TIME-005
TimeStatus shall contain UTC, local time, timezone, source, active server, synchronization state, last successful sync, next planned sync, and error status.

### RS-SCHED-001
`platform_scheduler` shall provide periodic, daily, weekly, and documented cron-style schedules and shall use monotonic timing for elapsed intervals.

### RS-SCHED-002
Scattered unmanaged timers are prohibited. Timer/schedule ownership and callback execution context shall be documented.

## 13. Diagnostics

### RS-DIAG-001
Every device shall expose one shared Diagnostics model rendered by each applicable renderer.

### RS-DIAG-002
System diagnostics shall include identity, versions, build mode, build date/time, Git commit, uptime, restart count, last reset reason, heap, PSRAM where present, largest free block, task count, and health states.

### RS-DIAG-003
Network diagnostics shall show active mode, connected or provided SSID as applicable, addresses in each active mode, RSSI/channel where applicable, gateway, DNS, internet reachability, and service states.

### RS-DIAG-004
Time diagnostics shall show UTC, local time, timezone, source, server, sync status, last sync, next sync, and internet-time availability.

### RS-DIAG-005
Storage diagnostics shall show SD presence, media size, used/free capacity, last successful write, and write-error status.

### RS-DIAG-006
I/O diagnostics shall be capability-aware and show display, touch, RTC, RS485, CAN, digital input, digital output, and relay health where present.

### RS-DIAG-007
Task diagnostics shall expose task name, state, stack watermark, and CPU/runtime information where supported by the configured build.

### RS-DIAG-008
Security diagnostics shall show build mode and whether the commissioning password remains active, without disclosing secrets.

## 14. Alarms and audit

### RS-ALARM-001
`platform_alarms` shall evaluate alarm conditions outside UI from tags, measurements, device health, communication state, and application services.

### RS-ALARM-002
Alarm severities are Information, Warning, Error, and Critical. Lifecycle states are New, Active, Acknowledged, Cleared, and Shelved where shelving is enabled.

### RS-ALARM-003
Alarm objects shall contain stable ID, source, severity, message key/parameters, activation/clear/acknowledgement timestamps, state, and quality context.

### RS-ALARM-004
Diagnostics shall contain a reusable dynamic active-alarm panel. When empty, it shall display `No Active Alarms`.

### RS-ALARM-005
A shared alarm-history view shall support filtering, searching, and export subject to permissions and storage availability.

### RS-ALARM-006
Generic platform alarms shall cover applicable network, time, storage, memory, OTA, bus, relay, and device-health failures without generating nuisance alarms during intentional commissioning states.

### RS-AUDIT-001
`platform_audit` shall record security-relevant and operator-initiated changes, including login events, password changes, settings changes, OTA operations, relay overrides, and alarm acknowledgements/shelving.

### RS-AUDIT-002
Audit records shall be append-oriented, timestamped, attributable where a user session exists, viewable through authorized UI, and exportable.

## 15. Storage, logging, historian, and trends

### RS-STOR-001
Configuration, OTA metadata/images, application storage, logs, historian data, exports, and backups shall have defined ownership and separation.

### RS-STOR-002
The partition design shall include NVS, OTA metadata, A/B application slots, and storage as sizing permits. Exact sizes shall be defined per exact board flash capacity and validated before use.

### RS-STOR-003
Settings shall be schema-versioned, migration-capable, validated before activation, and written using a power-loss-tolerant strategy.

### RS-LOG-001
Applications shall register data points and logging policies rather than writing files directly.

### RS-LOG-002
Each logging policy shall define selected tags, interval, change/deadband behavior where supported, retention, and enablement.

### RS-LOG-003
Initial standard intervals include 1 s, 5 s, 10 s, 30 s, 1 min, 5 min, 15 min, and 1 hour, while the domain model shall support validated configurable intervals.

### RS-LOG-004
Initial export/interchange support shall include CSV. The backend interface shall permit a future embedded database without UI or application changes.

### RS-LOG-005
Retention shall support age-based, size-based, and circular policies. Unlimited retention shall be permitted only with a documented full-storage behavior.

### RS-LOG-006
Logging shall use bounded queues, backpressure/error reporting, buffered writes, file rotation, and recovery after missing or remounted SD media.

### RS-TREND-001
Trend ViewModels shall query historian services only. Direct file or SD access from UI is prohibited.

### RS-TREND-002
The shared trend component shall support series selection, time-range selection, pan backward/forward, zoom in/out, live mode, and export.

### RS-TREND-003
Trend behavior and state shall remain equivalent across Web, preview, and capable LVGL devices, with renderer-appropriate performance limits.

## 16. OTA

### RS-OTA-001
All devices shall support A/B OTA where validated partition sizing permits it. The running slot shall not be overwritten.

### RS-OTA-002
New firmware shall remain pending until explicit startup validation succeeds. Failure to validate shall trigger rollback to the previously valid image.

### RS-OTA-003
Startup validation shall confirm essential runtime/services, required storage policy, network-independent core startup, and applicable UI/provider readiness before marking the image valid.

### RS-OTA-004
All images shall be checked for completeness and integrity. Production images shall require authenticity verification using the approved ESP-IDF security design.

### RS-OTA-005
Development builds may permit unsigned development images only under explicit development policy. Production builds shall reject images that fail authenticity policy.

### RS-OTA-006
Supported delivery methods are authenticated HTTPS download and authorized local Web upload. Future providers shall use the same OTA service interface.

### RS-OTA-007
OTA status/history, current/previous version, last result/time, pending state, and rollback count shall be available in Diagnostics. OTA configuration shall be protected.

### RS-OTA-008
OTA operations shall create events and audit records without exposing secrets.

## 17. Relays, DIO, RS485, CAN, RTC, and buses

### RS-IO-001
Shared service/provider interfaces shall exist for relay, digital I/O, RS485, CAN, RTC, and external I2C capabilities.

### RS-IO-002
All outputs shall initialize to board-documented safe states. Energizing hardware tests shall require explicit interactive acknowledgement.

### RS-IO-003
Each bus/provider shall define timeout, retry policy, recovery action, health state, counters, and alarm criteria.

### RS-IO-004
The SKU 30838 architecture shall include all verified digital inputs, digital outputs/relay outputs, RS485, SD, WiFi, and other exact-SKU capabilities, not merely its eight relays.

### RS-IO-005
SKU 28154 and SKU 28141 shall expose all verified peripherals through capabilities and providers, not only display and touch.

## 18. Reliability, memory, and concurrency

### RS-REL-001
Each board shall define flash, internal heap, PSRAM, task-stack, framebuffer, Web asset, and storage budgets.

### RS-REL-002
Long-running tasks shall document ownership, priority, core affinity if used, stack budget, queue limits, watchdog behavior, and shutdown/recovery behavior.

### RS-REL-003
LVGL access shall occur only from the designated LVGL task or through the approved locking/dispatch mechanism.

### RS-REL-004
Watchdog, brownout, panic, and reset reasons shall be retained where feasible, exposed to Diagnostics, and converted to alarm/audit events where appropriate.

### RS-REL-005
SD absence shall not prevent core startup unless the application safety policy explicitly requires historian availability.

### RS-REL-006
A recovery mode shall support invalid settings, unusable network configuration, failed OTA, and critical startup faults.

### RS-REL-007
Shared libraries shall be thread-safe or explicitly declare single-task ownership.

## 19. Scripts, USB flashing, GitHub, and CI

### RS-SCRIPT-001
Idempotent scripts shall cover workspace check/setup, configure, build, clean, flash, monitor, test, preview, package, release, GitHub login, remote validation, and repository initialization.

### RS-SCRIPT-002
Scripts shall validate prerequisites, identify board/port/build mode, fail with non-zero status, avoid silent fallback, write concise logs, and never echo secrets.

### RS-FLASH-001
Firmware shall be built and flashed using official ESP-IDF tooling. Scripts shall enumerate serial ports, allow selection, validate board/target/mode, build before flashing unless explicitly bypassed, and optionally start monitor.

### RS-FLASH-002
Scripts shall never collect OS administrator credentials. If driver installation/elevation is required, the user shall complete the trusted OS prompt directly.

### RS-FLASH-003
BOOT/RESET physical actions shall be clearly prompted when required.

### RS-GIT-001
Git operations shall use HTTPS, not SSH, unless the owner changes policy through an ADR.

### RS-GIT-002
Authentication shall use interactive `gh auth login` browser/device flow. The script shall first check `gh auth status`. The agent shall prompt the owner to complete trusted login but shall not request passwords, tokens, one-time codes, or MFA responses in chat.

### RS-GIT-003
Company-managed repository creation, visibility, access, branch protection, actions, and secrets shall follow applicable organizational policy. The agent shall not create a public repository for company code.

### RS-CI-001
CI shall validate the contract, formatting/static checks, host tests, simulation tests, renderer contracts, and a Development/Production build matrix for all three SKUs.

### RS-CI-002
CI shall not flash USB devices unless a separately approved dedicated hardware runner is introduced.

### RS-CI-003
Release artifacts shall identify platform/application version, Git commit, board SKU, build mode, partition checksum, dependency lock, firmware checksum, test state, and traceability report.

## 20. Testing, evidence, phase gates, and definition of done

### RS-TEST-001
Test layers shall include unit, component, service, integration, simulation, renderer-contract, hardware-in-the-loop, OTA rollback, storage-failure, power-cycle, security, and acceptance tests as applicable.

### RS-TEST-002
Renderer-contract tests shall enforce equivalent component IDs, bindings, actions, validation, visibility, navigation, permissions, and workflow transitions.

### RS-TEST-003
Hardware diagnostic tests shall cover serial, display, touch, SD, I2C scan, RS485, CAN, digital input, digital output, relay, RTC, network, and OTA where the capability exists.

### RS-GATE-001
Every phase shall define prerequisites, permitted changes, tests, evidence, exclusions, exit criteria, and next permitted phase.

### RS-GATE-002
A failed mandatory gate stops progression. Compilation alone shall never satisfy physical validation.

### RS-DOD-001
A phase is done only when implementation is complete, required tests pass, documentation and traceability are updated, simulation is verified, physical validation is recorded where applicable, security/reliability checks pass, and no unresolved mandatory defect remains.

## 21. Phase restore points, Git checkpoints, and recovery

### RS-BACKUP-001
Every successfully completed phase shall create a recoverable checkpoint. A phase is not complete until its checkpoint has been committed, tagged, pushed, archived locally, verified, and recorded.

### RS-BACKUP-002
The checkpoint shall include all controlled source, requirements, contract, status, traceability, tests, validation evidence, scripts, manifests, and accepted ADRs applicable to the completed phase.

### RS-BACKUP-003
Local phase snapshots shall be written under `artifacts/phase-snapshots/` and shall not contain credentials, ignored secret files, build caches, or untracked local-only data.

### RS-BACKUP-004
The snapshot filename shall use `phase-XX-complete.zip`. The snapshot shall be generated from the committed, annotated phase tag so its contents match the remote checkpoint exactly.

### RS-GIT-010
Development shall occur on a phase or feature branch. Direct development commits to protected `main` are prohibited. Integration to `main` shall follow repository policy and required review/status checks.

### RS-GIT-011
The canonical phase checkpoint commit message shall use:

`[PHASE-XX] <Phase Name> - Gate Passed`

### RS-GIT-012
The canonical annotated tag shall use `phase-XX-complete`. Tags are immutable restore points and shall not be moved or force-updated.

### RS-GIT-013
The phase branch commit and annotated phase tag shall be pushed to the configured HTTPS remote. Phase closure requires successful remote verification of both commit reachability and tag identity, unless an explicitly documented organizational outage exception is approved by the owner.

### RS-GIT-014
Checkpoint automation shall stop if the working tree contains unresolved conflicts, required tests/evidence are incomplete, the remote is absent, authentication is unavailable, or the intended tag already exists locally or remotely.

### RS-GIT-015
Checkpoint automation shall never use `git push --force`, rewrite published history, move phase tags, bypass branch protections, or suppress failed validations.

### RS-GIT-016
`PROJECT_STATUS.md` and `docs/recovery/RESTORE_POINTS.md` shall be updated with phase, commit, tag, push status, snapshot path/checksum, validation status, and date before the checkpoint commit.

### RS-RECOVERY-001
Before a new phase starts, the agent shall verify the latest completed-phase tag, remote tag, commit, snapshot checksum, phase acceptance report, and validation evidence.

### RS-RECOVERY-002
Recovery shall create a new branch from the selected immutable phase tag. The agent shall not reset or force-update shared branches without explicit owner authorization.

### RS-RECOVERY-003
The preferred recovery order is remote annotated tag, local snapshot generated from that tag, then documented branch recovery. Recovery procedures shall be tested at least once before Production release.

### RS-STARTUP-005
At startup, the agent shall report the latest completed phase, local and remote checkpoint tags, latest successful validation report, and snapshot verification state before modifying files.

### RS-STARTUP-006
Before invoking any repository script, the agent shall detect the host operating system and run the matching script family for that environment. On Linux and macOS, prefer the `.sh` entry points; on Windows, prefer the `.ps1` or `.cmd` entry points. The agent shall not call a script from a different OS family without explicit, documented justification and acceptance.

## 22. ADR, versioning, and migration

### RS-ADR-001
Non-trivial architectural decisions shall use numbered ADRs containing status, context, decision, alternatives, consequences, requirements, and validation.

### RS-VER-001
Platform and applications shall use semantic versioning. Diagnostics shall expose platform, application, firmware/build, and Git versions.

### RS-MIG-001
Persistent schemas shall have explicit versions and forward migration handlers. OTA shall validate migration compatibility before final image acceptance.

## 23. Agent startup and behavior

### RS-AGENT-001
At session start, read in order: this contract, `AGENT_STARTUP.md`, `PROJECT_STATUS.md`, current phase file, applicable board manifest, applicable ADRs, traceability, dependency lock, and latest validation evidence.

### RS-AGENT-002
Before coding, report current phase, target board(s), build mode, requirement IDs, expected files, tests, hardware assumptions, and unverified facts.

### RS-AGENT-003
Inspect existing code first and modify the smallest necessary set of files. Do not regenerate working libraries, projects, screens, or scripts.

### RS-AGENT-004
Do not change ESP-IDF, component versions, partition tables, GPIOs, RGB timing, touch configuration, safety states, or architecture without evidence and an ADR where required.

### RS-AGENT-005
After work, report files changed, requirements implemented, tests run/passed/not run, physical validation outstanding, evidence updated, ADRs, and limitations.

### RS-AGENT-006
Never claim hardware validation without a recorded physical test on the exact SKU.

## 24. Phased implementation roadmap

### PHASE-00 Repository baseline
Create control documents, structure, templates, Git ignore/attributes, and initial traceability. No board code.

### PHASE-01 Workspace validation
Create/run workspace scripts and prove ESP-IDF 5.5.5, toolchain, build tools, Git/GitHub CLI, and serial visibility. Do not reinstall valid tools.

### PHASE-02 Hardware evidence and capability discovery
Acquire approved exact-SKU sources, populate source/GPIO/capability registers, record unknowns, and establish safe states. No guessed drivers.

### PHASE-03 Serial and storage baseline
Build serial Hello World for each SKU, verify flash/monitor, validate board flash/PSRAM configuration, partition sizing, NVS, and SD diagnostic behavior.

### PHASE-04 Display bring-up
For SKUs 28154 and 28141 only: power/backlight, colour bars, timing validation, static label, and evidence.

### PHASE-05 Raw touch bring-up
For SKUs 28154 and 28141 only: GT911 raw test gate independent of LVGL.

### PHASE-06 Shared Hello UI and LVGL
Create counter domain/service/ViewModel/screen once and render through LVGL on both touch devices. Pass button acceptance.

### PHASE-07 Local Web preview
Render the same screen/workflow locally using simulator providers. Establish renderer-contract tests.

### PHASE-08 Three-device Hello acceptance
Deploy embedded Web UI to all three devices; touch devices also use LVGL. Prove shared model/workflow and Web-only behavior on SKU 30838.

### PHASE-09 Network provisioning
Add STA/AP/AP+STA, SoftAP setup, scanning, credential entry/storage, and shared setup workflow.

### PHASE-10 Settings and authentication
Add schemas, protected Settings, commissioning-password lifecycle, roles, password storage, audit, import/export without secrets.

### PHASE-11 Time and scheduler
Add NTP/SNTP, RTC fallback where present, UTC/local conversion, settings, scheduler, diagnostics, simulation, and failure tests.

### PHASE-12 Diagnostics and health
Add shared Overview/Diagnostics models and system, network, time, storage, security, tasks, I/O, and alarm sections.

### PHASE-13 Secure OTA
Design/validate partitions, local Web and HTTPS update paths, pending validation, rollback, production authenticity, diagnostics, and audit.

### PHASE-14 Tags, events, alarms, and audit
Add typed tags, quality, event bus, alarm evaluation/lifecycle/history, dynamic alarm panel, and audit viewer.

### PHASE-15 Logging, historian, and trends
Add data-point policies, SD logging, retention, recovery, historian queries, shared trends, pan/zoom/time navigation/export.

### PHASE-16 Board capabilities
Implement all verified relay, DIO, RS485, CAN, RTC, external I2C, and other exact-SKU capabilities through shared interfaces and safe hardware tests.

### PHASE-17 Production hardening
Complete budgets, watchdogs, power-cycle/fault/security tests, production configs, CI/release controls, migration tests, documentation, and final traceability.

### PHASE-18 First real application
Build the first application-specific module using only validated platform services, shared UI components, capability interfaces, and approved application-layer rules.

### PHASE-19 Platform expansion
Add separately approved extensions such as MQTT, Modbus TCP/RTU, OPC UA, webhooks, remote management, cloud integration, or alternate historian providers through ADRs and provider interfaces.

### PHASE-20 Version 1.0 release
Close all mandatory gaps, complete traceability/evidence, pass Production security/reliability/recovery tests, create signed release artifacts, and publish the approved 1.0.0 checkpoint.

## 25. Initial authorization boundary

Until explicitly authorized otherwise, the agent may execute PHASE-00 and PHASE-01 only. It shall stop at the PHASE-01 gate and report results. It shall not generate display, touch, LVGL, relay, DIO, RS485, CAN, Web application, network, OTA, or production firmware functionality during those phases.
