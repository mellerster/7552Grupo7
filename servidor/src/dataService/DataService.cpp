#include "DataService.hpp"

#include <chrono>
#include <random>
#include <functional>


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
    size_t cant = this->m_tokenContainer.count( tok );
    return (cant == 1);
}


unsigned int DataService::StartSession(std::string nombreUsuario, std::string password) {
    // Chequea que sea un usuario registrado
    bool userRegistrado = this->m_rocaDB.AutheticateUser( nombreUsuario, password );
    if (!userRegistrado) {
        HL_WARN( logger, "Intento de iniciar session de un usuario no registrado" );
        return 0;
    }

    // Si el usuario ya tiene una session, la elimina
    unsigned int currToken = ExisteSessionUsuario(nombreUsuario);
    if (currToken != 0) {
        this->m_tokenContainer.erase( currToken );
    }

    // Registra la nueva session
    unsigned int newToken = GenerateTokenUnico(nombreUsuario);
    this->m_tokenContainer[newToken] = nombreUsuario;

    HL_INFO( logger, "Nueva session iniciada" );

    return newToken;
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


unsigned int DataService::ExisteSessionUsuario(std::string nombreUsuario) const {
    for (auto it = this->m_tokenContainer.cbegin(); it != this->m_tokenContainer.cend(); ++it) {
        if ( it->second == nombreUsuario ) {
            return it->first;
        }
    }

    return 0;
}


unsigned int DataService::GenerateTokenUnico(std::string nomUsuario) const {
    // Un valor random le da sabor a nuestro token
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generador(seed);

    std::uniform_int_distribution<unsigned int> rndGen;
    std::string salt = std::to_string( rndGen(generador) );

    std::hash<std::string> hasher;
    unsigned int token = hasher(salt + nomUsuario);

    return token;
}


//-----------------------------------------------------------------------------


std::vector<UserStatus> DataService::ListActiveUsers() {
    std::vector<UserStatus> lista;

    // Hay que ver todos los usuario conectados
    for (auto it = this->m_tokenContainer.cbegin(); it != this->m_tokenContainer.cend(); ++it) {
        UserStatus us;
        us.Nombre = it->second;
        us.Estado = "Conectado";

        this->m_rocaDB.LoadUserFoto(us.Nombre, us.Foto);    // Carga la foto

        lista.push_back( us );
    }

    return lista;
}


UserProfile DataService::GetUserProfile(unsigned int token) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de obtener el perfil de un usuario no loggeado." );
        return UserProfile();
    }

    // Se recupera el nombre del usuario
    std::string userID = this->m_tokenContainer[token];

    // Se recuperan las coordenadas de la ubicación del usuario
    std::string lati = "";
    std::string longi = "";
    bool ok = this->m_rocaDB.LoadUserUbicacion( userID, lati, longi );
    if (!ok) {
        HL_ERROR( logger, "Hubo un error al recuperar la ubicación del usuario" );
        return UserProfile();
    }

    // Se recupera la descripcion de la ubicación del usuario
    std::string descrip = this->m_posicionador.getLugarMasCercano( std::stod(lati), std::stod(longi) );

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

    return userProf;
}


std::string DataService::GetCheckinLocations(unsigned int token) {
    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de obtener la ubicación de un usuario no loggeado." );
        return "";
    }

    // A partir del token se obtiene el userID
    std::string userID = this->m_tokenContainer[token];

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

    std::string userID = this->m_tokenContainer[token];
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

    std::string userID = this->m_tokenContainer[token];
    bool resul = this->m_rocaDB.StoreUserFoto( userID, foto );

    if (!resul) {
        HL_ERROR( logger, "Ocurrio un error al guardar la foto de un usuario" );
    }
}


void DataService::ReplaceEstado(unsigned int, std::string) {
    // TODO: Agregar soporte para esta funcionalidad en la base de datos...
}




