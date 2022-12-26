project(InternalController_VC)

add_library(${PROJECT_NAME} SHARED
        FruityPlug.cpp FruityPlug.def FruityPlug.h
        Resource.h
        StdAfx.cpp StdAfx.h
        SynthForm.cpp SynthForm.h
        TestPlug.cpp TestPlug.h
        )

#Definitions needed by Visual Studio compiler
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

target_link_libraries(${PROJECT_NAME} fl_sdk)

include_directories(${FL_SDK_PATH})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${FL_INSTALL_EFFECTS_PATH}/${PROJECT_NAME}
        RUNTIME DESTINATION ${FL_INSTALL_EFFECTS_PATH}/${PROJECT_NAME})

