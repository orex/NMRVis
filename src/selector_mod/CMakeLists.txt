include_directories( ${COMMON_UTILS_SRC_FOLDER}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                     ${Boost_INCLUDE_DIRS} )
    
add_executable(selector_mod selector_mod_main )
target_link_libraries(selector_mod ${FLOWVR_base_LIBRARY} 
                                   ${FLOWVR_mod_LIBRARY} 
                                   ${Boost_LIBRARIES} )

