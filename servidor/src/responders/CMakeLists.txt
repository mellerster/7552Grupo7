
#Los DTOs en el sub-subdirectorio
set ( SRC_DTOS 
        handlers/dtos/LoginDTO.cpp 
        handlers/dtos/UserStatusDTO.cpp 
        handlers/dtos/ListUsersDTO.cpp 
        handlers/dtos/BaseDTO.cpp
        handlers/dtos/RegistrationDTO.cpp
        handlers/dtos/PerfilDTO.cpp
        handlers/dtos/CheckinDTO.cpp
    )


#La lista de handlers en el subdirectorio
set ( SRC_HANDLERS 
        handlers/EmptyRequest.cpp 
        handlers/LoginRequest.cpp 
        handlers/ListUsersRequest.cpp 
        handlers/UserSignUpHandler.cpp
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

