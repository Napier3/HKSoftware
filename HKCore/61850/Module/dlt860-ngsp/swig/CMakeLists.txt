cmake_minimum_required(VERSION 3.13)
project(dlt860server)

if(POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif()

# SWIG: use SWIG_MODULE_NAME property.
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

find_package(SWIG)

if(SWIG_FOUND)
include(${SWIG_USE_FILE})
find_package(Python COMPONENTS Development REQUIRED)

set_property(SOURCE dlt860_server.i PROPERTY CPLUSPLUS ON)

set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)
set(SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)
SET_SOURCE_FILES_PROPERTIES(dlt860_server.i PROPERTIES COMPILE_OPTIONS "-threads")

swig_add_library(pydlt860 LANGUAGE python SOURCES dlt860_server.i)
target_link_libraries(pydlt860 dlt860 scd Python::Python)

add_dependencies(pydlt860 dlt860 scd)


if(WIN32)

add_custom_command(TARGET pydlt860 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pydlt860> ${CMAKE_SOURCE_DIR}/gui/ngspserver/_pydlt860.pyd
    COMMAND ${CMAKE_COMMAND} -E copy dlt860_server.py ${CMAKE_SOURCE_DIR}/gui/ngspserver/dlt860_server.py
)
else()
add_custom_command(TARGET pydlt860 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pydlt860> ${CMAKE_SOURCE_DIR}/gui/ngspserver/_pydlt860.so
    COMMAND ${CMAKE_COMMAND} -E copy dlt860_server.py ${CMAKE_SOURCE_DIR}/gui/ngspserver/dlt860_server.py
)
endif(WIN32)
endif()
