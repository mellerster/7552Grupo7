#include "LogoutRequest.hpp"

#include "dtos/LoginDTO.hpp"



LogoutRequest::LogoutRequest(IDataService &service) : RequestHandler(service) {
}


LogoutRequest::~LogoutRequest(){
}


Response LogoutRequest::GetResponseData(){
	//TODO: Realizar logout

    Response resp( 200, "");
    return resp;
}




