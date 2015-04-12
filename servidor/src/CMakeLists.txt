cmake_minimum_required ( VERSION 2.8 )

#El nombre del ejecutable
project ( serverMensajerO )

enable_testing()

#Flags para los distintos tipos de compilacion
SET( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wpedantic -Wextra" )
SET( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS} "-g -ggdb -O0" )
SET( CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS} "-O3 -DNDEBUG" )

#Permite que el compilador vea los includes de los subdirectorios
include_directories ( ${PROJECT_SOURCE_DIR}/libs/jsoncppLib )
include_directories ( ${PROJECT_SOURCE_DIR}/libs/mongooseLib )

#Donde buscar las librerias
add_subdirectory ( libs/jsoncppLib )
add_subdirectory ( libs/mongooseLib )
add_subdirectory ( tests )

#Define el ejecutable y linkea las librerias
set ( SRCs server.cpp )
add_executable ( ${PROJECT_NAME} ${SRCs} ) 
target_link_libraries ( ${PROJECT_NAME} mongooseLib jsoncppLib )



