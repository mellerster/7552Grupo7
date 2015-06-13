#include "SessionStateHandler.hpp"

#include <chrono>
#include <random>
#include <functional>



unsigned int SessionStateHandler::StartSession(std::string userID) {
    DeleteUserSession( userID );    // Si existe borra la sesión pre-existente del usuario

    unsigned int newToken = GenerateUniqueToken( userID );

    // Inicialmente el usuario se guarda como conectado
    this->m_tokenContainer[ newToken ] = std::make_pair( userID, "C" );

    return newToken;
}


bool SessionStateHandler::EndSession(unsigned int token) {
    unsigned int cantBorrada = this->m_tokenContainer.erase( token );

    return (cantBorrada == 1);
}


bool SessionStateHandler::DeleteUserSession(std::string userID) {
    for (auto it = this->m_tokenContainer.begin(); it != this->m_tokenContainer.end(); ++it) {
        if ( it->second.first == userID ) {
            this->m_tokenContainer.erase( it );
            return true;    // UserID encontrada y borrada.
        }
    }

    return false;   // No se encontró el UserID dado.
}


bool SessionStateHandler::IsSessionTokenValid(unsigned int token) const {
    unsigned int cant = this->m_tokenContainer.count( token );
    return (cant == 1);
}


std::vector<unsigned int> SessionStateHandler::GetAllActiveSessionTokens() const {
    std::vector<unsigned int> vec;

    for (auto it = this->m_tokenContainer.cbegin(); it != this->m_tokenContainer.cend(); ++it) {
        vec.push_back( it->first );
    }

    return vec;
}


std::string SessionStateHandler::GetAssociatedUserID(unsigned int token) const {
    return this->m_tokenContainer.at( token ).first;
}


std::string SessionStateHandler::GetAssociatedUserState(unsigned int token) const {
    return this->m_tokenContainer.at( token ).second;
}


std::string SessionStateHandler::GetAssociatedUserStateByUserID(std::string userID) const {

    for (auto it = this->m_tokenContainer.cbegin(); it != this->m_tokenContainer.cend(); ++it) {
        // El "value" del par contiene el userID y el estado
        std::pair<std::string, std::string> value = it->second;

        // Compara el userID del "value" con el parametro
        if ( value.first == userID ) {
            return value.second;    // Devuelve el estado asociado al usuario
        }
    }

    // El usuario no tiene sesión, esta desconectado
    return "D";
}


bool SessionStateHandler::SetAssociatedUserState(unsigned int token, std::string newEstado) {
    bool existe = IsSessionTokenValid( token );
    if (!existe) {
        return false;
    }

    // Solo "C" y "D" son los estados validos, y "C" es por defecto
    std::string stat = "C";
    if ( newEstado == "D" ) {
        stat = "D";
    }

    // En el segundo miembre del "value" se encuentra el estado
    this->m_tokenContainer[ token ].second = stat;
    return true;
}


unsigned int SessionStateHandler::GenerateUniqueToken(std::string userID) const {
    // Un valor random le da sabor a nuestro token
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generador(seed);

    std::uniform_int_distribution<unsigned int> rndGen;
    std::string salt = std::to_string( rndGen(generador) );

    std::hash<std::string> hasher;
    unsigned int token = hasher(salt + userID);

    return token;
}


