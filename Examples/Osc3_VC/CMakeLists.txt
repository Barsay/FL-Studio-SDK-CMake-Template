project(Osc3_VC)

add_library(${PROJECT_NAME} SHARED
        EditorDialog.h EditorDialog.cpp
        #Osc3_VC.h Osc3_VC.cpp
        Osc3_VC.def
        resource.h
        StdAfx.h StdAfx.cpp
        testplug.cpp testplug.h
        )


#Definitions needed by Visual Studio compiler
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

target_link_libraries(${PROJECT_NAME} fl_sdk)

include_directories(${FL_SDK_PATH})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${FL_INSTALL_GENERATORS_PATH}/${PROJECT_NAME}
        RUNTIME DESTINATION ${FL_INSTALL_GENERATORS_PATH}/${PROJECT_NAME})


