#ifndef BROADCAST_HANDLER_H
#define BROADCAST_HANDLER_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Dados la longitud y latitud devuelve una descripción del punto conocido mas cercano.
 * */
class BroadcastHandler : public RequestHandler {
    public:
        BroadcastHandler(IDataService &service);
        virtual ~BroadcastHandler();


        virtual Response GetResponseData();
};


#endif

