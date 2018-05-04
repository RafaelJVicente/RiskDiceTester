SET foldName=build
cd ../..
rmdir %foldName% /s /q
mkdir %foldName%
cd %foldName%
cmake ..\RiskDiceTester\ -G"Eclipse CDT4 - MinGW Makefiles"
PAUSE