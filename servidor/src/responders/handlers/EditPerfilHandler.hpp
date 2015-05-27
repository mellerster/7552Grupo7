#ifndef EDIT_PERFIL_HANDLER_H
#define EDIT_PERFIL_HANDLER_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Reemplaza los datos del perfil actual por el nuevo.
 * */
class EditPerfilHandler : public RequestHandler {
    public:
        EditPerfilHandler(IDataService &service);
        virtual ~EditPerfilHandler();


        virtual Response GetResponseData();
};


#endif

