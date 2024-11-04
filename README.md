# CMake C++ Template for FL Studio SDK


<p align="center">
    <img src="assets/fl_logo.png" width="200">
</p>

This is a *unofficial* CMake template for building custom FL Studio plugins ("FL" plugins), using FL Studio SDK. 

## Dependencies
This project is intended to be used on **Windows**, using a **Visual Studio** compiler. <br>
It is recommended to use a CMake-based IDE (e.g. CLion, a properly configured VSCode...) to handle and edit the project.

### CMake
This is a CMake-based project: you will need to [install CMake](https://cmake.org/download/) into your system in order to use it.

### MFC
You will need to add mfc components for visual studio. Best way to do so is by using Visual Studio Installer:
- Open Visual Studio Installer: Locate Visual Studio Installer in the Start menu and open it.
- Select Your Version: Find the version of Visual Studio you are using and click on Modify.
- Click on the Individual Components bar.
- Write MFC on the search bar.
- Select an MFC version, be sure to select the right CPU compatibility (x64/86-arm...) and a version compatible with your Visual Studio version. (e.g. for visual studio 17, MFC version 143)

Install Required Components: Follow the instructions to complete the installation and wait for the components to update.

## Project overview
In Project Root Directory:
- `SDK` folder contains the [FL Studio SDK](https://www.image-line.com/developers/) with some slight modifications and the CMakeLists.txt.
The SDK gets built as a library and linked against the Plugin(s). The subdirectory `SDK/SDK_documentation` contains the documentation as provided by the SDK.
- `Examples` folder contains the 4 example projects (FruityGain_VC, Saw_VC and others) provided by the SDK. Each one is built as a separate CMake project, and 
can be enabled in the root CMakeLists.txt. The source files contain some debug and small changes. They could contain some bugs still. 
- `Plugin` folder contains the plugin project template. Edit and add files there to build your project.
- `CMakeLists.txt` is the "root" Cmake. This project shall be built from there.

## Setting up the project
### 1. Root CMakeLists.txt:
1. Set the project name if necessary. Notice that this is only an "aestetic" choice, since the plugin will not have this name.
2. lines `8` and `11`: Set the *Installation paths* (${FL_INSTALL_GENERATORS_PATH} and ${FL_INSTALL_EFFECTS_PATH}): projects will be exported there after installation (see below).
3. From line `17`: If needed, set the paths for your Compilers and generators. It's a better idea to let these lines commented, and let CMake handle them.

### 2. Plugin CMakeLists.txt:
1. line `2`: set the project name according to the desired plugin Name. Notice that all the generated files and installation process will take that as the Plugin name. Upon installation, the dll will have <project_name>_x64.dll as a name.
2. Lines `8`, `10`, `12`: change variables.
3. line `30`: add source files you include for your plugin. *Do not include SDK files, they are automatically being built!*
4. line `38`: link other libraries if needed

## Compile (release) and install the plugin
Notice: FL Studio seems to be able to open plugins compiled in release mode only.
From the root folder:
- Create build directory and generate the build project `cmake -B build -DCMAKE_BUILD_TYPE=Release` 
- Enter build folder `cd build`
- Build `cmake --build . --config Release`
- Install `cmake --install . --config Release`

## Compiling the examples
To compile the example projects, uncomment the line(s) `28-31`. To avoid compiling and installing the template Plugin, comment line `25`.
Compilation and install commands are the same as for the Plugin.

## SDK documentation
To explore the FL Studio SDK documentation, open with your browser got to `SDK/SDK_documentation` and open in your browser `index.html`