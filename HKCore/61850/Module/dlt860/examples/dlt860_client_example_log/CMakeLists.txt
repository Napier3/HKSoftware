
set(dlt860_client_example_log_SRCS
   dlt860_client_example_log.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_log_SRCS} PROPERTIES LANGUAGE CXX)

ENDIF(WIN32)

add_executable(dlt860_client_example_log
    ${dlt860_client_example_log_SRCS}
)

target_link_libraries(dlt860_client_example_log
    dlt860
)

