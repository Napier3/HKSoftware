
set(dlt860_client_example_urcb_report_SRCS
   client_example_urcb_report.cpp
)

IF(WIN32)
    set_source_files_properties(${dlt860_client_example_urcb_report_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(dlt860_client_example_urcb_report
    ${dlt860_client_example_urcb_report_SRCS}
)

target_link_libraries(dlt860_client_example_urcb_report
    dlt860
)
