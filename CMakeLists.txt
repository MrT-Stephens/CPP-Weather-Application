cmake_minimum_required(VERSION 3.9.6...3.15.0)
project(EmptyStarter LANGUAGES C CXX)

set(ELEMENTS_ROOT "${PROJECT_SOURCE_DIR}/lib/elements")

add_link_options(/DYNAMICBASE /NXCOMPAT)

if (NOT ELEMENTS_ROOT)
   message(FATAL_ERROR "ELEMENTS_ROOT is not set")
endif()

# Make sure ELEMENTS_ROOT is an absolute path to add to the CMake module path
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

# If we are building outside the project, you need to set ELEMENTS_ROOT:
if (NOT ELEMENTS_BUILD_EXAMPLES)
   include(ElementsConfigCommon)
   set(ELEMENTS_BUILD_EXAMPLES OFF)
   add_subdirectory(${ELEMENTS_ROOT} elements)
endif()

set(ELEMENTS_APP_PROJECT "EmptyStarter")
set(ELEMENTS_APP_TITLE "Empty Starter")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2016-2023 Joel de Guzman")
set(ELEMENTS_APP_ID "com.cycfi.empty-starter")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)

set(ELEMENTS_APP_RESOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/View.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/DataView.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/DataView.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Controller.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Controller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Modal.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Modal.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/LoginView.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/LoginView.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Sensor.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/WeatherSensor.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/WeatherSensor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Xml.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Xml.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Subject.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/ProofID.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Authenticator.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/AuthenticatorInfo.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Storage.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Storage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/SubjectInfo.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/NoCopy.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Permission.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Resource.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/UserView.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/UserView.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/cloud.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/sun.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/cloud-sun.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/rain.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/snow.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/thunder.png"
)

# For your custom application icon on macOS or Windows see cmake/AppIcon.cmake module
include(AppIcon)
include(ElementsConfigApp)