include_directories(
   .
)

set(server_example_update_single_SRCS
   server_example_update_single.cpp
)

IF(WIN32)
	set_source_files_properties(${server_example_update_single_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(server_example_update_single
  ${server_example_update_single_SRCS}
)

target_link_libraries(server_example_update_single
   dlt860
   scd
)
