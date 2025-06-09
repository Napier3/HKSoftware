
set(dlt860_client_example_model_SRCS
   client_example_model.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_model_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_model
    ${dlt860_client_example_model_SRCS}
)

target_link_libraries(dlt860_client_example_model
    dlt860
)
