#Agrega la libreria de prueba
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/sumadorLib )
add_subdirectory ( sumadorLib )

#Compila los distintos testers
add_executable ( SumadorTester MainTester.cpp SumadorTests.cpp )
target_link_libraries ( SumadorTester sumadorLib )

add_executable ( JsonTester MainTester.cpp JsonTester.cpp )
target_link_libraries ( JsonTester jsoncppLib )

add_executable ( MessageFactoryTester MainTester.cpp FactoryTester.cpp )
target_link_libraries ( MessageFactoryTester requestHandlers )


############################ Tests ##########################

message ( "*** NOTA: Para ver el detalle de los tests correr los ejecutables en: ${CMAKE_CURRENT_BINARY_DIR} ***" )

#Corre todos los tests, pero los toma como si solo fuera uno
#add_test ( All_Sumador_Tests SumadorTester )
#add_test ( ALL_Json_Tests JsonTester )
add_test ( ALL_Factory_Tests MessageFactoryTester )

#Hay que pasar el nombre de los tests cases para que cmake los corra por separado
add_test ( Test_Positivos SumadorTester "Sumar enteros positivos" )
add_test ( Test_Negativos SumadorTester "Sumar enteros negativos" )
add_test ( Test_Ceros SumadorTester "Sumar ceros" )

add_test ( Test_Json_Strings JsonTester "Crear simple json con string" )
add_test ( Test_Json_Ints JsonTester "Crear simple json con int" )
add_test ( Test_Json_Float JsonTester "Crear simple json con float" )
add_test ( Test_Json_Array JsonTester "Crear simple json con array" )



