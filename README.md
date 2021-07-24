# E-tag
Laser tag system on an ESP32 chip.
The source code is written in C using esp-idf.
We use 1 third-party library for the screen (ssd1306),the remaining pieces of code are taken from the examples of the official idf.
The project is configured for use with a bluetooth headband(if the headband is not connected via bluetooth
then the anti-cheat function will work by blocking all other functions).
To transfer the source code to platformio:
1. Install vs_code +platformio.
2. Create a new project with esp-idf.
3. We collect an empty project,if it is going normally, go to step 4.
4. Open the project folder in the usual Windows Explorer, files:
"partitions_4m.csv"
"platform.ini"
"sdkconfig"
copy the sdk config to the root of the project with a replacement.
We copy the files from the src folder to the src folder of the project with replacement.
We copy the files from the lib folder to the lib folder of the project.
5. We are building a project.If the project is not going to write in a personal account or read errors in the console and search in Google.
