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
    bool ok = this->m_rocaDB.LoadUserUbicacion( userID, lati, longi );
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
    userProf.latitud = lati;
    userProf.longitud = longi;
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
    bool resul = this->m_rocaDB.LoadUserUbicacion(userID, latitud, longitud);
    if (!resul) {
        HL_ERROR( logger, "Falló la obtención de la ubicación del usuario." );
        return "";
    }

    // Se extrae la descripción del lugar mas cercano a las coordenadas del usuario.
    return this->m_posicionador.getLugarMasCercano( std::stod(latitud), std::stod(longitud) );
}


void DataService::ReplaceCheckinLocation(unsigned int token, double latitud, double longitud) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se intentó guardar la ubicación de un usuario no conectado" );
        return;
    }

    std::string userID = this->m_sessionHandler.GetAssociatedUserID( token );
    bool resul = this->m_rocaDB.StoreUserUbicacion( userID, std::to_string(latitud), std::to_string(longitud) );

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

