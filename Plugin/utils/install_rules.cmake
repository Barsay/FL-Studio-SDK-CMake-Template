#This file contains installation rules and checks

message("CMAKE FL SDK TEMPLATE: IS_EFFECT set to ${IS_EFFECT}")
message("CMAKE FL SDK TEMPLATE: IS_GENERATOR set to ${IS_GENERATOR}")

if(${IS_EFFECT})
    message("CMAKE FL SDK TEMPLATE: will be installed as an effect, in folder ${FL_INSTALL_EFFECTS_PATH}")
    install(TARGETS ${PROJECT_NAME}_x64
            RUNTIME DESTINATION ${FL_INSTALL_EFFECTS_PATH}/${PROJECT_NAME} )
endif()

if(${IS_GENERATOR})
    message("CMAKE FL SDK TEMPLATE: will be installed as a generator, in folder ${FL_INSTALL_GENERATORS_PATH}")
    install(TARGETS ${PROJECT_NAME}_x64
            RUNTIME DESTINATION ${FL_INSTALL_GENERATORS_PATH}/${PROJECT_NAME})
endif()

if(${IS_EFFECT} AND ${IS_GENERATOR})
    message("CMAKE FL SDK TEMPLATE: WARNING! this plugin is set both as a generator and an effect! will be installed in both directories!")
endif()

if(NOT ${IS_EFFECT} AND NOT {IS_GENERATOR})
    message("CMAKE FL SDK TEMPLATE: WARNING! This plugin is not set as a generator nor an effect! No installation will be performed")
endif()
