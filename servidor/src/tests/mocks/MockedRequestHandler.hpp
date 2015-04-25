#ifndef MOCKED_REQUEST_HANDLER_H
#define MOCKED_REQUEST_HANDLER_H

#include "json/json.h"
#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"


class MockedRequestHandler : public RequestHandler {
    public:
        MockedRequestHandler(IDataService &service);
        virtual ~MockedRequestHandler();

        virtual Response GetResponseData();

        Json::Value GetContentJSON() const;
        Json::Value GetQueryStringJSON() const;
};


#endif

