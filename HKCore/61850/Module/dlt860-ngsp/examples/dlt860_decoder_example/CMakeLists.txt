
set(decoder_example_SRCS
   decoder_example.cpp
)

IF(WIN32)
    set_source_files_properties(${decoder_example_SRCS} PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(decoder_example
    ${decoder_example_SRCS}
)

target_link_libraries(decoder_example
    dlt860
)
