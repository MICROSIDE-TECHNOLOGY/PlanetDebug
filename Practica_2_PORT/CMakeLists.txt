cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Practica_2_PORT LANGUAGES MikroC)
else()
    project(Practica_2_PORT LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Practica_2_PORT main.c)

############################ Practica_2_PORT GENERATED CODE START ###########################
find_package(MikroSDK.Driver.GPIO.Port REQUIRED)
target_link_libraries(Practica_2_PORT PUBLIC MikroSDK.Driver.GPIO.Port)
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_2_PORT PUBLIC MikroC.Core)
############################ Practica_2_PORT GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_2_PORT
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Practica_2_PORT
        PUBLIC
            MikroC.System
    )
endif()
