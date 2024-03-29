#include "Response.hpp"
#include <iostream>



Response::Response(int statusCode, Json::Value jsonData) : 
    m_status(statusCode), 
    m_ssContainer(std::stringstream::binary | std::stringstream::in | std::stringstream::out) 
{
    this->m_ssContainer << jsonData;
}


Response::Response(const Response& r) : 
    m_status(r.m_status), 
    m_ssContainer(std::stringstream::binary | std::stringstream::in | std::stringstream::out) 
{
    this->m_ssContainer << r.m_ssContainer.rdbuf();
}


Response::~Response(){ }



int Response::GetStatus() const{
    return this->m_status;
}



const char* Response::GetData() {
    size_t tam = GetDataLength();
    char* buff = new char[tam +1];  // Lugar para el null terminator

    this->m_ssContainer.read(buff, tam);
    buff[tam] = '\0';

    return buff;
}


size_t Response::GetDataLength(){
    this->m_ssContainer.seekg(0, std::ios::end);
    size_t tam = this->m_ssContainer.tellg();
    this->m_ssContainer.seekg(0, std::ios::beg);

    return tam;
}


