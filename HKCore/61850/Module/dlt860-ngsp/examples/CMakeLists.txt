# 约束 cmake 版本
cmake_minimum_required(VERSION 2.8.12)

# api搜索路径(对外提供接口时使用)
#include_directories(
#    /usr/local/include/libdlt860/
#)

# 服务端例子
add_subdirectory(server_example_simple)
add_subdirectory(server_example_update_single)
add_subdirectory(server_example_update_report)
add_subdirectory(server_example_rpc)
add_subdirectory(server_example_control)
add_subdirectory(server_example_settings)

# 客户端例子
add_subdirectory(dlt860_client_example_model)
add_subdirectory(dlt860_client_example_read_value)
add_subdirectory(dlt860_client_example_read_cbvalue)
add_subdirectory(dlt860_client_example_read_allvalue)
add_subdirectory(dlt860_client_example_filedirectory)
add_subdirectory(dlt860_client_example_filesync)
add_subdirectory(dlt860_client_example_getfile)
add_subdirectory(dlt860_client_example_setfile)
add_subdirectory(dlt860_client_example_brcb_report)
#add_subdirectory(dlt860_client_example_brcb_report_multiple_op)
add_subdirectory(dlt860_client_example_urcb_report)
add_subdirectory(dlt860_client_example_read_sg)
add_subdirectory(dlt860_client_example_edit_sg)
add_subdirectory(dlt860_client_example_set_value)
add_subdirectory(dlt860_client_example_dataset)
add_subdirectory(dlt860_client_example_connect)
add_subdirectory(dlt860_client_example_log)
add_subdirectory(dlt860_client_example_test)
add_subdirectory(dlt860_client_example_control)
add_subdirectory(dlt860_client_example_rpc)
add_subdirectory(dlt860_client_example_data_define)
#add_subdirectory(dlt860_decoder_example)

# windows 平台开启winpcap
if(WIN32)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        set(BUILD_SV_GOOSE_EXAMPLES ON)
        message("Found winpcap -> compile examples for GOOSE and SV")
    endif()
else()
    set(BUILD_SV_GOOSE_EXAMPLES OFF)
endif()

# GOOSE/SV 例子
if(${BUILD_SV_GOOSE_EXAMPLES})
    # add_subdirectory(server_example_goose)
    # add_subdirectory(goose_subscriber)
    # add_subdirectory(goose_publisher)
    # add_subdirectory(sv_subscriber)
    # add_subdirectory(iec61850_9_2_LE_example)
    # #add_subdirectory(iec61850_sv_client_example)
    # add_subdirectory(sv_publisher)
endif()
