

add_library ( mangostaServer mangostaServer.cpp )

#Esta libreria depende de mongoose
target_link_libraries ( mangostaServer mongooseLib )

