#include "CodecFactory.hpp"


CodecFactory::CodecFactory() { }
CodecFactory::~CodecFactory() { }



std::unique_ptr<ICodec> CodecFactory::BuildAutenticationCodec() const{
    std::unique_ptr<ICodec> ptr;
    return ptr;
}


std::unique_ptr<ICodec> CodecFactory::BuildUsersListingCodec() const{
    std::unique_ptr<ICodec> ptr;
    return ptr;
}


std::unique_ptr<ICodec> CodecFactory::BuildNotFoundCodec() const{
    std::unique_ptr<ICodec> ptr;
    return ptr;
}


