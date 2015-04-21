#include "AuthenticateUserRequest.hpp"


AuthenticateUserRequest::AuthenticateUserRequest(IDataService &service, std::unique_ptr<Codec> codec)
    : RequestHandler(service, codec)
{
}


AuthenticateUserRequest::~AuthenticateUserRequest(){
}


std::unique_ptr<Response> AuthenticateUserRequest::GetResponseData(){
    std::vector<char> v;
    v.push_back( 'A' );
    v.push_back( 'U' );
    v.push_back( 'R' );

    return v;
}




