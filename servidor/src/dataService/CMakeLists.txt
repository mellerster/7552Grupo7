
add_subdirectory ( db )


set ( SRC HardCodedDataService.cpp posicionaitor/Posicionador.cpp posicionaitor/Posicion.cpp )


add_library ( dataService ${SRC} )

target_link_libraries ( dataService db )


