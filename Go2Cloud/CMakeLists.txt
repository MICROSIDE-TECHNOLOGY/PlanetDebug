cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Go2Cloud LANGUAGES MikroC)
else()
    project(Go2Cloud LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Go2Cloud main.c)

############################ Go2Cloud GENERATED CODE START ###########################
add_subdirectory(lib_g2c)
target_link_libraries(Go2Cloud PUBLIC Click.G2C)
add_subdirectory(lib_environment)
target_link_libraries(Go2Cloud PUBLIC Click.Environment)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(Go2Cloud PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(Go2Cloud PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(Go2Cloud PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(Go2Cloud PUBLIC MikroC.Core)
############################ Go2Cloud GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(Go2Cloud
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Go2Cloud
        PUBLIC
            MikroC.System
    )
endif()
