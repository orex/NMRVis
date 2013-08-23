# FlowVR Middleware Library 
# Once done this will define#

# FLOWVR_FOUND  - system has FlowVR (TRUE only if all FlowVR sub components are found)
# FLOWVR_INCLUDE_DIR  - FlowVR  include directory
# FLOWVR_LIBRARY  - FlowVR  libraries

# And for each flowvr sub component  (base mod ftl utils plugd commands)

# FLOWVR_component_FOUND  - system has FlowVR component 
# FLOWVR_component_ INCLUDE_DIR  - FlowVR  component include directory
# FLOWVR_component_LIBRARY  - FlowVR  component libraries

SET(FLOWVR_PREFIX /home/kirill/projects/flowvr-suite-dev/install CACHE PATH "Path to FlowVR root")

SET(_components base mod ftl utils plugd commands)

SET(_depends_none)
SET(_depends_base none)
SET(_depends_mod base)
SET(_depends_ftl base)
SET(_depends_utils mod base)
SET(_depends_commands mod base ftl)
SET(_depends_launcher base utils ftl commands)


# build component dependency list
FOREACH(_component ${FLOWVR_FIND_COMPONENTS})
 IF(_depends_${_component})
  FOREACH(_depcomp ${_depends_${_component}})
   IF(NOT FLOWVR_FIND_REQUIRED_${_depcomp} AND _depends_${_depcomp})
    MESSAGE(STATUS "FlowVR: ${_component}  requires ${_depcomp}.")
    SET(FLOWVR_FIND_REQUIRED_${_depcomp} TRUE)
   ENDIF(NOT FLOWVR_FIND_REQUIRED_${_depcomp} AND _depends_${_depcomp})
  ENDFOREACH(_depcomp ${_depends_${_component}})
 ELSE(_depends_${_component})
  MESSAGE(SEND_ERROR "FlowVR: ${_component} is not a known FlowVR component")
 ENDIF(_depends_${_component})
ENDFOREACH(_component ${FLOWVR_FIND_COMPONENTS})


IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/buffer.h)
 SET(FLOWVR_base_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_base_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libflowvr-base.so)
 SET(FLOWVR_base_FOUND TRUE)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/buffer.h)
 IF(FLOWVR_FIND_REQUIRED_base)
   MESSAGE(FATAL_ERROR "FlowVR base  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_base)
 SET(FLOWVR_base_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/buffer.h)

IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/module.h)
 SET(FLOWVR_mod_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_mod_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libflowvr-mod.so)
 SET(FLOWVR_mod_FOUND TRUE)
 IF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_mod)
   MESSAGE(FATAL_ERROR "FlowVR mod found but required FlowVR base component not  found")
 ENDIF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_mod)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/module.h)
 IF(FLOWVR_FIND_REQUIRED_mod)
   MESSAGE(FATAL_ERROR "FlowVR mod  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_mod)
 SET(FLOWVR_mod_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/module.h)

IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/ftl/type.h)
 SET(FLOWVR_ftl_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_ftl_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libftlm.so)
 SET(FLOWVR_ftl_FOUND TRUE)
 IF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_ftl)
   MESSAGE(FATAL_ERROR "FlowVR ftl found but required FlowVR base component not  found")
 ENDIF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_ftl)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/ftl/type.h)
 IF(FLOWVR_FIND_REQUIRED_ftl)
   MESSAGE(FATAL_ERROR "FlowVR ftl  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_ftl)
 SET(FLOWVR_ftl_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/ftl/type.h)

IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/plugd/class.h)
 SET(FLOWVR_plugd_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_plugd_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libflowvr-plugd.so)
 SET(FLOWVR_plugd_FOUND TRUE)
 IF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_plugd)
   MESSAGE(FATAL_ERROR "FlowVR plugd found but required FlowVR base component not  found")
 ENDIF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_plugd)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/plugd/class.h)
 IF(FLOWVR_FIND_REQUIRED_plugd)
   MESSAGE(FATAL_ERROR "FlowVR plugd  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_plugd)
 SET(FLOWVR_plugd_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/plugd/class.h)

IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/telnet.h)
 SET(FLOWVR_commands_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_commands_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libflowvr-commands.so)
 SET(FLOWVR_commands_FOUND TRUE)
 IF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_commands)
   MESSAGE(FATAL_ERROR "FlowVR commands  found but required FlowVR base component not  found")
 ENDIF(NOT FLOWVR_base_FOUND AND FLOWVR_FIND_REQUIRED_commands)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/telnet.h)
 IF(FLOWVR_FIND_REQUIRED_commands)
   MESSAGE(FATAL_ERROR "FlowVR commands  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_commands)
 SET(FLOWVR_commands_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/telnet.h)


IF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/utils/filepath.h)
 SET(FLOWVR_utils_INCLUDE_DIR /home/kirill/projects/flowvr-suite-dev/install/include)
 SET(FLOWVR_utils_LIBRARY /home/kirill/projects/flowvr-suite-dev/install/lib/libflowvr-utils.so)
 SET(FLOWVR_utils_FOUND TRUE)
ELSE(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/utils/filepath.h)
 IF(FLOWVR_FIND_REQUIRED_utils)
   MESSAGE(FATAL_ERROR "FlowVR utils  not  found")
 ENDIF(FLOWVR_FIND_REQUIRED_utils)
 SET(FLOWVR_utils_FOUND FALSE)
ENDIF(EXISTS /home/kirill/projects/flowvr-suite-dev/install/include/flowvr/utils/filepath.h)


SET(FLOWVR_INCLUDE_DIR ${FLOWVR_base_INCLUDE_DIR} 
                       ${FLOWVR_mod_INCLUDE_DIR} 
                       ${FLOWVR_ftl_INCLUDE_DIR} 
                       ${FLOWVR_plugd_INCLUDE_DIR} 
                       ${FLOWVR_commands_INCLUDE_DIR} 
                       ${FLOWVR_utils_INCLUDE_DIR}   )
                       
SET(FLOWVR_LIBRARY ${FLOWVR_base_LIBRARY} 
                   ${FLOWVR_mod_LIBRARY} 
                   ${FLOWVR_ftl_LIBRARY} 
                   ${FLOWVR_plugd_LIBRARY} 
                   ${FLOWVR_commands_LIBRARY} 
                   ${FLOWVR_utils_LIBRARY} )

SET (FLOWVR_FOUND TRUE)




