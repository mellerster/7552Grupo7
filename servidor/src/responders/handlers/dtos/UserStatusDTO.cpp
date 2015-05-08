#include "UserStatusDTO.hpp"
#include <string.h>



UserStatusDTO::UserStatusDTO() : BaseDTO(),
    Nombre(""), Estado(""), 
    UltimaActividadHora(""), UltimaActividadFecha(""),
    m_foto(nullptr)
{
}


UserStatusDTO::UserStatusDTO(Json::Value jData) : BaseDTO(jData), m_foto(nullptr) {
    this->Nombre = jData.get("Nombre", "").asString();
    this->Estado = jData.get("Estado", "").asString();

    this->UltimaActividadHora = jData.get("UltimaActividadHora", "").asString();
    this->UltimaActividadFecha = jData.get("UltimaActividadFecha", "").asString();

    const char* binData = jData.get("Foto", "").asCString();
    if ( strcmp(binData, "") != 0 ){
        size_t tam = strlen(binData);
        this->m_foto = new char[tam +1];

        strcpy(this->m_foto, binData);
    }
}


UserStatusDTO::~UserStatusDTO() {
    clearFoto();
}


void UserStatusDTO::clearFoto(){
    if (this->m_foto != nullptr){
        delete[] this->m_foto;
        this->m_foto = nullptr;
    }
}


void UserStatusDTO::CargarFotografia(const char* strData){
    clearFoto();

    size_t tam = strlen(strData);
    this->m_foto = new char[tam +1];

    strcpy(this->m_foto, strData);
}


const char* UserStatusDTO::GetFotografia() const {
    return this->m_foto;
}


Json::Value UserStatusDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Nombre"] = this->Nombre;
    j["Estado"] = this->Estado;
    j["UltimaActividadHora"] = this->UltimaActividadHora;
    j["UltimaActividadFecha"] = this->UltimaActividadFecha;

    if (this->m_foto != nullptr){
        j["Foto"] = std::string(this->m_foto);
    }

    return j;
}


