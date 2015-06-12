#include "LogoutRequest.hpp"

#include "dtos/LoginDTO.hpp"



LogoutRequest::LogoutRequest(IDataService &service) : RequestHandler(service) {
}


LogoutRequest::~LogoutRequest(){
}


Response LogoutRequest::GetResponseData(){
	// El logout seguramente sea un "DELETE", cuyos datos vienen como POST
    LoginDTO dto( this->m_parsedParameters_ContentData );

    this->m_dataService.EndSession( dto.Token );

    // Devuelve un mensaje de OK, no hay mas que hacer
    return Response( 200, "");
}




