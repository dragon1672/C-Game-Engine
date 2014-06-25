@echo off

call :processDirectory
goto :eof

:processDirectory
::compile mocs
for %%a in ("*.h") do (
	findstr /N Q_OBJECT "%%a" > tempLogFile && echo exporting %%a && moc48 %%a > %a%%%~na_mock.cpp
	del tempLogFile
)
::loop folders
for /D %%d in (*) do (
	cd %%d
	call :processDirectory
	cd ..
)
::not compiling
:eof

::requires moc48 to be in system path...fix this