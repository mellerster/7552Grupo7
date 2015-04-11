cmake_minimum_required ( VERSION 2.6 )

#El nombre del ejecutable
project ( serverMensajerO )

#Flags para compilacion
SET( CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic" )


#Permite que el compilador vea los includes de los subdirectorios
include_directories ( ${PROJECT_SOURCE_DIR}/libs/jsoncppLib )
include_directories ( ${PROJECT_SOURCE_DIR}/libs/mongooseLib )

#Donde buscar las librerias
add_subdirectory ( libs/jsoncppLib )
add_subdirectory ( libs/mongooseLib )

#Define el ejecutable
set ( SRCs server.cpp )
add_executable ( serverMensajerO ${SRCs} )

#Las librerias
target_link_libraries ( serverMensajerO mongooseLib jsoncppLib )


# 
#
MESSAGE( STATUS "current CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

# the compiler flags for compiling C++ sources 
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE} )

# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug) 
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )



