
set(dlt860_client_example_read_allvalue_SRCS
   client_example_read_allvalue.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_read_allvalue_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_read_allvalue
    ${dlt860_client_example_read_allvalue_SRCS}
)

target_link_libraries(dlt860_client_example_read_allvalue
    dlt860
)
