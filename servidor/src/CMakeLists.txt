cmake_minimum_required ( VERSION 2.8 )

#El nombre del ejecutable
project ( serverMensajerO )

enable_testing()

#Flags para los distintos tipos de compilacion
SET( CMAKE_CXX_FLAGS "-std=c++11 -pthread -Wall -Wpedantic -Wextra" )
SET( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS} "-g -ggdb -O0" )
SET( CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS} "-O3 -DNDEBUG" )

find_library ( LIBROCKSDB rocksdb )
if ( NOT LIBROCKSDB )
    MESSAGE( FATAL_ERROR "RocksDB library NOT found! You need to install them." )
endif()

#Permite que el compilador vea los includes de los subdirectorios
include_directories ( ${PROJECT_SOURCE_DIR}/libs/jsoncppLib )
include_directories ( ${PROJECT_SOURCE_DIR}/libs/mongooseLib )
include_directories ( ${PROJECT_SOURCE_DIR}/mangosta )
include_directories ( ${PROJECT_SOURCE_DIR}/responders )
include_directories ( ${LIBROCKSDB_SOURCE_DIR} )

#Donde buscar las librerias
add_subdirectory ( libs/jsoncppLib )
add_subdirectory ( libs/mongooseLib )
add_subdirectory ( mangosta )
add_subdirectory ( responders )
add_subdirectory ( tests )

#Define el ejecutable y linkea las librerias
set ( SRCs MainServer.cpp )
add_executable ( ${PROJECT_NAME} ${SRCs} ) 
target_link_libraries ( ${PROJECT_NAME} mangostaServer jsoncppLib ${LIBROCKSDB} requestHandlers )



