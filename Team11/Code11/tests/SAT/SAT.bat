cd /D "%~dp0"
START "AutoTester Script" "..\..\Debug\AutoTester.exe" SAT1-Source.txt SAT1-Queries.txt ..\TestOutput\outSAT1.xml
START "AutoTester Script" "..\..\Debug\AutoTester.exe" SAT2-Source.txt SAT2-Queries.txt ..\TestOutput\outSAT2.xml
START "AutoTester Script" "..\..\Debug\AutoTester.exe" SAT3-Source.txt SAT3-Queries.txt ..\TestOutput\outSAT3.xml
PAUSE
START firefox ..\TestOutput\outSAT1.xml
PING 127.0.0.1 -n 3 >NUL
START firefox ..\TestOutput\outSAT2.xml
PING 127.0.0.1 -n 3 >NUL
START firefox ..\TestOutput\outSAT3.xml
PING 127.0.0.1 -n 3 >NUL