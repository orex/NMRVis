find_package(Qt4)

if(QT4_FOUND)
  find_package(Qwt)
  if(QWT_FOUND)
    include(${QT_USE_FILE} )

    set(SRC_NMRVIS_GUI_CODE nmr_plot.cpp c_flowvr_event_loop.cpp nmr_shift_data_process.cpp) 
    
    set(SRC_NMRVIS_GUI_CODE ${SRC_NMRVIS_GUI_CODE} 
                            ${COMMON_UTILS_SRC_FOLDER}/science/math_utils.cpp  
                            ${COMMON_UTILS_SRC_FOLDER}/others/TStatisticCollect.cpp)
    
    set(UIS nmr_plot.ui)
    set(MOC_HEADERS nmr_plot.h c_flowvr_event_loop.h)

    qt4_wrap_ui(UI_HEADERS ${UIS})
    qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})
    
    include_directories(${COMMON_UTILS_SRC_FOLDER}
                        ${CMAKE_CURRENT_BINARY_DIR} ${QWT_INCLUDE_DIR} 
                        ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                        ${Boost_INCLUDE_DIRS} )
    
    add_executable(nmr_gui_mod main.cpp
                              ${SRC_NMRVIS_GUI_CODE} 
                              ${UI_HEADERS}
                              ${MOC_SRCS}
                              ${QT_RES_RCC} )

    set(NMRVIS_GUI_LIBS ${QT_LIBRARIES} ${QWT_LIBRARY}
                         ${FLOWVR_base_LIBRARY} 
                         ${FLOWVR_mod_LIBRARY}
                         ${Boost_LIBRARIES} )

    target_link_libraries(nmr_gui_mod ${NMRVIS_GUI_LIBS})
    add_dependencies(nmr_gui_mod common_utils)
  endif()  
endif()