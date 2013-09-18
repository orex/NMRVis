set(SHIFTX2_LATEST_FILE "shiftx2-v107-linux-20120106.tgz")
set(BLAST_LATEST_FILE "blast-2.2.22-x64-linux.tar.gz")
set(SHIFTX2_EXAMPLE_FILE "shiftx2-testset-June2011.tgz")
set(ESBTL10_BETA_FILE "esbtl10-beta.tar.bz2")

include(DownloadFileCheck.in)

obtain_file(http://www.shiftx2.ca/download/${SHIFTX2_LATEST_FILE} 
            ${CMAKE_CURRENT_SOURCE_DIR}/${SHIFTX2_LATEST_FILE} 
            47bd11f00c824967738f72a02387b47eafc60a10697aa157e27163f2edbf9927)

add_custom_target(blast ALL)

set(BLAST_DATA_FOLDER "")
            
if( (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64") AND (UNIX) )
  #Obtaining legacy blast
  obtain_file(ftp://ftp.ncbi.nlm.nih.gov/blast/executables/release/2.2.22/${BLAST_LATEST_FILE}
              ${CMAKE_CURRENT_SOURCE_DIR}/${BLAST_LATEST_FILE}
              4fa41716bb5616d811824569f7514c6ed86a3d82a3a73fc089f264f8d0d99d02)

  add_custom_target(blast_x86_64 
                    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/blast-2.2.22)
                    
  add_dependencies(blast blast_x86_64) 
                    
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/blast-2.2.22
                     COMMAND tar -xf ${CMAKE_CURRENT_SOURCE_DIR}/${BLAST_LATEST_FILE} -C ${CMAKE_CURRENT_BINARY_DIR} )
  unset(BLAST_DATA_FOLDER)
  set(BLAST_DATA_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/blast-2.2.22")

endif()

#Obtaining example pdbs
obtain_file(http://www.shiftx2.ca/download/${SHIFTX2_EXAMPLE_FILE} 
            ${CMAKE_CURRENT_SOURCE_DIR}/${SHIFTX2_EXAMPLE_FILE} 
            83860b18ec82e5db142a783f7a12acaa687b3e104e83f99890173bba0add3317)
            
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-testset-June2011/PDB-testset
                  COMMAND tar -xf ${CMAKE_CURRENT_SOURCE_DIR}/${SHIFTX2_EXAMPLE_FILE} -C ${CMAKE_CURRENT_BINARY_DIR})
            
add_custom_target(pdb_examples ALL
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-testset-June2011/PDB-testset)
                  
set_property(TARGET pdb_examples 
             PROPERTY WORK_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-testset-June2011/PDB-testset)
             
             
#Obtain PDB read/write library
#obtain_file(http://downloads.sourceforge.net/project/esbtl/ESBTL-1.0-beta01.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fesbtl%2Ffiles%2F%3Fsource%3Dnavbar&ts=1378650432&use_mirror=optimate
#            ${CMAKE_CURRENT_SOURCE_DIR}/${ESBTL10_BETA_FILE}
#            c42e0b3c3e11f1782032be70fc3e8da816774a49ca4fd628e69e79cda7b7bb1d)

include(ExternalProject)

ExternalProject_Add(shiftx2
                    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/shiftx2
                    URL ${CMAKE_CURRENT_SOURCE_DIR}/${SHIFTX2_LATEST_FILE} 
                    CONFIGURE_COMMAND ""
                    BUILD_IN_SOURCE 1
                    INSTALL_COMMAND "") 

if(NOT (BLAST_DATA_FOLDER STREQUAL ""))
  ExternalProject_Add_Step(shiftx2 setup_blast
                           COMMAND rm -rf <SOURCE_DIR>/shifty3/blast && mv ${BLAST_DATA_FOLDER} <SOURCE_DIR>/shifty3/blast
                           COMMENT "Installing BLAST..."
                           DEPENDEES download
                           DEPENDERS configure)
endif()                           
                        
add_dependencies(shiftx2 blast)

#ExternalProject_Add(pdb_io
#                    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/pdb_io
#                    URL ${CMAKE_CURRENT_SOURCE_DIR}/${ESBTL10_BETA_FILE} 
#                    CONFIGURE_COMMAND ""
#                    BUILD_COMMAND ""
#                    INSTALL_COMMAND "") 


                 
#add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-v107-linux
#                   COMMAND tar -xf ${CMAKE_CURRENT_SOURCE_DIR}/${SHIFTX2_LATEST_FILE} -C ${CMAKE_CURRENT_BINARY_DIR} )

#installing shiftx2
#add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-v107-linux/modules/shiftx/shiftx
#                   COMMAND make
#                   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-v107-linux 
#                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shiftx2-v107-linux )

