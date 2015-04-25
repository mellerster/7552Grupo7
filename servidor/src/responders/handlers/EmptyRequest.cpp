#include "EmptyRequest.hpp"


EmptyRequest::EmptyRequest(IDataService &service) : RequestHandler(service) {
}


EmptyRequest::~EmptyRequest() {
}


Response EmptyRequest::GetResponseData(){
    Response resp (404, "");
    return resp;
}


