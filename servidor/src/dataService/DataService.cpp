#include "DataService.hpp"

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
    std::default_random_engine eng;
    std::uniform_int_distribution<unsigned int> rndGen;
    std::string salt = std::to_string( rndGen(eng) );

    std::hash<std::string> hasher;
    unsigned int token = hasher(salt + nomUsuario);

    return token;
}


//-----------------------------------------------------------------------------


std::vector<UserStatus> DataService::ListActiveUsers() {
    return std::vector<UserStatus>();
}


std::string DataService::GetCheckinLocations(double latitud, double longitud) {
    return "";
}


void DataService::ReplaceCheckinLocation(unsigned int token, double latitud, double longitud) {
}


void DataService::ReplaceFoto(unsigned int token, std::string foto) {
}


void DataService::ReplaceEstado(unsigned int token, std::string estado) {
}




