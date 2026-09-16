# Layer Rules

- Applications may compose screens, workflows, configuration, and application rules.
- UI depends on ViewModels, never providers/BSP/ESP-IDF.
- ViewModels depend on application services.
- Domain services depend on provider interfaces.
- Hardware providers may depend on BSP and ESP-IDF.
- BSP exposes hardware mapping, initialization, capabilities, and safe states only.
- Renderers implement presentation, never business logic.
