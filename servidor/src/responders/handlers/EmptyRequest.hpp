#ifndef EMPTY_REQUEST_H
#define EMPTY_REQUEST_H


#include "RequestHandler.hpp"
#include "Response.hpp"
#include "IDataService.hpp"



/** Representa un request nulo.
 * */
class EmptyRequest : public RequestHandler {
    public:
        EmptyRequest(IDataService &service);
        virtual ~EmptyRequest();

        virtual Response GetResponseData();
};


#endif

