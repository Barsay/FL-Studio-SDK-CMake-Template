# CMake C++ Template for FL Studio SDK


<p align="center">
    <img src="assets/fl_logo.png" width="200">
</p>

This is a *unofficial* CMake template for building custom FL Studio plugins ("FL" plugins), using FL Studio SDK. 

## Dependencies
This project is intended to be used on **Windows**, using a **Visual Studio** compiler. <br>
It is recommended to use a CMake-based IDE (CLion, a properly configured VSCode...) to handle and edit the project.

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
2. lines `8` and `11`: Set the *Installation paths* (${FL_INSTALL_GENERATORS_PATH} and ${FL_INSTALL_EFFECTS_PATH}): projects will be saved there.
3. From line `17`: If needed, set the paths for your Compilers and generators. It's a better idea to let these lines commented, and let the IDE handle them (if you are using one).
4. If needed, add subdirectories by uncommenting them. 

### 2. Plugin CMakeLists.txt:
1. line `2`: set the project name according to the desired plugin Name. Notice that all the generated files and installation process will take that as the Plugin name. On installation, the dll will have <project_name>_x64.dll as a name.
2. Lines `8`, `10`, `12`: change variables.
3. line `30`: add source files you include for your plugin. *Do not include SDK files, they are automatically being built!*
4. line `38`: link other libraries if needed

## Compile the plugin
From the project root folder:
- Generate Makefiles inside a build directory `cmake -B build` 
- Enter Build folder `cd build`
- Build `cmake --build . --config Release` <br>

