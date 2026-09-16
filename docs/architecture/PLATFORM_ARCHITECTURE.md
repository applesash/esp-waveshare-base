# Platform Architecture

Dependency direction:

`Applications -> UI/ViewModels -> Application Services -> Runtime/Domain Services -> Provider Interfaces -> Hardware/Simulation Providers -> BSP -> ESP-IDF`

The runtime owns lifecycle and registration. Board-specific facts remain in board packages. Shared platform services must not know a SKU. UI is presentation only.
