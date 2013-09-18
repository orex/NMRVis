get_property(PDB_EXAMPLES_FOLDER       TARGET pdb_examples PROPERTY WORK_FOLDER)
get_property(SHIFT_CALC_PROJECT_FOLDER TARGET shiftx2      PROPERTY _EP_BINARY_DIR)

get_property(PDB_FRAMES_FOLDER TARGET   gromacs_traj PROPERTY PDB_FRAMES_FOLDER)
get_property(PDB_FRAMES_SUFFIX TARGET   gromacs_traj PROPERTY PDB_FRAMES_SUFFIX)

configure_file(proj_folders.h.cfg proj_folders.h)

#get_property(PDB_IO_SRC TARGET pdb_io PROPERTY _EP_SOURCE_DIR)
#set(PDB_IO_INCLUDE "${PDB_IO_SRC}/include")

get_property(COMMON_UTILS_SRC_FOLDER TARGET common_utils PROPERTY ROOT_SRC_FOLDER)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR} )

#add_subdirectory(fake_io_mod)
add_subdirectory(selector_mod)
add_subdirectory(pdb_generate_mod)
add_subdirectory(shift_calc_mod)
add_subdirectory(spectra_gui)
