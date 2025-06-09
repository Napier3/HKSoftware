
set(dlt860_client_example_brcb_report_multiple_op_SRCS
   dlt860_client_example_brcb_report_multiple_op.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_brcb_report_multiple_op_SRCS} PROPERTIES LANGUAGE CXX)

ENDIF(WIN32)

add_executable(dlt860_client_example_brcb_report_multiple_op
    ${dlt860_client_example_brcb_report_multiple_op_SRCS}
)

target_link_libraries(dlt860_client_example_brcb_report_multiple_op
    dlt860
)

