# pico-two-cores

First application for Raspberry Pi Pico, exploring the onboard temperature sensor and multi core capability.

If this is your first time here, go to *Windows 10 Installation bellow* and perform the installation steps.

## Build:

```
mkdir build
cd build
cmake -G "NMake Makefiles" .. 
nmake
```

## Install 

Go into the `build` folder and you will find `twoCores.uf2` file.

The .uf2 file can be dragged into the USB storage drive letter that appears when you hold down the BOOTSEL button and plug the Pico's USB connection into your PC (release the button after you've plugged the Pico into the PC). The application should become programmed into the Flash storage and begin execution.

## Windows 10 Installation:

* _Pico Setup Installer_:
1) Download and run its latest release from https://github.com/ndabas/pico-setup-windows/releases. It will install everything you need.
2) Go to the folder where you installed it and run the script `pico_env.py` and `pico_setup.py`, just by double clicking on them.
3) You can now go to the `CMakeLists.txt` file in this repo and adjust the `PICO_SDK_PATH` for your case.

* _Compilation of examples_:
1) Open the *Developer Command Prompt for VS 2019*.
2) Go to `pico-examples` folder.
3) Execute:
```
mkdir build
cd build
cmake -G "NMake Makefiles" .. 
nmake
```
It will take a while to build all the examples.

4) *(optional)* After that, you can look for `.uf2` files for each example subdirectory, plug your Pico to the serial with `BOOTSEL` pressed down and test some of them.

## Configuring Visual Studio Code:
1) Go to https://www.element14.com/community/community/raspberry-pi/blog/2021/01/24/working-with-the-raspberry-pi-pico-with-windows.
2) Follow the instruction from section *Building with Visual Code* on.

This should be enough for you to start developing for Rasberry Pi Pico in a Windows 10 environment.
