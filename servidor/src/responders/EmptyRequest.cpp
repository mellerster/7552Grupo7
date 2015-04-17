#include "EmptyRequest.hpp"


EmptyRequest::EmptyRequest(IDataService &service, ICodec &codec)
    : RequestHandler(service, codec)
{
}


EmptyRequest::~EmptyRequest(){ }



void EmptyRequest::LoadParameters(std::string, const char*, size_t){ }


std::vector<char> EmptyRequest::GetResponseData(){
    std::vector<char> v;
    v.push_back('0');

    return v;
}


