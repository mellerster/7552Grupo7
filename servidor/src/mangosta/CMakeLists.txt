

add_library ( mangostaServer MangostaServer.cpp )

#Esta libreria depende de mongoose
target_link_libraries ( mangostaServer mongooseLib requestHandlers )

