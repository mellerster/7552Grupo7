#include "DataService.hpp"



HUMBLE_LOGGER( logger, "default" );


DataService::DataService(IDB& dbRef, IPosicionador& posInator) 
    : m_rocaDB(dbRef), m_posicionador(posInator)
{
    this->m_rocaDB.Open("rockingDB.bin");
    HL_INFO( logger, "Iniciado el servicio de datos" );
}


DataService::~DataService() {
    this->m_rocaDB.Close();
    HL_INFO( logger, "Terminado el servicio de datos" );
}


//-----------------------------------------------------------------------------


bool DataService::IsTokenActive(unsigned int tok) {
    return this->m_sessionHandler.IsSessionTokenValid( tok );
}


unsigned int DataService::StartSession(std::string nombreUsuario, std::string password) {
    // Chequea que sea un usuario registrado
    bool userRegistrado = this->m_rocaDB.AutheticateUser( nombreUsuario, password );
    if (!userRegistrado) {
        HL_WARN( logger, "Intento de iniciar session de un usuario no registrado" );
        return 0;
    }

    // Registra la nueva session
    unsigned int newToken = this->m_sessionHandler.StartSession( nombreUsuario );
    HL_INFO( logger, "Nueva session iniciada" );

    return newToken;
}


void DataService::EndSession(unsigned int token) {
    // Se intenta borrar
    bool exito = this->m_sessionHandler.EndSession( token );

    if (exito) {
        HL_INFO( logger, "Sesión terminada" );

    } else {
        HL_WARN( logger, "Se intentó terminar una sesión inexistente" );
    }
}


bool DataService::RegisterNewUser(std::string nombreUsuario, std::string password) {
    bool existe = this->m_rocaDB.ExistsUser( nombreUsuario );
    if (existe) {
        HL_WARN( logger, "Se intentó registrar un usuario que ya existia" );
        return false;
    }

    bool creado = this-m_rocaDB.CreateUser( nombreUsuario, password );

    if (creado) {
        HL_INFO( logger, "Nueva usuario registrado" );

    } else {
        HL_WARN( logger, "Falló la registración de un nuevo usuario" );
    }

    return creado;
}


//-----------------------------------------------------------------------------


std::vector<UserStatus> DataService::ListActiveUsers() {
    std::vector<UserStatus> lista;

    // Recorre la lista de tokens
    for ( unsigned int tok : this->m_sessionHandler.GetAllActiveSessionTokens() ) {
        UserStatus us;
        us.Nombre = this->m_sessionHandler.GetAssociatedUserID( tok );  // UserID
        us.Estado = this->m_sessionHandler.GetAssociatedUserState( tok );   // Estado

        this->m_rocaDB.LoadUserFoto(us.Nombre, us.Foto);    // Carga la foto

        lista.push_back( us );
    }

    return lista;
}


UserProfile DataService::GetUserProfile(unsigned int token, std::string userID) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de obtener el perfil por un usuario no loggeado." );
        return UserProfile();
    }

    if (!this->m_rocaDB.ExistsUser( userID ) ){
        HL_ERROR( logger, "Se trató de obtener el perfil de un usuario no existente." );
        return UserProfile();
    }

    // Se recuperan las coordenadas de la ubicación del usuario
    std::string lati = "";
    std::string longi = "";
    std::string fechaHora = "";
    bool ok = this->m_rocaDB.LoadUserUbicacion( userID, lati, longi, fechaHora );
    if (!ok) {
        HL_ERROR( logger, "Hubo un error al recuperar la ubicación del usuario" );
        return UserProfile();
    }

    // Se recupera la descripcion de la ubicación del usuario
    std::string descrip = "";
    if (!lati.empty() && !longi.empty()) {
	    descrip = this->m_posicionador.getLugarMasCercano( std::stod(lati), std::stod(longi) );
    }

    // Se recupera la foto del usuario
    std::string foto = "";
    ok = this->m_rocaDB.LoadUserFoto( userID, foto );
    if (!ok) {
        HL_ERROR( logger, "Hubo un error al recuperar la foto del usuario" );
        return UserProfile();
    }

    // Se arma la respuesta
    UserProfile userProf;
    userProf.Nombre = userID;
    userProf.Foto = foto;
    userProf.Latitud = lati;
    userProf.Longitud = longi;
    userProf.FechaHora = fechaHora;
    userProf.Ubicacion = descrip;

    userProf.Estado = this->m_sessionHandler.GetAssociatedUserStateByUserID( userID );

    return userProf;
}


std::string DataService::GetCheckinLocations(unsigned int token) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de obtener la ubicación de un usuario no loggeado." );
        return "";
    }

    // A partir del token se obtiene el userID
    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );

    // A partir del userID se obtiene la ultima coordenada del usuario.
    std::string latitud = "";
    std::string longitud = "";
    std::string fechaHora = "";
    bool resul = this->m_rocaDB.LoadUserUbicacion( userID, latitud, longitud, fechaHora );
    if (!resul) {
        HL_ERROR( logger, "Falló la obtención de la ubicación del usuario." );
        return "";
    }

    // Se extrae la descripción del lugar mas cercano a las coordenadas del usuario.
    return this->m_posicionador.getLugarMasCercano( std::stod(latitud), std::stod(longitud) );
}


void DataService::ReplaceCheckinLocation(unsigned int token, double latitud, double longitud, std::string fechaHora) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se intentó guardar la ubicación de un usuario no conectado" );
        return;
    }

    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
    bool resul = this->m_rocaDB.StoreUserUbicacion( userID, std::to_string(latitud), std::to_string(longitud), fechaHora );

    if (!resul) {
        HL_ERROR( logger, "Ocurrió un error al intentar guardar la ubicación del usuario." );
    }
}


void DataService::ReplaceFoto(unsigned int token, std::string foto) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de modificar la foto de un usuario no loggeado." );
        return;
    }

    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
    bool resul = this->m_rocaDB.StoreUserFoto( userID, foto );

    if (!resul) {
        HL_ERROR( logger, "Ocurrio un error al guardar la foto de un usuario" );
    }
}


void DataService::ChangeEstado(unsigned int token, std::string estado) {
    bool exito = this->m_sessionHandler.SetAssociatedUserState( token, estado );
    if (!exito) {
        HL_ERROR( logger, "Ocurrio un error cambiar el estado de un usuario" );
    }
} 


//-----------------------------------------------------------------------------


std::vector<Conversacion> DataService::ListActiveConversations(unsigned int token) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de recuperar conversaciones de un usuario no loggeado." );
        return std::vector<Conversacion>();
    }

    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
    std::vector<unsigned int> conversaciones = this->m_rocaDB.GetConversaciones( userID );

    std::vector<Conversacion> resul;
    for ( unsigned int convID : conversaciones ) {

        Conversacion c;
        c.IDConversacion = convID;
        //Obtiene los participantes de la conversación
        c.Participantes = this->m_rocaDB.GetParticipantesConversacion(convID);

        // Obtiene todos los mensajes de una conversación
        std::vector<unsigned int> msgs = this->m_rocaDB.GetMensajesConversacion( convID );

        if ( !msgs.empty() ) {
            // Compara el ultimo mensaje recibido con el ultimo mensaje de la conversación
            unsigned int ultimoMsgRecibido = this->m_rocaDB.GetIDUltimoMensaje( userID, convID );
            unsigned int ultimoMsgEnviado = msgs.back();
            std::string usuarioUltimoMensaje = this->m_rocaDB.GetRemitente( ultimoMsgRecibido );

            c.UltimoMensaje = usuarioUltimoMensaje + ": " + this->m_rocaDB.GetMensaje( ultimoMsgEnviado );
            c.UltimoMensajeLeido = (ultimoMsgRecibido == ultimoMsgEnviado);
        }

        resul.push_back( c );
    }

    return resul;
}


unsigned int DataService::GetConversacion(unsigned int token, std::string IDdestinatario) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de crear/obtener una conversación para un usuario no loggeado." );
        return 0;
    }

    // El user ID del creador de la conversación
    std::string IDfuente = this->m_sessionHandler.GetAssociatedUserID( token );

    // Se obtienen todas las conversaciones de ambos usuarios
    std::vector<unsigned int> convs_1 = this->m_rocaDB.GetConversaciones( IDfuente );
    std::vector<unsigned int> convs_2 = this->m_rocaDB.GetConversaciones( IDdestinatario );

    // Se busca una conversación en común
    unsigned int convID = GetInterseccion( convs_1, convs_2 );

    if (convID == 0) {
        std::vector<std::string> vecIDs;
        vecIDs.push_back( IDfuente );
        vecIDs.push_back( IDdestinatario );

        HL_INFO( logger, "Se crea una nueva conversación" );
        return this->m_rocaDB.CreateNewConversacion( vecIDs );

    } else {
        HL_INFO( logger, "Se encontró una conversación en común" );
        return convID;
    }
}


unsigned int DataService::GetInterseccion( std::vector<unsigned int> v1, std::vector<unsigned int> v2 ) {
    for ( unsigned int i : v1 ) {
        for ( unsigned int j : v2 ) {
            if (i == j) {
                return i;   // Encontrado
            }
        }
    }

    return 0;   // No encontrado
}

std::vector<std::string> DataService::GetParticipantes(unsigned int token, unsigned int convID) {
	std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
	std::vector<std::string> participantes =this->m_rocaDB.GetParticipantesConversacion( convID );
	unsigned int posUsuario = -1;
	for (unsigned int i = 0; i < participantes.size(); i++) {
		if(participantes[i].compare(userID) == 0){
			posUsuario = i;
			break;
		}
	}
	participantes.erase(participantes.begin()+posUsuario);
	return participantes;
}

std::vector<Mensaje> DataService::GetMensajes(unsigned int token, unsigned int convID) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de recuperar mensajes de un usuario no loggeado." );
        return std::vector<Mensaje>();
    }

    // Se recuperan los ID de todos los mensajes de la conversación
    std::vector<unsigned int> lMensajeIDs = this->m_rocaDB.GetMensajesConversacion( convID );

    std::vector<Mensaje> vecMsjs;
    for ( unsigned int msgID : lMensajeIDs ) {
        Mensaje m;
        m.Texto = this->m_rocaDB.GetMensaje( msgID );
        m.IDRemitente = this->m_rocaDB.GetRemitente( msgID );

        vecMsjs.push_back( m );
    }

    return vecMsjs;
}

bool DataService::AgregarMensaje(unsigned int token, unsigned int IDConversacion , std::string texto) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Trató de enviar un mensaje un usuario no loggeado." );
        return false;
    }
    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
    
    if(this->m_rocaDB.AgregarMensaje(userID, IDConversacion, texto ) == 0) {
    	HL_ERROR( logger, "Se intento enviar un mensaje pero este no se grabo correctamente." );
    	return false;
    }
    return true;
}



