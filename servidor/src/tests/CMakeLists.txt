
#Compila los distintos testers
add_executable ( JsonTester
        MainTester.cpp 
        JsonTester.cpp 
        )
target_link_libraries ( JsonTester jsoncppLib )


add_executable ( MessageFactoryTester 
        MainTester.cpp 
        FactoryTester.cpp 
        mocks/MockedRequestHandler.cpp 
        )
target_link_libraries ( MessageFactoryTester requestHandlers )


add_executable ( CoreRequestHandlerTester 
        MainTester.cpp 
        RequestsHandlerTester.cpp 
        ResponseTester.cpp 
        AuthenticationHandlerTester.cpp
        mocks/MockedRequestHandler.cpp 
        )
target_link_libraries ( CoreRequestHandlerTester requestHandlers )


add_executable ( HandlerTester 
        MainTester.cpp 
        LoginHandlerTester.cpp
        ListUsersHandlerTester.cpp
        RegistrationHandlerTester.cpp
        CheckinHandlerTester.cpp
        EditProfileHandlerTester.cpp
        UserDataRequestTester.cpp
        ConversacionHandlerTester.cpp
        MensajesRequestHandlerTester.cpp
        )
target_link_libraries ( HandlerTester requestHandlers )


add_executable ( DTOTester 
        MainTester.cpp 
        DTOsTester.cpp 
        )
target_link_libraries ( DTOTester requestHandlers jsoncppLib )


add_executable ( RocaDBTester 
        MainLoggedTester.cpp 
        RocaDBUsuariosTester.cpp 
        RocaDBMensajesTester.cpp 
        SliceJsonTester.cpp 
        )
target_link_libraries ( RocaDBTester rocaDB jsoncppLib humblelogging )
                        

add_executable ( DataServiceTester 
        MainLoggedTester.cpp 
        SessionTester.cpp 
        UserDataDataServiceTester.cpp 
        ConversacionDataServiceTester.cpp
        MensajesDataServiceTester.cpp
        )
target_link_libraries ( DataServiceTester dataService humblelogging )


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
#add_test ( ALL_Core_Request_Handler_Tests CoreRequestHandlerTester )
#add_test ( ALL_Handler_Tests HandlerTester )
#add_test ( ALL_DTOs_Tests DTOTester )
#add_test ( ALL_RocaDB_Tests RocaDBTester )
#add_test ( ALL_DataServiceTests DataServiceTester )


#Hay que pasar el nombre de los tests cases para que cmake los corra por separado

#Json tests
add_test ( Test_Json_Strings JsonTester "Crear simple json con string" )
add_test ( Test_Json_int JsonTester "Crear simple json con int" )
add_test ( Test_Json_float JsonTester "Crear simple json con float" )
add_test ( Test_Json_array JsonTester "Crear simple json con array" )
add_test ( Test_Json_empty JsonTester "Descripcion de un JSON vacio" )
add_test ( Test_Json_RAW JsonTester "Cargar datos crudos en un JSON" )
add_test ( Test_Json_emptyArray JsonTester "JSON con array vacio" )


#DTO tests
add_test ( Test_DTO_BaseCodif DTOTester "BaseDTO - Codificar a JSON" )
add_test ( Test_DTO_BaseDecod DTOTester "BaseDTO - Decodificar desde JSON" )
add_test ( Test_DTO_UserStatCodif DTOTester "UserStatus - Codificar a JSON" )
add_test ( Test_DTO_UserStatDecod DTOTester "UserStatus - Decodificar desde JSON" )
add_test ( Test_DTO_ListUsersCodif DTOTester "ListUsers - Codificar a JSON" )
add_test ( Test_DTO_ListUsersDecod DTOTester "ListUsers - Decodificar desde JSON" )
add_test ( Test_DTO_LoginCodif DTOTester "Login - Codificar a JSON" )
add_test ( Test_DTO_LoginDecod DTOTester "Login - Decodificar desde JSON" )
add_test ( Test_DTO_RegistracionCodif DTOTester "Registration DTO - codificar a JSON" )
add_test ( Test_DTO_RegistracionDecod DTOTester "Registration DTO - decodificar desde JSON" )
add_test ( Test_DTO_PerfilCodif DTOTester "PerfilDTO - codificar a JSON" )
add_test ( Test_DTO_PerfilDecod DTOTester "PerfilDTO - deCodificar desde JSON" )
add_test ( Test_DTO_CheckinCodif DTOTester "CheckinDTO - codificar a JSON" )
add_test ( Test_DTO_CheckinDecod DTOTester "CheckinDTO - deCodificar desde JSON" )
add_test ( Test_DTO_MensajeCodif DTOTester "Mensaje DTO - codificar" )
add_test ( Test_DTO_MensajeDecod DTOTester "Mensaje DTO - De-codificar" )
add_test ( Test_DTO_ListMensajesCodif DTOTester "Lista de mensajes DTO - codificar" )
add_test ( Test_DTO_ListMensajesDecod  DTOTester "Lista de mensajes DTO - De-codificar" )
add_test ( Test_DTO_ConversacionesCodif DTOTester "Conversaciones - codificar en JSON" )
add_test ( Test_DTO_ConversacionesDecod DTOTester "Conversaciones - decodificar" )
add_test ( Test_DTO_ListConversacionesCodif DTOTester "Lista de conversaciones - codificar en JSON" )
add_test ( Test_DTO_ListConversacionesDecod DTOTester "Lista de conversaciones - decodificar" )
add_test ( Test_DTO_SendMensajeCodif DTOTester "Enviar mensaje - codif" )
add_test ( Test_DTO_SendMensajeDecod DTOTester "Enviar mensaje - decodif" )
add_test ( Test_DTO_BroadcastCodif DTOTester "Broadcast - codif" )
add_test ( Test_DTO_BroadcastDecod DTOTester "Broadcast - decodif" )


#Message factory tests
add_test ( Test_Factory_handlers_esperados MessageFactoryTester "Request handlers esperados" )
add_test ( Test_Factory_Autenticador MessageFactoryTester "Crear manejador de autenticacion" )
add_test ( Test_Factory_handler_NOesperado MessageFactoryTester "Request no esperado" )
add_test ( Test_mock_Interfaces MessageFactoryTester "Prueba simple de mockeo de interfaces" )
add_test ( Test_pointers MessageFactoryTester "Manejo de char pointers" )
add_test ( Test_Factory_MapImplementation MessageFactoryTester "Nueva inplemetación para la factory" )


#Core request handler tests
add_test ( Test_CoreHandler_Base CoreRequestHandlerTester "Fake test de Request handler base" )
add_test ( Test_CoreHandler_ParseQueryString CoreRequestHandlerTester "Request handler - Parseo de query string" )
add_test ( Test_CoreHandler_ParseContentData CoreRequestHandlerTester "Request handler - Parseo de JSON content data" )
add_test ( Test_CoreHandler_LoadParams CoreRequestHandlerTester "Probar la carga de parametros en el handler vacio" )
add_test ( Test_CoreHandler_ResponseBuild CoreRequestHandlerTester "Response tests - construccion" )
add_test ( Test_CoreHandler_Response CoreRequestHandlerTester "Response tests" )
add_test ( Test_CoreHandler_AutenticadorPOST CoreRequestHandlerTester "Autenticador de pedidos - POST" )
add_test ( Test_CoreHandler_AutenticadorGET CoreRequestHandlerTester "Autenticador de pedidos - GET" )


#Handlers tests
add_test ( Test_Handler_Login HandlerTester  "Testeo de login requests - Parseo de params" )
add_test ( Test_Handler_Logout HandlerTester "Handler de logout" )
add_test ( Test_Handler_ListUsers_resul HandlerTester "Testeo de list users requests - Manejo de resultados" )
add_test ( Test_Handler_ListUsers_Params HandlerTester "Testeo de list users requests - Parseo de params" )
add_test ( Test_Handler_AltaUsers HandlerTester "Testear Registracion de usuario" )
add_test ( Test_Handler_Checkin HandlerTester "Checkin handler" )
add_test ( Test_Handler_EditPerfil HandlerTester "EditPerfil handler" )
add_test ( Test_Handler_EditPerfil_params HandlerTester "User data request - parametros" )
add_test ( Test_Handler_ListConversaciones HandlerTester "Obtener el listado de conversaciones" )
add_test ( Test_Handler_Conversaciones HandlerTester "Conversacion handler" )
add_test ( Test_Handler_Broadcast HandlerTester "Testear broadcast de mensajes" )
add_test ( Test_Handler_SendMensajes HandlerTester "Testear envio de mensajes" )
add_test ( Test_Handler_MensajesRequest HandlerTester "Message request tests" )

  
#RocaDB tests
add_test ( Test_RocaDB_CreateDelete RocaDBTester "Crear y eliminar la base de datos" )
add_test ( Test_RocaDB_Usuario RocaDBTester "Crear y chequear usuario" )
add_test ( Test_RocaDB_DatosUsuario RocaDBTester "Guardar y recuperar datos del usuario" )
add_test ( Test_RocaDB_Conversaciones RocaDBTester "Pruebas de conversaciones" )
add_test ( Test_RocaDB_Mensajes RocaDBTester "Pruebas de mensaje" )
add_test ( Test_RocaDB_UltimosMensajes RocaDBTester "Recuperar los ultimos mensajes" )
add_test ( Test_RocaDB_Participantes RocaDBTester "Obtener los participantes de un conversacion" )
add_test ( Test_RocaDB_Remitente RocaDBTester "Obtener el remitente de un mensaje" )
add_test ( Test_RocaDB_JSON2Slice RocaDBTester "JSON to Slice - usando writers" )
add_test ( Test_RocaDB_JSON3Slice  RocaDBTester "JSON to Slice - usando stream y estilized writer" )
add_test ( Test_RocaDB_Slice2JSON RocaDBTester "Slice to JSON" )


#DataService tests
add_test ( Test_DataService_Session DataServiceTester "Testear manejor de session" )
add_test ( Test_DataService_NuevosUsuarios DataServiceTester "Registrar nuevos usuarios" )
add_test ( Test_DataService_EstadosUsuarios DataServiceTester "Manejar estados de usuarios" )
add_test ( Test_DataService_UsuariosConectados DataServiceTester "Probar listado de usuario conectados" )
add_test ( Test_DataService_FotoUsuario DataServiceTester "Probar modificar la foto del usuario" )
add_test ( Test_DataService_CheckinUsuario DataServiceTester "Probar checkin del usuario" )
add_test ( Test_DataService_PerfilUsuario DataServiceTester "Probar perfil del usuario" )
add_test ( Test_DataService_ListaConversaciones DataServiceTester "Listado de convesaciones" )
add_test ( Test_DataService_ConversacionUsuario DataServiceTester "Get conversacion por usuarios" )
add_test ( Test_DataService_ParticipantesConversacion DataServiceTester "Get participantes de una conversacion" )
add_test ( Test_DataService_ListMensajes DataServiceTester "Listado de mensajes" )
add_test ( Test_DataService_MensajesNoLeidos DataServiceTester "Obtener los mensajes no leidos" )
add_test ( Test_DataService_PostMensajes DataServiceTester "Postear un mensaje" )
add_test ( Test_DataService_BroadcastMensaje DataServiceTester "Enviar broadcast" )



