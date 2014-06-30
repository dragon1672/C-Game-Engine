robocopy "./Engine/Engine" "./MiddleWare/EngineCorbin/include" *.h /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
robocopy "./Example Project/Debug" "./MiddleWare/EngineCorbin/bin" *.dll /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
robocopy "./Example Project/Debug" "./MiddleWare/EngineCorbin/lib" *.lib /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
::prompt for copy paste into export folder
SET /P EXPORT=Do you want to copy to other SVN? (Y/N)? 
if /i {%EXPORT%}=={y} (goto :yes) 
if /i {%EXPORT%}=={yes} (goto :yes) 
goto :no 
:yes 
echo Exporting! 
::prompt changelog message
SET /P CommitMsg=What is the changelog message:  
cd ..
Date /t >> "./Engine Renderer Export/ChangeLog.txt"
echo -- Anthony Corbin >> "./Engine Renderer Export/ChangeLog.txt"
echo -*%CommitMsg% >> "./Engine Renderer Export/ChangeLog.txt"

robocopy "./Engine Renderer/MiddleWare/EngineCorbin" "./Engine Renderer Export" *.lib /S /R:1 /W:1 /NDL /XJD /XD OutputFolder
cd "Engine Renderer"

exit /b 0 

:no 
echo Have a nice day! 
exit /b 1