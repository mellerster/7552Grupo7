#include "EditPerfilHandler.hpp"
#include "dtos/PerfilDTO.hpp"



EditPerfilHandler::EditPerfilHandler(IDataService &service) : RequestHandler(service) {
}


EditPerfilHandler::~EditPerfilHandler() {
}


Response EditPerfilHandler::GetResponseData() {
    // Editar perfil es una operacion de modificación de datos
    PerfilDTO dto( this->m_parsedParameters_ContentData );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    // Si hay una foto definida se almacena
    if (!dto.Foto.empty()) {
        this->m_dataService.ReplaceFoto( dto.Token, dto.Foto );
    }

    // So hay algún estado definido se almacena
    if (!dto.Estado.empty()) {
        this->m_dataService.ReplaceEstado( dto.Token, dto.Estado );
    }

    // Crea la respuesta
    Response resp( 200, "" );
    return resp;
}


