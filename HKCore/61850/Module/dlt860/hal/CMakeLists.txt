cmake_minimum_required(VERSION 3.0)

# 交叉编译工具连
if(DEFINED ENV{TOOLCHAIN})
    set(CMAKE_C_COMPILER        $ENV{TOOLCHAIN}gcc)
    set(CMAKE_CXX_COMPILER      $ENV{TOOLCHAIN}g++)
    set(CMAKE_AR        "$ENV{TOOLCHAIN}ar" CACHE FILEPATH "CW archiver" FORCE)
endif()

# 项目名字
project(hal)

# 设置版本号
set(LIBHAL_VERSION_MAJOR "2")
set(LIBHAL_VERSION_MINOR "0")
set(LIBHAL_VERSION_PATCH "0")

# clock_gettime 检查
include(CheckLibraryExists)
check_library_exists(rt clock_gettime "time.h" CONFIG_SYSTEM_HAS_CLOCK_GETTIME)

# 探测平台大小端
include (TestBigEndian)
test_big_endian(PLATFORM_IS_BIGENDIAN)

# windows 平台
if(WIN32)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        message("Found winpcap -> compile ethernet HAL layer (required for GOOSE/SV support)")
        set(WITH_WPCAP 1)
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Include")
    else()
        message("winpcap not found -> skip ethernet HAL layer (no GOOSE/SV support)")
    endif()
endif(WIN32)

# 头文件包含
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

# linux 平台源文件
set (libhal_linux_SRCS
 ${CMAKE_CURRENT_LIST_DIR}/socket/linux/socket_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/ethernet/linux/ethernet_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/thread/linux/thread_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/time/unix/time.cpp
 ${CMAKE_CURRENT_LIST_DIR}/serial/linux/serial_port_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/memory/lib_memory.cpp
)

# windows 平台源文件
set (libhal_windows_SRCS
 ${CMAKE_CURRENT_LIST_DIR}/socket/win32/socket_win32.cpp
 ${CMAKE_CURRENT_LIST_DIR}/thread/win32/thread_win32.cpp
 ${CMAKE_CURRENT_LIST_DIR}/time/win32/time.cpp
 ${CMAKE_CURRENT_LIST_DIR}/memory/lib_memory.cpp
)

# winpcap 选项开启时
if(WITH_WPCAP)
    set (libhal_windows_SRCS ${libhal_windows_SRCS}
     ${CMAKE_CURRENT_LIST_DIR}/ethernet/win32/ethernet_win32.cpp
    )
endif(WITH_WPCAP)

# BSD 平台源文件
set (libhal_bsd_SRCS
 ${CMAKE_CURRENT_LIST_DIR}/socket/bsd/socket_bsd.cpp
 ${CMAKE_CURRENT_LIST_DIR}/ethernet/bsd/ethernet_bsd.cpp
 ${CMAKE_CURRENT_LIST_DIR}/thread/bsd/thread_macos.cpp
 ${CMAKE_CURRENT_LIST_DIR}/filesystem/linux/file_provider_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/time/unix/time.cpp
 ${CMAKE_CURRENT_LIST_DIR}/memory/lib_memory.cpp
)

# MACOS 平台源文件
set (libhal_macos_SRCS
 ${CMAKE_CURRENT_LIST_DIR}/socket/bsd/socket_bsd.cpp
 ${CMAKE_CURRENT_LIST_DIR}/ethernet/bsd/ethernet_bsd.cpp
 ${CMAKE_CURRENT_LIST_DIR}/thread/macos/thread_macos.cpp
 ${CMAKE_CURRENT_LIST_DIR}/filesystem/linux/file_provider_linux.cpp
 ${CMAKE_CURRENT_LIST_DIR}/time/unix/time.cpp
 ${CMAKE_CURRENT_LIST_DIR}/memory/lib_memory.cpp
)

# 屏蔽掉平台层 获取源码详情
IF(WIN32)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        message("Found winpcap -> can compile with GOOSE support")
        set(WITH_WPCAP 1)
    endif()

    set (libhal_SRCS
        ${libhal_windows_SRCS}
    )

    IF(MSVC)
        set_source_files_properties(${libhal_SRCS} PROPERTIES LANGUAGE CXX)
    ENDIF()

ELSEIF(UNIX)
    IF(APPLE)
        set (libhal_SRCS
            ${libhal_macos_SRCS}
        )
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        set (libhal_SRCS
            ${libhal_bsd_SRCS}
        )
    ELSE()
        set (libhal_SRCS
            ${libhal_linux_SRCS}
        )
    ENDIF(APPLE)
ENDIF(WIN32)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )

# TLS 支持
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/../third_party/mbedtls/mbedtls-2.16)
    message("Found mbedtls -> can compile with TLS support")
    set(WITH_MBEDTLS 1)
endif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/../third_party/mbedtls/mbedtls-2.16)
if(WITH_MBEDTLS)
    include_directories(
            ${CMAKE_CURRENT_LIST_DIR}/tls/mbedtls
        ${CMAKE_CURRENT_LIST_DIR}/../third_party/mbedtls/mbedtls-2.16/include
    )
    file(GLOB tls_SRCS ${CMAKE_CURRENT_LIST_DIR}/../third_party/mbedtls/mbedtls-2.16/library/*.c)
    add_definitions(-DMBEDTLS_CONFIG_FILE="mbedgsp_tls_config.h")
    set (libhal_SRCS ${libhal_SRCS}
      ${CMAKE_CURRENT_LIST_DIR}/tls/mbedtls/tls_mbedtls.c
    )

    IF(MSVC)
        set_source_files_properties(${libhal_SRCS} PROPERTIES LANGUAGE CXX)
    ENDIF()

    list (APPEND libhal_SRCS ${tls_SRCS})

endif(WITH_MBEDTLS)

# 静态库
add_library (dlt860hal STATIC ${libhal_SRCS})

# 静态库(位置无关,该静态库可以被编译进动态库中)
add_library (dlt860hal-shared STATIC ${libhal_SRCS})
# target_compile_definitions(dlt860hal-shared PRIVATE EXPORT_FUNCTIONS_FOR_DLL)
# SET_TARGET_PROPERTIES(dlt860hal-shared PROPERTIES COMPILE_FLAGS "-fPIC" )

# 链接目标库
IF(UNIX)
  IF (CONFIG_SYSTEM_HAS_CLOCK_GETTIME)
     target_link_libraries (dlt860hal
         -lpthread
         -lrt
     )
  ELSE ()
     target_link_libraries (dlt860hal
         -lpthread
     )
  ENDIF (CONFIG_SYSTEM_HAS_CLOCK_GETTIME)
ENDIF(UNIX)

# mingw 时链接额外的库
IF(MINGW)
  target_link_libraries(dlt860hal ws2_32 iphlpapi)
ENDIF(MINGW)

# winpcap 时链接额外的库
iF(WITH_WPCAP)
    target_link_libraries(dlt860hal
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/packet.lib
)
ENDIF(WITH_WPCAP)

set(BINDIR "bin")
set(LIBDIR "lib")
if(UNIX)
    # GNUInstallDirs is required for Debian multiarch
    include(GNUInstallDirs)
    set(LIBDIR ${CMAKE_INSTALL_LIBDIR})
    set(BINDIR ${CMAKE_INSTALL_BINDIR})
endif()

# install 相关信息
install (TARGETS dlt860hal
	RUNTIME DESTINATION ${BINDIR} COMPONENT Applications
	ARCHIVE DESTINATION ${LIBDIR} COMPONENT Libraries
        LIBRARY DESTINATION ${LIBDIR} COMPONENT Libraries
)

