#This file checks the existence of user-defined variable paths

if(NOT EXISTS ${FL_SDK_PATH})
    message(FATAL_ERROR "CMAKE FL SDK TEMPLATE: Variable FL_SDK_PATH doesn't refer to an existing path!")
endif()

if(NOT EXISTS ${FL_INSTALL_GENERATORS_PATH})
    message("CMAKE FL SDK TEMPLATE: warning! Variable FL_INSTALL_GENERATORS_PATH doesn't refer to any existing path!")
endif()

if(NOT EXISTS ${FL_INSTALL_GENERATORS_PATH})
    message("CMAKE FL SDK TEMPLATE: warning! Variable FL_INSTALL_EFFECTS_PATH doesn't refer to any existing path!")
endif()
