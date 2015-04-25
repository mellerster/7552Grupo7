cmake_minimum_required ( VERSION 2.8 )

#El nombre del ejecutable
project ( serverMensajerO )

enable_testing()

#Flags para los distintos tipos de compilacion
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall -Wpedantic -Wextra" )
set ( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG" )

set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -ggdb -O0 -fprofile-arcs -ftest-coverage" )
set ( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" )

if ( NOT CMAKE_BUILD_TYPE )
    message ( "=============================================" )
    message ( "== Por defecto siempre compilamos en Debug ==" )
    message ( "=============================================" )
    set ( CMAKE_BUILD_TYPE Debug )
endif ()


#Trata de cargar la libreria de RocksDB
find_library ( LIBROCKSDB rocksdb )
if ( NOT LIBROCKSDB )
    message( FATAL_ERROR "RocksDB library NOT found! You need to install them." )
endif()


#Agrega un nuevo target para generar los datos de coverage a partir de los tests
add_custom_target ( coverage
                    COMMAND lcov --quiet --capture --directory ${PROJECT_BINARY_DIR} --output-file coverage.info 
                    COMMAND lcov --quiet --remove coverage.info /usr/include/\\* --output-file coverage.info    
                    COMMAND genhtml coverage.info --output-directory CoverageReport
                  )


############################## Compilacion del programa ###########################################


#Permite que el compilador vea los includes de los subdirectorios
include_directories ( ${PROJECT_SOURCE_DIR}/libs/jsoncppLib )
include_directories ( ${PROJECT_SOURCE_DIR}/libs/mongooseLib )
include_directories ( ${PROJECT_SOURCE_DIR}/mangosta )
include_directories ( ${PROJECT_SOURCE_DIR}/responders )
include_directories ( ${PROJECT_SOURCE_DIR}/dataService )
include_directories ( ${LIBROCKSDB_SOURCE_DIR} )

#Donde buscar las librerias
add_subdirectory ( libs/jsoncppLib )
add_subdirectory ( libs/mongooseLib )
add_subdirectory ( mangosta )
add_subdirectory ( responders )
add_subdirectory ( tests )


#Define el ejecutable y linkea las librerias
add_executable ( ${PROJECT_NAME} MainServer.cpp ) 
target_link_libraries ( ${PROJECT_NAME} jsoncppLib ${LIBROCKSDB} requestHandlers mangostaServer )


