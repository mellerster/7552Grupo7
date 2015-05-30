
# Los archivos fuente
set ( DB_SRC RocaDB.cpp )

# Compilar la libreria
add_library ( rocaDB ${DB_SRC} )

# Linkear con las siguientes librerias
target_link_libraries ( rocaDB
                        humblelogging
                        jsoncppLib 
                        ${LIBROCKSDB}
                      )

