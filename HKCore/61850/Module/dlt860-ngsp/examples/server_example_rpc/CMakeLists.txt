include_directories(
   .
)

set(server_example_rpc_SRCS
   server_example_rpc.cpp
)

IF(WIN32)
	set_source_files_properties(${server_example_rpc_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(server_example_rpc
  ${server_example_rpc_SRCS}
)

target_link_libraries(server_example_rpc
   dlt860
   scd
)
