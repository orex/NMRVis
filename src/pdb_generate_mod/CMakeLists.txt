find_package(Boost 1.46 REQUIRED COMPONENTS filesystem system)

include_directories( ${CMAKE_CURRENT_BINARY_DIR}
                     ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                     ${Boost_INCLUDE_DIRS} 
                     ${COMMON_UTILS_SRC_FOLDER})
    
add_executable(pdb_generate_mod pdb_gen_mod_main.cpp 
                                  ${COMMON_UTILS_SRC_FOLDER}/others/file_utils.cpp 
                                  ${COMMON_UTILS_SRC_FOLDER}/others/rnd_utils.cpp)

target_link_libraries(pdb_generate_mod ${FLOWVR_base_LIBRARY} 
                                       ${FLOWVR_mod_LIBRARY} 
                                       ${Boost_LIBRARIES} )
                                         
add_dependencies(pdb_generate_mod gromacs_traj common_utils)

