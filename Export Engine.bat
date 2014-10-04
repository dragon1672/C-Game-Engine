robocopy "./Engine/Engine" "./MiddleWare/EngineCorbin/include" *.h /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
robocopy "./Example Project/Debug" "./MiddleWare/EngineCorbin/bin" *.dll /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
robocopy "./Example Project/Debug" "./MiddleWare/EngineCorbin/lib" *.lib /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
echo Have a nice day! 
exit /b 1