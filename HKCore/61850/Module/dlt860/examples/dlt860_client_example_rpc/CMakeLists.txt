
set(dlt860_client_example_rpc_SRCS
    dlt860_client_example_rpc.cpp
    )

IF(WIN32)
set_source_files_properties(${dlt860_client_example_rpc_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_rpc
    ${dlt860_client_example_rpc_SRCS}
    )

target_link_libraries(dlt860_client_example_rpc
    dlt860
    )

