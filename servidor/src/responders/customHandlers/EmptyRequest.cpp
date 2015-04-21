#include "EmptyRequest.hpp"


EmptyRequest::EmptyRequest(IDataService &service, std::unique_ptr<Codec> codec)
    : RequestHandler(service, codec)
{
}


EmptyRequest::~EmptyRequest(){ }


std::unique_ptr<Response> EmptyRequest::GetResponseData(){
    std::vector<char> v;

    return v;
}


