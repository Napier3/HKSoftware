
set(dlt860_client_example_dataset_SRCS
   dlt860_client_example_dataset.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_dataset_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_dataset
    ${dlt860_client_example_dataset_SRCS}
)

target_link_libraries(dlt860_client_example_dataset
    dlt860
)
