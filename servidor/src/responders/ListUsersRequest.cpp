#include "ListUsersRequest.hpp"


ListUsersRequest::ListUsersRequest(IDataService &service, ICodec &codec)
    : RequestHandler(service, codec)
{
}


ListUsersRequest::~ListUsersRequest(){
}



std::vector<char> ListUsersRequest::GetResponseData(){
    std::vector<char> v;
    v.push_back( 'L' );
    v.push_back( 'U' );
    v.push_back( 'R' );

    return v;
}
