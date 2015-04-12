#El nombre del ejecutable que contiene los tests
project ( SumadorTester )

#La referencia a la libreria a testear
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/sumadorLib )
add_subdirectory ( sumadorLib )

#Compila el test runner
set ( SRCs mainTester.cpp sumadorTests.cpp )
add_executable ( ${PROJECT_NAME} ${SRCs} ) 
target_link_libraries ( ${PROJECT_NAME} sumadorLib )


############################ Tests ##########################

message ( "*** NOTA: Para ver el detalle de los tests ejecutar: ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}" )

#Corre todos los tests, pero los toma como si solo fuera uno
#add_test ( All_Tests ${PROJECT_NAME} )

#Hay que pasar el nombre de los tests cases para que cmake los corra por separado
add_test ( Test_Positivos ${PROJECT_NAME} "Sumar enteros positivos" )
add_test ( Test_Negativos ${PROJECT_NAME} "Sumar enteros negativos" )
add_test ( Test_Ceros ${PROJECT_NAME} "Sumar ceros" )



