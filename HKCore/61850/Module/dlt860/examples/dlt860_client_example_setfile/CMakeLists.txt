
set(dlt860_client_example_setfile_SRCS
   client_example_setfile.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_setfile_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_setfile
    ${dlt860_client_example_setfile_SRCS}
)

target_link_libraries(dlt860_client_example_setfile
    dlt860
)

