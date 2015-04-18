#include "EmptyRequest.hpp"


EmptyRequest::EmptyRequest(IDataService &service, ICodec &codec)
    : RequestHandler(service, codec)
{
}


EmptyRequest::~EmptyRequest(){ }


std::vector<char> EmptyRequest::GetResponseData(){
    // TODO: Definir como responder...
    std::vector<char> v;
    v.push_back('0');

    return v;
}


