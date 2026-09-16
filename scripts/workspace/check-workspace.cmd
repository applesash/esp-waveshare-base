@echo off
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0check-workspace.ps1"
exit /b %ERRORLEVEL%
