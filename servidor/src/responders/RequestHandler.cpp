#include "RequestHandler.hpp"


RequestHandler::RequestHandler(IDataService &service, std::unique_ptr<Codec> codec)
    : m_codec(codec), m_dataService(service)
{
}


RequestHandler::~RequestHandler(){
}


void RequestHandler::LoadParameters(const char* queryString, const char* data, std::size_t data_len){
}


