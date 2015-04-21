#include "ListUsersRequest.hpp"


ListUsersRequest::ListUsersRequest(IDataService &service, std::unique_ptr<Codec> codec)
    : RequestHandler(service, codec)
{
}


ListUsersRequest::~ListUsersRequest(){
}



std::unique_ptr<Response> ListUsersRequest::GetResponseData(){
    std::vector<char> v;
    v.push_back( '{' );
    v.push_back( '"' );
    v.push_back( 'D' );
    v.push_back( '"' );
    v.push_back( ':' );
    v.push_back( '"' );
    v.push_back( 'U' );
    v.push_back( '"' );
    v.push_back( '}' );

    return v;
}
