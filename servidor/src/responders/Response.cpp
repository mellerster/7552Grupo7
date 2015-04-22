#include "Response.hpp"



Response::Response(int statusCode, Json::Value jsonData) : m_status(statusCode) {
    // TODO: Procesar el JSON y cargarlo en el data container
}


Response::~Response(){
}


int Response::GetStatus() const{
    return this->m_status;
}



const void* Response::GetData() const{
    return nullptr;
}


size_t Response::GetDataLength() const{
    return 0;
}


