#include "ListUsersRequest.hpp"


ListUsersRequest::ListUsersRequest(IDataService &service, ICodec &codec)
    : RequestHandler(service, codec)
{
}


ListUsersRequest::~ListUsersRequest(){
}



std::vector<char> ListUsersRequest::GetResponseData(){
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
