#include "HardCodedDataService.hpp"
#include <random>


bool HardCodedDataService::Open(){
    return true;
}


void HardCodedDataService::Close(){
}


unsigned int HardCodedDataService::startSession(std::string nombreUsuario, std::string password){
    if (nombreUsuario == "" || password == ""){
        return 0;
    }

    std::default_random_engine eng;
    std::uniform_int_distribution<unsigned int> tokenGenerator;

    return tokenGenerator( eng );
}


bool HardCodedDataService::RegisterNewUser(std::string nombreUsuario, std::string password) {
    if (nombreUsuario == "" || password == ""){
        return false;

    } else {
        return true;
    }
}


bool HardCodedDataService::IsTokenActive(unsigned int){
    return true;
}


std::vector<UserStatus> HardCodedDataService::ListActiveUsers(){
    UserStatus user;
    user.Nombre = "pepe";
    user.Estado = "Testing";
    user.UltimaActividadHora = "00:00";
    user.UltimaActividadFecha = "2015/12/31";
    user.Foto = this->m_fotoBin;

    std::vector<UserStatus> v;
    v.push_back( user );

    return v;
}



