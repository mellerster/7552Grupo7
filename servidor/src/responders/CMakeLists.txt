
#Los DTOs en el sub-subdirectorio
set ( SRC_DTOS 
        handlers/dtos/LoginDTO.cpp 
        handlers/dtos/UserStatusDTO.cpp 
        handlers/dtos/ListUsersDTO.cpp 
        handlers/dtos/BaseDTO.cpp
        handlers/dtos/RegistrationDTO.cpp
        handlers/dtos/PerfilDTO.cpp
        handlers/dtos/CheckinDTO.cpp
        handlers/dtos/BroadcastDTO.cpp        
        handlers/dtos/ConversationDTO.cpp
        handlers/dtos/ListConversationsDTO.cpp
        handlers/dtos/MensajeDTO.cpp
        handlers/dtos/ListaMensajesDTO.cpp
    )


#La lista de handlers en el subdirectorio
set ( SRC_HANDLERS 
        handlers/EmptyRequest.cpp 
        handlers/LoginRequest.cpp 
        handlers/LogoutRequest.cpp
        handlers/ListUsersRequest.cpp 
        handlers/UserSignUpHandler.cpp
        handlers/CheckinHandler.cpp
        handlers/BroadcastHandler.cpp
        handlers/UserDataRequest.cpp
        handlers/EditPerfilHandler.cpp
        handlers/ListConversationsRequest.cpp
        handlers/SendMessageHandler.cpp
        handlers/MessageRequest.cpp
        handlers/ConversationRequest.cpp
    )


#La lista de clases en el directorio actual
set ( SRCS 
        RequestHandlerFactory.cpp 
        Response.cpp 
        RequestHandler.cpp
        AuthenticationHandler.cpp
    )


#Compila la libreria
add_library ( requestHandlers ${SRCS} ${SRC_HANDLERS} ${SRC_DTOS} )

#Se necesita linkear contra JsonCpp
target_link_libraries ( requestHandlers jsoncppLib )

