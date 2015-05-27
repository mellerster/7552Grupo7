#ifndef CHECKIN_HANDLER_H
#define CHECKIN_HANDLER_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Dados la longitud y latitud devuelve una descripción del punto conocido mas cercano.
 * */
class CheckinHandler : public RequestHandler {
    public:
        CheckinHandler(IDataService &service);
        virtual ~CheckinHandler();


        virtual Response GetResponseData();
};


#endif

