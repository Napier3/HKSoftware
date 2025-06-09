
set(dlt860_client_example_set_value_SRCS
   dlt860_client_example_set_value.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_set_value_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_set_value
    ${dlt860_client_example_set_value_SRCS}
)

target_link_libraries(dlt860_client_example_set_value
    dlt860
)
