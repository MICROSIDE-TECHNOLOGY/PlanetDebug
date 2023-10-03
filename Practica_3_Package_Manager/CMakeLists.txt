cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Practica_3_Package_Manager LANGUAGES MikroC)
else()
    project(Practica_3_Package_Manager LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Practica_3_Package_Manager main.c)

############################ Practica_3_Package_Manager GENERATED CODE START ###########################
find_package(MikroSDK.Plot REQUIRED)
target_link_libraries(Practica_3_Package_Manager PUBLIC MikroSDK.Plot)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(Practica_3_Package_Manager PUBLIC MikroSDK.Log)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(Practica_3_Package_Manager PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_3_Package_Manager PUBLIC MikroC.Core)
############################ Practica_3_Package_Manager GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_3_Package_Manager
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Practica_3_Package_Manager
        PUBLIC
            MikroC.System
    )
endif()
