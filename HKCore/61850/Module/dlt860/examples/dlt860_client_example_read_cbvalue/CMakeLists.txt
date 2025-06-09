
set(dlt860_client_example_read_cbvalue_SRCS
   client_example_read_cbvalue.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_read_cbvalue_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_read_cbvalue
    ${dlt860_client_example_read_cbvalue_SRCS}
)

target_link_libraries(dlt860_client_example_read_cbvalue
    dlt860
)
