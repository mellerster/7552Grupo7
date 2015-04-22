#include "RequestHandler.hpp"


RequestHandler::RequestHandler(IDataService &service)
    : m_dataService(service)
{
}


RequestHandler::~RequestHandler(){
}


void RequestHandler::LoadParameters(const char* queryString, const char* data, std::size_t data_len){
    if (queryString != nullptr){
        // TODO: Pärsear el query string
        this->m_parsedParameters_QueryString;
    }

    if (data_len > 0 && data != nullptr){
        // TODO: Parsear la data POST
        this->m_parsedParameters_ContentData;
    }
}


