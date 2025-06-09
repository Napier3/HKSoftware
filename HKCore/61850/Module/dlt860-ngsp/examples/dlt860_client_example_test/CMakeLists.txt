
set(dlt860_client_example_test_SRCS
    dlt860_client_example_test.cpp
    )

IF(WIN32)
set_source_files_properties(${dlt860_client_example_test_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_test
    ${dlt860_client_example_test_SRCS}
    )

target_link_libraries(dlt860_client_example_test
    dlt860
    )

