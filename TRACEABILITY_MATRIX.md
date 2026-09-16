# Requirements Traceability Matrix

| Requirement | Summary | Component / Document | Test | Board | Status | Evidence |
|---|---|---|---|---|---|---|
| RS-GOV-001 | Reusable platform | AGENT_CONTRACT.md | Contract review | All | BASELINED | AGENT_CONTRACT.md |
| RS-WORK-001 | Validate workspace | scripts/workspace/check-workspace.sh | Workspace check executed | All | PASS | scripts/workspace/check-workspace.sh |
| RS-HW-001 | Initial supported devices | AGENT_CONTRACT.md | Source confirmation | 28154, 28141, 30838 | CONFIRMED | docs/devices/*/SOURCE_REGISTER.md |
| RS-HW-003 | Capability manifest | boards/*/board_manifest.json | Manifest validation | All | IN PROGRESS | board_manifest.json |
| RS-SRC-004 | Source/GPIO evidence | docs/devices/*/SOURCE_REGISTER.md; GPIO_REGISTER.md | Source review | 28154, 28141, 30838 | IN PROGRESS | docs/devices/* |
| RS-DISP-001 | Verified display mapping | docs/devices/* | Display diagnostic | 28154, 28141 | NOT STARTED | Pending |
| RS-TOUCH-002 | Raw GT911 gate | apps/touch_diagnostic | Touch acceptance | 28154, 28141 | NOT STARTED | Pending |
| RS-HELLO-003 | Shared UI acceptance | apps/hello_world | Three-board acceptance | All | NOT STARTED | Pending |
| RS-GIT-002 | HTTPS browser login | scripts/github/login.ps1 | Auth status check | Host | NOT STARTED | Pending |

| RS-BACKUP-001 | Phase restore point | scripts/github/create-phase-checkpoint.ps1 / scripts/github/verify-phase-closeout.sh | Recovery verification | All | BASELINED | docs/recovery/RECOVERY_POLICY.md |
| RS-RECOVERY-001 | Verify latest checkpoint | scripts/github/verify-phase-closeout.sh | Recovery check | All | BASELINED | docs/recovery/RESTORE_POINTS.md |
