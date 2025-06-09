# 约束 cmake 版本
cmake_minimum_required(VERSION 2.8.12)

# 交叉编译时的对于编译工具连的探测
if(DEFINED ENV{TOOLCHAIN})
    set(CMAKE_C_COMPILER	$ENV{TOOLCHAIN}gcc)
    set(CMAKE_CXX_COMPILER	$ENV{TOOLCHAIN}g++)
    set(CMAKE_AR	"$ENV{TOOLCHAIN}ar" CACHE FILEPATH "CW archiver" FORCE)
endif()

# 项目名字
project(ngsp)

# 启用测试
ENABLE_TESTING()

# 设置版本号
set(LIB_VERSION_MAJOR "1")
set(LIB_VERSION_MINOR "0")
set(LIB_VERSION_PATCH "38")
set(LIB_VERSION "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}")
ADD_DEFINITIONS(-DLIB_VERSION=\"${LIB_VERSION}\")

# 强制加上编译调试选项
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 设置模块的搜索路径(采用里面的配置)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/third_party/cmake/modules/")

# clock_gettime 函数存在行判断
include(CheckLibraryExists)
check_library_exists(rt clock_gettime "time.h" CONFIG_SYSTEM_HAS_CLOCK_GETTIME)

# 测试平台的大小端
include (TestBigEndian)
test_big_endian(PLATFORM_IS_BIGENDIAN)

# 设置最大的数据单元的尺寸
set(CONFIG_MMS_MAXIMUM_APDU_SIZE "32767" CACHE STRING "配置 MMS PDU 最大长度 (default 32767)"   )
set(CONFIG_MMS_MAXIMUM_ASDU_SIZE "32763" CACHE STRING "配置 MMS SDU 最大长度(default 32763)"   )

# 设置最大客户端链接数量
set(CONFIG_MAXIMUM_TCP_CLIENT_CONNECTIONS 32 CACHE STRING "配置服务端所允许的客户端并发数量")

# 编译选项 是否构建使用示例
option(BUILD_EXAMPLES "构建示例" ON)

# 编译选项 是否构建python绑定
option(BUILD_PYTHON_BINDINGS "构建python支持" OFF)

# 编译选项 是否构建单线程版本
option(CONFIG_MMS_SINGLE_THREADED "构建单线程版本" ON)

# 编译选项 是否构建无线程堆栈
option(CONFIG_MMS_THREADLESS_STACK "构建无线程堆栈 (warning: single- or multi-threaded server will not work!)" OFF)

# 编译选项 是否启用TCP keepalive 的功能
option(CONFIG_ACTIVATE_TCP_KEEPALIVE "开启 TCP keepalive" OFF)

# 编译选项 是否启用 GOOSE 的功能
option(CONFIG_INCLUDE_GOOSE_SUPPORT "GOOSE特性 支持" OFF)

# 编译选项 是否服务端支持控制操作
option(CONFIG_DLT860_CONTROL_SERVICE "控制特性 支持" ON)

# 编译选项 是否服务端支持报告
option(CONFIG_DLT860_REPORT_SERVICE "服务报告特性 支持" ON)

# 编译选项 是否服务端支持日志
option(CONFIG_DLT860_LOG_SERVICE "日志特性 支持" ON)

# 编译选项 是否服务端支持定制组操作
option(CONFIG_DLT860_SETTING_GROUPS "定制组特性 支持" ON)

# 编译选项 是否服务端提供用户读操作的回调控制
option(CONFIG_DLT860_SUPPORT_USER_READ_ACCESS_CONTROL "读值回调特性 支持" ON)

# 设置报告的默认缓存大小
set(CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE "100" CACHE STRING "默认报告缓存大小" )

# 编译选项 是否启用调试打印模式
option(DEBUG_SERVER "启动服务端调试" OFF)
option(DEBUG_CLIENT "启动客户端调试" ON)
option(DEBUG_APER "编码调试信息" ${DEBUG_CLIENT})
option(DEBUG_SOCKET "启用 socket 层 printf 打印" ${DEBUG_SERVER})
option(DEBUG_COTP "启用 COTP 层 打印" ${DEBUG_SERVER})
option(DEBUG_ISO_SERVER "启用  ISO SERVER printf 调试" ${DEBUG_SERVER})
option(DEBUG_ISO_CLIENT "启用 ISO CLIENT printf 调试" ${DEBUG_CLIENT})
option(DEBUG_IED_SERVER "启用 IED SERVER printf 调试" ${DEBUG_SERVER})
option(DEBUG_IED_CLIENT "启用 IED CLIENT printf 调试" ${DEBUG_CLIENT})
option(DEBUG_MMS_SERVER "启用 MMS SERVER printf 调试" ${DEBUG_SERVER})
option(DEBUG_MMS_CLIENT "启用 MMS CLIENT printf 调试" ${DEBUG_CLIENT})
option(DEBUG_GOOSE_SUBSCRIBER "启用 GOOSE subscriber printf 调试" ${DEBUG_SERVER})
option(DEBUG_GOOSE_PUBLISHER "启用 GOOSE publisher printf 调试" ${DEBUG_SERVER})
option(DEBUG_SV_SUBSCRIBER "启用 Sampled Values subscriber 调试" ${DEBUG_SERVER})
option(DEBUG_SV_PUBLISHER "启用 Sampled Values publisher 调试" ${DEBUG_SERVER})
option(DEBUG_HAL_ETHERNET "启用 Ethernet HAL printf 调试" ${DEBUG_SERVER})

# 错误打印时是否断言终止程序
option(ERROR_JUST_LOG "出现严重错误时,是否仅仅是打印日志" ${ERROR_JUST_LOG})

# 设置头文件的搜索路径
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/src/common/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/goose
    ${CMAKE_CURRENT_LIST_DIR}/src/sampled_values
    ${CMAKE_CURRENT_LIST_DIR}/src/hal/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/dlt860/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/dlt860/inc_private
    ${CMAKE_CURRENT_LIST_DIR}/src/mms/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/mms/inc/valuehelper
    ${CMAKE_CURRENT_LIST_DIR}/src/mms/inc_private
    ${CMAKE_CURRENT_LIST_DIR}/src/mms/iso_mms/asn1c_860
    ${CMAKE_CURRENT_LIST_DIR}/src/logging
    ${CMAKE_CURRENT_LIST_DIR}/src/model
    ${CMAKE_CURRENT_LIST_DIR}/src/scd
    ${CMAKE_CURRENT_LIST_DIR}/src/scd/pugixml
    ${CMAKE_CURRENT_LIST_DIR}/src/scd/types
    ${CMAKE_CURRENT_LIST_DIR}/src/scd/model
    ${CMAKE_CURRENT_LIST_DIR}/src/hashmap
    ${CMAKE_CURRENT_LIST_DIR}/src/sg
    ${CMAKE_CURRENT_LIST_DIR}/3rd_lib
    ${CMAKE_CURRENT_LIST_DIR}/3rd_lib/sqlite
)

# c++ 标准
set(CMAKE_CXX_STANDARD 20)

# 编解码的接口
file(GLOB API_HEADERS_EXTRA
    "${CMAKE_CURRENT_LIST_DIR}/src/mms/iso_mms/asn1c_860/*.h"
)

# 设置API接口说明
set(API_HEADERS
    hal/inc/gsp_hal_base.h
    hal/inc/gsp_hal_time.h
    hal/inc/gsp_hal_thread.h
    hal/inc/gsp_hal_ethernet.h
    hal/inc/gsp_hal_socket.h
    hal/inc/gsp_tls_config.h
    hal/inc/gsp_lib_memory.h
    src/common/inc/libdlt860_common_api.h
    src/common/inc/gsp_linked_list.h
    src/common/inc/libdlt860_define.h
    src/common/inc/nlogging.h
    src/common/inc/conversions.h
    src/dlt860/inc/dlt860_client.h
    src/dlt860/inc_private/gsp_ied_connection_private.h
    src/dlt860/inc/dlt860_common.h
    src/dlt860/inc/dlt860_cdc.h
    src/dlt860/inc/dlt860_dynamic_model.h
    src/dlt860/inc/dlt860_model.h
    src/dlt860/inc/dlt860_server_interface.h
    src/model/modelgenerator.h
    src/mms/inc/gsp_mms_value.h
    src/mms/inc/gsp_mms_common.h
    src/mms/inc/gsp_mms_types.h
    src/mms/inc/gsp_mms_type_spec.h
    src/mms/inc/gsp_mms_client_connection.h
    src/mms/inc/gsp_mms_server.h
    src/mms/inc/gsp_iso_connection_parameters.h
    src/mms/inc/asn_inc.h
    src/goose/gsp_goose_subscriber.h
    src/goose/gsp_goose_receiver.h
    src/goose/gsp_goose_publisher.h
    src/sampled_values/gsp_sv_subscriber.h
    src/sampled_values/gsp_sv_publisher.h
    src/logging/logging_api.h
)

# msvc编译器的判断
if(MSVC AND MSVC_VERSION LESS 1800)
    include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/src/vs
    )
endif(MSVC AND MSVC_VERSION LESS 1800)

if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(CMAKE_CXX_FLAGS "/Zc:strictStrings-")
endif(MSVC)

# TLS 支持的判断 (指定目录存在源码包时,自动附加该功能)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/third_party/mbedtls/mbedtls-2.16)
    set(WITH_MBEDTLS 1)
endif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/third_party/mbedtls/mbedtls-2.16)
if(WITH_MBEDTLS)
    add_definitions(-DCONFIG_MMS_SUPPORT_TLS=1)
endif(WITH_MBEDTLS)

# 配置信息
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/config/stack_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config/stack_config.h
)

# 增加硬件平台层头文件
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/hal/inc
)

# 增加硬件平台层源文件
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/hal")

# 调试模式时修改构建方式
if(DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
endif(DEBUG)

# 需要构建例子时引入源码
if(BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples)
endif(BUILD_EXAMPLES)

# 引入系统源码
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

# python binding
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/swig)

# install 命令时的文件操作
install(FILES ${API_HEADERS} DESTINATION include/libdlt860 COMPONENT Development)
install(FILES ${API_HEADERS_EXTRA} DESTINATION include/libdlt860 COMPONENT Development)

# cpack 打包相关配置
set(CPACK_PACKAGE_DESCRIPTION "DLT/860 MMS/GOOSE client and server library")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "DLT/860 MMS/GOOSE MMS/GOOSE client and server library")
set(CPACK_PACKAGE_VENDOR "sduept")
set(CPACK_PACKAGE_CONTACT "comm@sduept.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${LIB_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${LIB_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${LIB_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_COMPONENTS_ALL Libraries Development Applications)
#set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}")
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
    include(InstallRequiredSystemLibraries)
    include(CPack)
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")


