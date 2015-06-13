
# Donde se encuentra la libreria
add_subdirectory ( rocaDB )

# Los archivos fuente que forman esta libreria
set ( SRC 
        DataService.cpp 
        helpers/SessionStateHandler.cpp 
        helpers/Posicionador.cpp 
        helpers/Posicion.cpp 
    )


# Compila los fuentes y los linkea con otras librerias
add_library ( dataService ${SRC} )
target_link_libraries ( dataService rocaDB  )


