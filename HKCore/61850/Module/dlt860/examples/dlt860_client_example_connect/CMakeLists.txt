
set(dlt860_client_example_connect_SRCS
   dlt860_client_example_connect.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_connect_SRCS} PROPERTIES LANGUAGE CXX)

ENDIF(WIN32)

add_executable(dlt860_client_example_connect
    ${dlt860_client_example_connect_SRCS}
)

target_link_libraries(dlt860_client_example_connect
    dlt860
)

