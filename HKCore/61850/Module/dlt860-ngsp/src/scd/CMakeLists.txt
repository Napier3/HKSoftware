cmake_minimum_required(VERSION 3.2)

aux_source_directory(. MODEL_GEN_SRC)
aux_source_directory(types TYPES_SRC)
aux_source_directory(model MODEL_SRC)
aux_source_directory(pugixml PUGIXML_SRC)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(scd ${MODEL_GEN_SRC} ${TYPES_SRC} ${MODEL_SRC} ${PUGIXML_SRC})
set_property(TARGET scd PROPERTY CXX_STANDARD 20)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/pugixml)

set(BINDIR "bin")
set(LIBDIR "lib")

if(UNIX)
    # GNUInstallDirs is required for Debian multiarch
    include(GNUInstallDirs)
    set(LIBDIR ${CMAKE_INSTALL_LIBDIR})
    set(BINDIR ${CMAKE_INSTALL_BINDIR})
endif()

# install 相关信息
install (TARGETS scd
        RUNTIME DESTINATION ${BINDIR} COMPONENT Applications
        ARCHIVE DESTINATION ${LIBDIR} COMPONENT Libraries
        LIBRARY DESTINATION ${LIBDIR} COMPONENT Libraries
)
