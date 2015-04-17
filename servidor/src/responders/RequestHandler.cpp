#include "RequestHandler.hpp"


RequestHandler::RequestHandler(IDataService &service, ICodec &codec)
    : m_codec(codec), m_dataService(service)
{
}


RequestHandler::~RequestHandler(){
}


void RequestHandler::LoadParameters(std::string queryString, const char* data, size_t data_len){
}


