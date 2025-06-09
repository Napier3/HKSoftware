
set(dlt860_client_example_data_define_SRCS
   dlt860_client_example_data_define.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_data_define_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_data_define
    ${dlt860_client_example_data_define_SRCS}
)

target_link_libraries(dlt860_client_example_data_define
    dlt860
)
