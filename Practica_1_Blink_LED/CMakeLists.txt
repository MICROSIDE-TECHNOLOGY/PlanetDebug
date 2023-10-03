cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Practica_1_Blink_LED LANGUAGES MikroC)
else()
    project(Practica_1_Blink_LED LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Practica_1_Blink_LED main.c)

############################ Practica_1_Blink_LED GENERATED CODE START ###########################
find_package(MikroSDK.Driver.GPIO.Out REQUIRED)
target_link_libraries(Practica_1_Blink_LED PUBLIC MikroSDK.Driver.GPIO.Out)
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_1_Blink_LED PUBLIC MikroC.Core)
############################ Practica_1_Blink_LED GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(Practica_1_Blink_LED
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Practica_1_Blink_LED
        PUBLIC
            MikroC.System
    )
endif()
