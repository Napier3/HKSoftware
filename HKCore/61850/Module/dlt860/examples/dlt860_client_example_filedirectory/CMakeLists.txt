
set(dlt860_client_example_read_directory_SRCS
   client_example_read_directory.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_read_directory_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_directory
    ${dlt860_client_example_read_directory_SRCS}
)

target_link_libraries(dlt860_client_example_directory
    dlt860
)

