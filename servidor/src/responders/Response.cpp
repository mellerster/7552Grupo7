#include "Response.hpp"



Response::Response(int statusCode) : m_status(statusCode) {
}


Response::~Response(){
}


int Response::GetStatus() const{
    return this->m_status;
}



const void* Response::GetData() const{
    return *(this->m_dataContainer[0])
}


size_t Response::GetDataLength() const{
    return this->m_dataContainer.size();
}


