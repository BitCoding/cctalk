file(GLOB_RECURSE files *.c *.h)


set(CCTALK_SHARED_SRCS
  ${files}
)
set(CCTALK_SHARED_LIBS)

add_library(cctalk SHARED ${CCTALK_SHARED_SRCS})
install(TARGETS cctalk DESTINATION lib )

# 
# target_link_libraries(cctalk_shared ${CCTALK_SHARED_LIBS})
