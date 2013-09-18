#add_custom_target(start_script ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/NMRVis_test.py
#                                           ${CMAKE_CURRENT_SOURCE_DIR}/start_NMRVis.bash )


#get_property(FAKE_PUT_FILE       TARGET fake_io_mod PROPERTY LOCATION)
get_property(NMR_VIS_FILE        TARGET nmr_gui_mod PROPERTY LOCATION)
get_property(SHIFT_CALC_FILE     TARGET shift_calc_mod PROPERTY LOCATION)
get_property(PDB_GEN_FILE        TARGET pdb_generate_mod PROPERTY LOCATION)
get_property(SELECTOR_MOD_FILE   TARGET selector_mod PROPERTY LOCATION)

set(CFG_NAME "nmr_mod_test")

configure_file(NMRVis_test.py.cfg NMRVis_test.py)
configure_file(start_NMRVis.bash.cfg start_NMRVis.bash @ONLY)

add_custom_target(start_script ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/NMRVis_test.py
                                           ${CMAKE_CURRENT_BINARY_DIR}/start_NMRVis.bash )
                                           
add_custom_command(TARGET start_script
                   POST_BUILD
                   COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/start_NMRVis.bash)
                                          
add_dependencies(start_script nmr_gui_mod fake_io_mod)