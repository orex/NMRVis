include_directories( ${CMAKE_CURRENT_BINARY_DIR}
                     ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                     ${Boost_INCLUDE_DIRS} )
    
add_executable(fake_io_mod main.cpp )
target_link_libraries(fake_io_mod ${FLOWVR_base_LIBRARY} 
                                  ${FLOWVR_mod_LIBRARY} 
                                  ${Boost_LIBRARIES} )

