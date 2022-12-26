cmake_minimum_required(VERSION 3.15)
project(FL_TEMPLATE)

#Path for the SDK
set(FL_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDK )

#Installation Folder for generator plugin export
set(FL_INSTALL_GENERATORS_PATH C:/Program\ Files/Image-Line/FL\ Studio\ 20/Plugins/Fruity/Generators)

#Installation Folder for Effect plugin plugin export
set(FL_INSTALL_EFFECTS_PATH C:/Program\ Files/Image-Line/FL\ Studio\ 20/Plugins/Fruity/Effects)

#Set compilers. NOTICE: This template only works with VISUAL Studio compilers!
#Behaviour with other compilers (e.g. MinGW) is undefined and could not work.
#If you are using an IDE (CLion, VSCode ...) it's a better idea to let handle compilers and generators, by keeping the following lines commented.

#set(CMAKE_C_COMPILER "<insert Visual Studio C Compiler path>")
#set(CMAKE_CXX_COMPILER "<insert Visual Studio C++ Compiler path>")
#set(CMAKE_MAKE_PROGRAM "<insert your make / Ninja / (other) path >")

#Adds the CMake project for the SDK
add_subdirectory(SDK)

#Adds the CMake project for the Plugin
add_subdirectory(Plugin)

#Uncomment to build example plugins
#add_subdirectory(Examples/Osc3_VC)
#add_subdirectory(Examples/FruityGain_VC)
#add_subdirectory(Examples/Saw_VC)
#add_subdirectory(Examples/InternalController_VC)

