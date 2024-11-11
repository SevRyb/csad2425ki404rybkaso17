@echo off

rem create deploy directory
mkdir deploy
cd deploy
mkdir client
mkdir server
cd ..
echo [INFO] Created deploy directory

rem build client app
cd client
mkdir build
cd build
cmake ..
cmake --build .
cd ../..
xcopy "client/build" "deploy/client" /E /I
echo [INFO] Client app built in deploy

rem build and upload server app
cd server
platformio run --target upload
cd ..
xcopy "server/.pio/build" "deploy/server" /E /I
echo [INFO] Server app built in deploy and uploaded to ESP

rem run tests
cd client/build
ctest -C Debug
cd ../..
echo [INFO] Tests completed

rem clean build directories from roots
cd client
rmdir /S /Q build
cd ../server/.pio
rmdir /S /Q build
cd ../..
echo [INFO] Cleaned up