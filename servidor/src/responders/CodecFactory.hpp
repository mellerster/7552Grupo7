#ifndef CODEC_FACTORY_H
#define CODEC_FACTORY_H

#include <memory>
#include "Codec.hpp"



/**
 * Factory para los distintos tipos de codecs.
 * */
class CodecFactory {
    public:
        CodecFactory();
        virtual ~CodecFactory();


        /** Codec para la autenticacion de usuarios.
         * */
        std::unique_ptr<Codec> BuildAutenticationCodec() const;

        
        /** Codec para el listado de usuarios.
         * */
        std::unique_ptr<Codec> BuildUsersListingCodec() const;

        
        /** Codec para los recursos no existentes.
         * */
        std::unique_ptr<Codec> BuildNotFoundCodec() const;
        
};


#endif

