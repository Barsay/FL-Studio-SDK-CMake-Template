project(FruityGain_VC_x64)

add_library(${PROJECT_NAME} SHARED
        EditorDialog.cpp EditorDialog.h
        FruityGain_VC.h FruityGain_VC.cpp FruityGain_VC.def
        Gain.h Gain.cpp
        resource.h
        StdAfx.cpp StdAfx.h
        )

#Definitions needed by Visual Studio compiler
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

target_link_libraries(${PROJECT_NAME} fl_sdk)

include_directories(${FL_SDK_PATH})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${FL_INSTALL_EFFECTS_PATH}/${PROJECT_NAME}
        RUNTIME DESTINATION ${FL_INSTALL_EFFECTS_PATH}/${PROJECT_NAME})
 