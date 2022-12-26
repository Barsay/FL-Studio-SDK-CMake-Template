project(Saw_VC)

add_library(${PROJECT_NAME} SHARED
        FruityPlug.cpp FruityPlug.def testplug.h testplug.cpp
        )
#        ../SDK/fp_cplug.h ../SDK/fp_cplug.cpp
#        ../SDK/fp_def.h
#        ../SDK/fp_extra.cpp ../SDK/fp_extra.h
#        ../SDK/fp_pathmanager.cpp ../SDK/fp_pathmanager.h
#        ../SDK/fp_plugclass.cpp
#        ../SDK/fp_plugclass.h ../SDK/generictransport.h)

#Definitions needed by Visual Studio compiler
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

target_link_libraries(${PROJECT_NAME} fl_sdk)

include_directories(${FL_SDK_PATH})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${FL_INSTALL_GENERATORS_PATH}/${PROJECT_NAME}
        RUNTIME DESTINATION ${FL_INSTALL_GENERATORS_PATH}/${PROJECT_NAME})


