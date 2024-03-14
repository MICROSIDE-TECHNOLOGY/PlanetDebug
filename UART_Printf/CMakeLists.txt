cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(UART_Printf LANGUAGES MikroC)
else()
    project(UART_Printf LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(UART_Printf
main.c
printf.c
printf.h
)

############################ UART_Printf GENERATED CODE START ###########################
find_package(MikroSDK.HalLowLevel.GPIO REQUIRED)
target_link_libraries(UART_Printf PUBLIC MikroSDK.HalLowLevel.GPIO)
find_package(MikroSDK.Driver.UART REQUIRED)
target_link_libraries(UART_Printf PUBLIC MikroSDK.Driver.UART)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(UART_Printf PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(UART_Printf PUBLIC MikroC.Core)
############################ UART_Printf GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(UART_Printf
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(UART_Printf
        PUBLIC
            MikroC.System
    )
endif()
