
#Compila los distintos testers
add_executable ( JsonTester MainTester.cpp JsonTester.cpp )
target_link_libraries ( JsonTester jsoncppLib )

add_executable ( MessageFactoryTester MainTester.cpp FactoryTester.cpp )
target_link_libraries ( MessageFactoryTester requestHandlers )

add_executable ( RequestHanderTester MainTester.cpp RequestsTester.cpp ResponseTester.cpp)
target_link_libraries ( RequestHanderTester requestHandlers )

add_executable ( DTOTester MainTester.cpp DTOsTester.cpp )
target_link_libraries ( DTOTester requestHandlers jsoncppLib )


############################ Tests ##########################

message ( "********************************************************************" )
message ( "** NOTA: " )
message ( "**      Para ver el detalle de los tests correr los ejecutables en: " )
message ( "** " )
message ( "** ${CMAKE_CURRENT_BINARY_DIR} " )
message ( "********************************************************************" )

#Corre todos los tests, pero los toma como si solo fuera uno
#add_test ( ALL_Json_Tests JsonTester )
#add_test ( ALL_MessageFactory_Tests MessageFactoryTester )
add_test ( ALL_Request_Handler_Tests RequestHanderTester )
add_test ( ALL_DTOs_Tests DTOTester )

#Hay que pasar el nombre de los tests cases para que cmake los corra por separado

#Json tests
add_test ( Test_Json_Strings JsonTester "Crear simple json con string" )
add_test ( Test_Json_Ints JsonTester "Crear simple json con int" )
add_test ( Test_Json_Float JsonTester "Crear simple json con float" )
add_test ( Test_Json_Array JsonTester "Crear simple json con array" )

#Message factory tests
add_test ( Test_Factory_Creacion_Handlers MessageFactoryTester "Request handlers esperados" )
add_test ( Test_Factory_Handlers_invalidos MessageFactoryTester "Request no esperado" )
add_test ( Test_Factory_Mocking MessageFactoryTester "Prueba simple de mockeo de interfaces" )
add_test ( Test_Factory_Memoria MessageFactoryTester "Manejo de char pointers" )
  


