#Plugin name
project(PLUGIN)

#-------VARIABLES-------#
#Set these variables according to your needs. They are used by this CMakeLists.txt and included .cmake files to configure files, set tests etc.

#True if the plugin is an effect
set(IS_EFFECT TRUE)
#True if the plugin is a Generator.
set(IS_GENERATOR FALSE)
#Insert here your plugin description
set(PLUGIN_DESCRIPTION "Describe your plugin here")

#TODO: this feature has to be implemented yet
#if set TRUE, enables the testing suite for this plugin. The testing suite includes googleTests and default assertions
#to assert the "basic" functioning of the plugin.
#set(PLUGIN_TESTING_ENABLED FALSE)

#------FILE SETTINGS------#
#This section contains semi-automatic file generation settings.
#Notice: the configured files are in the build folder.
configure_file(utils/definitions.h.in definitions.h @ONLY)
configure_file(utils/plugin.def.in ${PROJECT_NAME}.def)

#Include files in the binary dir (useful for including configured definition.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Add here the files to be built.
#Notice: SDK files do not need to be included here!
add_library(${PROJECT_NAME}_x64 SHARED
        plugin.h plugin.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.def #include the configured .def file for exporting functions.
        )

#-----------------------#

#Link the sdk files against the library
target_link_libraries(${PROJECT_NAME}_x64 fl_sdk)

#Include the SDK: enables to include the SDK files using #include "<filename>.hpp" without inserting full or relative path
include_directories(${FL_SDK_PATH})

#Executes CMake commands (here check of directory existence) in the given .cmake file
include(utils/check_dir.cmake)
#Executes CMake commands (here related to installation) in the given .cmake file
include(utils/install_rules.cmake)

#Definitions needed by Visual Studio compiler
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

