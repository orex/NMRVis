include_directories( ${CMAKE_CURRENT_BINARY_DIR} 
                     ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                     ${Boost_INCLUDE_DIRS} 
                     ${COMMON_UTILS_SRC_FOLDER}
                     ${PDB_IO_INCLUDE})
    
add_executable(shift_calc_mod   shift_calc_mod_main.cpp 
                                nmr_shift_data_parse.cpp
                                ${COMMON_UTILS_SRC_FOLDER}/others/file_utils.cpp 
                                ${COMMON_UTILS_SRC_FOLDER}/others/string_utils.cpp )

target_link_libraries(shift_calc_mod ${FLOWVR_base_LIBRARY} 
                                     ${FLOWVR_mod_LIBRARY} 
                                     ${Boost_LIBRARIES} )

add_dependencies(shift_calc_mod pdb_io common_utils)