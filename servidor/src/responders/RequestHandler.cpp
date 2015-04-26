#include "RequestHandler.hpp"
#include <vector>
#include <string>
#include <utility>



RequestHandler::RequestHandler(IDataService &service)
    : m_dataService(service)
{
}


RequestHandler::~RequestHandler(){
}


void RequestHandler::LoadParameters(const char* queryString, const char* data, std::size_t data_len){
    // Pärsea el query string
    if (queryString != nullptr){   
        this->m_parsedParameters_QueryString = parseQueryStringData( queryString );
    }

    if (data_len > 0 && data != nullptr){
        // TODO: Parsear la data POST
        this->m_parsedParameters_ContentData;
    }
}


Json::Value RequestHandler::parseQueryStringData(std::string qStr) const {
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


std::pair<std::string, std::string> RequestHandler::toKeyValuePair(std::string keyVal) const {
    size_t pos = keyVal.find('=');

    std::string k = keyVal.substr(0, pos);
    std::string v = keyVal.substr(pos +1);

    return std::make_pair(k, v);
}



