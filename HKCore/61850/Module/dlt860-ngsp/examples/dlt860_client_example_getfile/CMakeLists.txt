
set(dlt860_client_example_getfile_SRCS
   client_example_getfile.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_getfile_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_getfile
    ${dlt860_client_example_getfile_SRCS}
)

target_link_libraries(dlt860_client_example_getfile
    dlt860
)

