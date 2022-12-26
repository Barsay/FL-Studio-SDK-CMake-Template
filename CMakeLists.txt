cmake_minimum_required(VERSION 3.23)
project(FL_TEMPLATE)


set(FL_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDK )
set(FL_INSTALL_GENERATORS_PATH C:/Program\ Files/Image-Line/FL\ Studio\ 20/Plugins/Fruity/Generators)
set(FL_INSTALL_EFFECTS_PATH C:/Program\ Files/Image-Line/FL\ Studio\ 20/Plugins/Fruity/Effects)


add_subdirectory(SDK)
add_subdirectory(Plugin)

#Uncomment to build example plugins
#add_subdirectory(Examples/Osc3_VC)
#add_subdirectory(Examples/FruityGain_VC)
#add_subdirectory(Examples/Saw_VC)
#add_subdirectory(Examples/InternalController_VC)

