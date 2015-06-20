#include "AuthenticationHandler.hpp"

#include <memory>
#include <string>
#include <utility>



void AuthenticationHandler::LoadParameters(const char*, const char*, size_t){
    // Pärsea el query string que viene con los GET
    if (queryString != nullptr){   
        this->m_parsedParameters_QueryString = parseQueryStringData( queryString );
    }

    // Parsea la data de tipo POST
    if (data_len > 0 && data != nullptr){
        this->m_parsedParameters_ContentData = parseContentData( data, data_len );
    }
}


bool AuthenticationHandler::IsResourceAccesible(std::string httpVerb, std::string httpURI){
    // TODO: Validar que el token este activo para todos los recursos, excepto el login.
    return true;
}


Json::Value AuthenticationHandler::parseContentData(const char* data, size_t dataLen) const {
    // Usa un builder para parsear los datos
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> ptrJsonBuilder( builder.newCharReader() );

    // Apunta al final de los datos
    const char* dataEnd = &data[dataLen];

    Json::Value jData;
    ptrJsonBuilder->parse( data, dataEnd, &jData, nullptr );

    return jData;
}



Json::Value AuthenticationHandler::parseQueryStringData(std::string qStr) const {
    Json::Value jTemp;

    // Se guarda la posicion anterior para poder calcular la longitud del substring
    size_t prevPos = 0;
    size_t posSeparator = -1;   // Permite que los valores se inicializen bien en cada iteracion.

    do {
        // Se avanza en la iteracion
        prevPos = posSeparator +1;
        posSeparator = qStr.find('&', prevPos);  // No se toman en cuenta los ya encontrados

        // Extrae el substring que corresponde a un par clave-valor del JSON y los separa
        std::string sTemp = qStr.substr(prevPos, posSeparator - prevPos);
        std::pair<std::string, std::string> kv = toKeyValuePair( sTemp );

        // Agrega el resultado al JSON
        jTemp[kv.first] = kv.second;

    } while (posSeparator != std::string::npos);

    return jTemp;
}


std::pair<std::string, std::string> AuthenticationHandler::toKeyValuePair(std::string keyVal) const {
    size_t pos = keyVal.find('=');

    std::string k = keyVal.substr(0, pos);
    std::string v = keyVal.substr(pos +1);

    return std::make_pair(k, v);
}



