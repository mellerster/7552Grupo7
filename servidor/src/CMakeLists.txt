cmake_minimum_required ( VERSION 2.6 )

#El nombre del ejecutable
project ( serverMensajerO )

#Permite que el compilador vea los includes de los subdirectorios
include_directories ( ${PROJECT_SOURCE_DIR}/mongooseLib )

#Donde buscar las librerias
add_subdirectory ( mongooseLib )

#Define el ejecutable
set ( SRCs server.cpp )
add_executable ( serverMensajerO ${SRCs} )

#Las librerias
target_link_libraries ( serverMensajerO mongooseLib )

