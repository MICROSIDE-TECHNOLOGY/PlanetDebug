cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Practica_4_GUI LANGUAGES MikroC)
else()
    project(Practica_4_GUI  LANGUAGES C ASM)
endif()

include(mikroeUtils)

set(PROJECT_TYPE "designer" CACHE STRING "" FORCE)

add_executable(Practica_4_GUI 
    main.c
    main_screen.c
    main_screen.h
    main_screen.mscr
)

designer_generator(Practica_4_GUI resource.mres main_screen.mscr)
############################ Practica_4_GUI GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
find_package(MikroSDK.TouchController REQUIRED)
find_package(MikroSDK.GraphicLibrary REQUIRED)
find_package(MikroSDK.VisualTft REQUIRED)

target_link_libraries(Practica_4_GUI
    PUBLIC
        MikroC.Core
        MikroSDK.TouchController
        MikroSDK.GraphicLibrary
        MikroSDK.VisualTft
)
############################ Practica_4_GUI GENERATED CODE END ###########################