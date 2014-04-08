@echo off
set ENABLED=true

if %ENABLED% == true (
	echo creating moc files
	moc48 DebugSlider.h > DebugSlider_mock.cpp
	echo creating moc files complete
) else (
	echo rebuilding moc files skipped, re-enable in batch file
)