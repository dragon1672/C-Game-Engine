@echo off

::clean the old
mkdir hackyTempFolder
robocopy hackyTempFolder ../MiddleWare/Engine /MIR /NFL /NDL /NJH /NJS /nc /ns /np
rmdir hackyTempFolder

::import the new
cd Engine
echo Export Log Begin > ../ExportMiddleWareLog.txt
for %%a in ("*.h") do (
		::findstr /N ENGINE_SHARED "%%a" > tempLogFile && echo exporting %%a >> ../ExportMiddleWareLog.txt &&robocopy . ../../MiddleWare/Engine/include/ %%a /NFL /NDL /NJH /NJS /nc /ns /np && echo exporting %%a
		echo exporting %%a >> ../ExportMiddleWareLog.txt
		robocopy . ../../MiddleWare/Engine/include/ %%a /NFL /NDL /NJH /NJS /nc /ns /np
)
cd ../Debug
::cd ../release
robocopy . ../../MiddleWare/Engine/lib/ Engine.lib /NFL /NDL /NJH /NJS /nc /ns /np
robocopy . ../../MiddleWare/Engine/bin/ Engine.dll /NFL /NDL /NJH /NJS /nc /ns /np
cd ../