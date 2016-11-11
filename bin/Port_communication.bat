@echo off
"%cd%"
cd ..
"%cd%"
cd ..
"%cd%"
cd ..
cd Program Files (x86)
cd Zaber Technologies
cd Zaber Console 2.0.10
cd Scripts
ScriptRunner /port COM3 /m a Port_communication.cs>> 233.txt

exit