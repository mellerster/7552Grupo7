
set ( DB_SRC RocaDB.cpp )


add_library ( db ${DB_SRC} )

target_link_libraries ( db
                        humblelogging
                        jsoncppLib 
                        ${LIBROCKSDB}
                      )

