# Xela Networking
A small library that wraps the networking functions in Windows and Linux to allow for easy cross-platform network programming in C++.

#### Current version: 1.0.0

### Table of Contents
* [Installation](#installation)
* [Getting Started](#getting-started)
* [Credits](#credits)
* [License](#license)

### Installation
<details>
  <summary>Windows</summary>
  
  * Go to releases and download the latest release of XelaNetworking
  * Unzip the file in it's own folder
  * Link XelaNetworking to your project
    * The following instructions explain how to set this up with Visual Studio 2019, but similar steps would be used for any IDE. If you're unsure what to do, try searching for how to install libraries with your IDE of choice using Google.
      * When you're in your project on Visual Studio, on the right side should be Solution Explorer. Under the Solution (name) should be the name of your project.
      * Right click the name of your project and select Properties
      * In the properties window, select C/C++ -> General.
      * Click Additional Include Directories, then click the down arrow on the right side and select edit.
        * Add the path to xelanetworking_(version)_(x86/x64)/include
          * If you're targeting 32-bit systems, use the folder with x86. If you're targeting 64-bit systems, use the folder with x64.
        * Select OK
      * Go to linker -> General
      * Click Additional Library Directories, then click the down arrow on the right side and select edit
        * Add the path to xelanetworking_(version)_(x86/x64)/lib
        * Select OK
      * Make sure xelanetworking.dll is copied to the same folder your program's EXE file will be located in
        * xelanetworking.dll is located at xelanetworking_(version)_(x86/x64)/lib
      * Click apply
    * You're done! You can now use Xela Networking in your project.
    * When including header files from XelaNetworking in your project, be sure to prefix header file names with xela/networking/
      * Such as `#include <xela/networking/XelaNetworking.h>`
  
</details>
<details>
  <summary>Linux</summary>
  
  * Open a terminal in a new folder.
  * `git clone https://github.com/XelaSpirit/Xela-Networking.git`
  * `cd Xela-Networking`
  * `sudo ./install`
    * This will compile XelaNetworking and put the proper files for XelaNetworking in /usr/lib and /usr/include.
    * Header files will be in /usr/include/xela/networking, so in your programs make sure to prefix header includes with xela/networking.
      * Such as `#include <xela/networking/XelaNetworking.h>`
  * When compiling a program that uses XelaNetworking, link XelaNetworking.
    * With G++, this would look like `g++ <Source Files> -lxelanetworking`
  
</details>

### Getting Started
If you haven't already installed Xela Networking, make sure you read the [Installation](#installation) instructions to find out how.

The [Documentation](doc) contains information on every function in Xela Networking you might need to use while writing a program.

There's also some [sample code](sample) showing some of the features of the library

### Credits
**Author - Alex Morse:** morse.alex.j@gmail.com

### License
Xela Networking is under the terms of the MIT license, available [here](LICENSE.md)