find_package(Qt4)

if(QT4_FOUND)
  find_package(Qwt)
  if(QWT_FOUND)
    include(${QT_USE_FILE} )

    set(SRC_NMRVIS_GUI_CODE nmr_plot.cpp c_flowvr_event_loop.cpp) 
    
    set(SRC_NMRVIS_GUI_CODE ${SRC_NMRVIS_GUI_CODE} ${CMAKE_SOURCE_DIR}/libs/utils/math_utils.cpp ) 
    
    
    set(UIS nmr_plot.ui)
    set(MOC_HEADERS nmr_plot.h c_flowvr_event_loop.h)

    qt4_wrap_ui(UI_HEADERS ${UIS})
    qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})
    
    include_directories(${CMAKE_SOURCE_DIR}/libs/utils/
                        ${CMAKE_CURRENT_BINARY_DIR} ${QWT_INCLUDE_DIR} 
                        ${FLOWVR_base_INCLUDE_DIR} ${FLOWVR_mod_INCLUDE_DIR}
                        ${Boost_INCLUDE_DIRS} )
    
    add_executable(nmr_module main.cpp
                              ${SRC_NMRVIS_GUI_CODE} 
                              ${UI_HEADERS}
                              ${MOC_SRCS}
                              ${QT_RES_RCC} )

    set(NMRVIS_GUI_LIBS ${QT_LIBRARIES} ${QWT_LIBRARY}
                         ${FLOWVR_base_LIBRARY} 
                         ${FLOWVR_mod_LIBRARY}
                         ${Boost_LIBRARIES} )

    target_link_libraries(nmr_module ${NMRVIS_GUI_LIBS})
  endif()  
endif()

add_subdirectory(fake_io_mod)