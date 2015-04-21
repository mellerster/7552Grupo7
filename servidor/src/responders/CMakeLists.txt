
set ( SRC_HANDLERS customHandlers/AuthenticateUserRequest.cpp customHandlers/EmptyRequest.cpp customHandlers/ListUsersRequest.cpp )

set ( SRCs
        RequestHandlerFactory.cpp 
        CodecFactory.cpp

        RequestHandler.cpp 
        RequestData.cpp
        ResultData.cpp
        Response.cpp 
    )

add_library ( requestHandlers ${SRCs} ${SRC_HANDLERS} )




