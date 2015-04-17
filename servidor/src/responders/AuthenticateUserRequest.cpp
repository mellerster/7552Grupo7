#include "AuthenticateUserRequest.hpp"


AuthenticateUserRequest::AuthenticateUserRequest(IDataService &service, ICodec &codec)
    : RequestHandler(service, codec)
{
}


AuthenticateUserRequest::~AuthenticateUserRequest(){
}


std::vector<char> AuthenticateUserRequest::GetResponseData(){
    std::vector<char> v;
    v.push_back( 'A' );
    v.push_back( 'U' );
    v.push_back( 'R' );

    return v;
}




