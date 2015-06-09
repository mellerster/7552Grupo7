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


std::string DataService::GetCheckinLocations(double latitud, double longitud) {
/*    if (!IsTokenActive(token)) {
        HL_ERROR( logger, "Se trató de obtener la ubicación de un usuario no loggeado." );
        return "";
    }*/
	return "";
    // TODO: Analizar; deberia sacar la ubicación de un usuario dado o es un sevicio general?

}


void DataService::ReplaceCheckinLocation(unsigned int token, double latitud, double longitud) {
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




