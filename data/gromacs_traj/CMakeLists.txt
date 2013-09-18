find_program(GROMACS_GROMPP grompp)
if(NOT GROMACS_GROMPP )
  message(SEND_ERROR "Gromacs is not found. Check PATH variable")
endif()  

set(MOL_SEED_NAME 1UBQ)
set(PDB_FRAMES_FOLDER pdb_frames)

add_custom_target(gromacs_traj 
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${MOL_SEED_NAME}_md.trr)


file(COPY ${MOL_SEED_NAME}.pdb DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



#configure_file(gen_traj.bash.cfg gen_traj.bash @ONLY)
file(COPY gen_traj.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${MOL_SEED_NAME}.pdb
#                          ${CMAKE_CURRENT_BINARY_DIR}/gen_traj.bash
#                   COMMAND cp -av ${CMAKE_CURRENT_SOURCE_DIR}/${MOL_SEED_NAME}.pdb ${CMAKE_CURRENT_BINARY_DIR}/ && cp -av ${CMAKE_CURRENT_SOURCE_DIR}/gen_traj.bash ${CMAKE_CURRENT_BINARY_DIR}/ )
                  
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${MOL_SEED_NAME}_md.trr
                   COMMAND ./gen_traj.bash ${MOL_SEED_NAME} ${PDB_FRAMES_FOLDER}
                   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${MOL_SEED_NAME}.pdb
                           ${CMAKE_CURRENT_BINARY_DIR}/gen_traj.bash)

set_property(TARGET   gromacs_traj
             PROPERTY PDB_FRAMES_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/${PDB_FRAMES_FOLDER})
             
set_property(TARGET   gromacs_traj
             PROPERTY PDB_FRAMES_SUFFIX ${MOL_SEED_NAME})
             
             