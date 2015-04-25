#include "MockedRequestHandler.hpp"



MockedRequestHandler::MockedRequestHandler(IDataService &service) : RequestHandler(service){ }

MockedRequestHandler::~MockedRequestHandler() { }


Response MockedRequestHandler::GetResponseData(){
    Response r(0, "");
    return r;
}


Json::Value MockedRequestHandler::GetContentJSON() const{
    return this->m_parsedParameters_ContentData;
}


Json::Value MockedRequestHandler::GetQueryStringJSON() const{
    return this->m_parsedParameters_QueryString;
}

