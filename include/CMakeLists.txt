file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

foreach ( file ${INCLUDE_FILES} )
    get_filename_component( dir ${file} DIRECTORY )
    install( FILES ${file} DESTINATION include/${dir} )
endforeach()