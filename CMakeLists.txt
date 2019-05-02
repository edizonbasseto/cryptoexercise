#
# This file, project or its parts can not be copied and/or distributed without
# the express permission of Edizon Basseto Jr.
#
# @file: randomhelpers.hpp
# @Date: Sunday, 5th March 2019
# @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
#

# required modules for our task
include(ExternalProject)

# Setup the minimum version required of CMake to generate the Makefile
cmake_minimum_required (VERSION 3.1.3)

#Project name
project(CryptoMethod LANGUAGES CXX)

#-std=11
set_property(TARGET PROPERTY CXX_STANDARD 11)

#Setting version
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

#output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist/)

set(BUILD_TESTING "" OFF)
set(BUILD_TESTING_STATIC "" OFF)
set(BUILD_TESTING_SHARED "" OFF)

#Installing 3pps
#########################
set(JSON_BuildTests OFF CACHE INTERNAL "")
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.cryptopp.txt) #The worst... don't have a CMAKE file.

#Add the given directories to those the compiler uses to search for include files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include/helpers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include/business)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include/handlers)

set(CRYPTOMETHOD_EXECUTABLES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/business/KeyBusinessLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/business/MessageBusinessLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helpers/RandomHelpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helpers/RsaHelpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp )

add_executable(cryptomethod ${CRYPTOMETHOD_EXECUTABLES_FILES})
install(TARGETS cryptomethod DESTINATION bin)

#Joining LIBS
target_link_libraries(cryptomethod PUBLIC gmp gmpxx cryptopp boost_system)