include_directories(
   .
)

set(server_example_update_report_SRCS
   server_example_update_report.cpp
)

IF(WIN32)
	set_source_files_properties(${server_example_update_report_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(server_example_update_report
  ${server_example_update_report_SRCS}
)

target_link_libraries(server_example_update_report
   dlt860
   scd
)
