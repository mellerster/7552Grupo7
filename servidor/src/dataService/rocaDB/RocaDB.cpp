#include "RocaDB.hpp"



HUMBLE_LOGGER( logger, "default" );



RocaDB::~RocaDB() {
    Close();
}


void RocaDB::Open(std::string fileName) {
    rocksdb::Options opt;
    opt.create_if_missing = true;

    rocksdb::Status st = rocksdb::DB::Open( opt, fileName, &this->m_rockdb );

    if (!st.ok()) {
        HL_FATAL( logger, "Falló la apertura de la base de datos\n" + st.ToString() );
        throw std::runtime_error( st.ToString() );
    }
}


void RocaDB::Close() {
    if (this->m_rockdb != nullptr) {
        delete this->m_rockdb;

        this->m_rockdb = nullptr;
    }
}


//------------------- Usuarios ----------------------------


bool RocaDB::ExistsUser(std::string userID) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val);

    return !st.IsNotFound();
}


bool RocaDB::CreateUser(std::string userID, std::string password) {
    Json::Value jUser;
    jUser["Password"] = password;

    // Si existia algo lo sobre-escribe
    rocksdb::Status st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetUserKey(userID), JsonToSlice(jUser) );
    return st.ok();
}


bool RocaDB::AutheticateUser(std::string userID, std::string password) {
    std::string userData;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &userData );

    if (st.IsNotFound()) {
        return false;   // No existe el usuario
    }

    Json::Value jUser = SliceToJson( userData );
    std::string storedPass = jUser["Password"].asString();

    return (storedPass == password);
}


bool RocaDB::StoreUserUbicacion(std::string userID, std::string latitud, std::string longitud, std::string fechaHora) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val );

    if (st.IsNotFound()) {
        return false;   // No existe el usuario
    }

    Json::Value jUser = SliceToJson( val );
    jUser["Latitud"] = latitud;
    jUser["Longitud"] = longitud;
    jUser["Fecha-Hora"] = fechaHora;

    st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetUserKey(userID), JsonToSlice(jUser) );

    return st.ok();
}


bool RocaDB::LoadUserUbicacion(std::string userID, std::string &latitud, std::string &longitud, std::string &fechaHora) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val);

    if (st.IsNotFound()) {
        return false;   // No existe el usuario
    }

    Json::Value jUser = SliceToJson( val );
    latitud = jUser.get("Latitud", "").asString();
    longitud = jUser.get("Longitud", "").asString();
    fechaHora = jUser.get("Fecha-Hora", "").asString();

    return true;
}


bool RocaDB::StoreUserFoto(std::string userID, std::string foto) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val);

    if (st.IsNotFound()) {
        return false;   // No existe el usuario
    }

    Json::Value jUser = SliceToJson( val );
    jUser["Foto"] = foto;

    st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetUserKey(userID), JsonToSlice(jUser) );

    return st.ok();
}


bool RocaDB::LoadUserFoto(std::string userID, std::string &foto) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val );

    if (st.IsNotFound()) {
        return false;   // No existe el usuario
    }

    Json::Value jUser = SliceToJson( val );
    foto = jUser.get("Foto", "").asString();

    return true;
}


std::string RocaDB::GetUserKey(std::string userID) const {
    return std::string( "U/" + userID );
}


//------------------------- Mensajes ----------------------------


unsigned int RocaDB::CreateNewConversacion(std::vector<std::string> listaUsuarios) {
    // Se genera un ID para la conversación
    unsigned int convID = GenerateNewID();

    // Se crea la conversación
    Json::Value jConv;
    jConv["IDMensajes"] = Json::Value( Json::arrayValue );  // Array vacio

    // Almacena todos los participantes de la conversacion
    for (unsigned int i = 0; i < listaUsuarios.size(); ++i) {
        jConv["IDUsuarios"][i] = listaUsuarios[i];
    }

    // Se guarda la nueva conversación
    rocksdb::Status st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetConversationKey(convID), JsonToSlice(jConv) );

    if (!st.ok()) {
        HL_ERROR( logger, "No se logró guardar una nueva conversación\n" + st.ToString() );
        return 0;
    }

    // Se asocia cada usuario que participa de la conversación
    for (unsigned int i = 0; i < listaUsuarios.size(); ++i) {
        std::string userKey = GetUserKey( listaUsuarios[i] );

        std::string val;
        st = this->m_rockdb->Get( rocksdb::ReadOptions(), userKey, &val );   // Recupera los datos del usuario

        if (!st.ok()) {
            HL_FATAL( logger, "Se grabó una conversación, pero no se pudo asociar a algún usuario\n" + st.ToString() );
            throw std::runtime_error( "Error al recuperar un usuario (" + userKey + ")\n" + st.ToString() );
        }

        Json::Value jUser = SliceToJson( val );
        jUser["IDConversaciones"].append( convID ); // Agrega el id de la nueva conversación

        st = this->m_rockdb->Put( rocksdb::WriteOptions(), userKey, JsonToSlice(jUser) );    // Lo guarda

        if (!st.ok()) {
            HL_FATAL( logger, "Se asoció un usuario a una conversación, pero no se puede almacenarla\n" + st.ToString() );
            throw std::runtime_error( "Error al guardar un usuario (" + userKey + ")\n" + st.ToString() );
        }
    }

    return convID;
}


std::vector<unsigned int> RocaDB::GetConversaciones(std::string userID) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetUserKey(userID), &val );

    if (st.IsNotFound()) {
        return std::vector<unsigned int>(); // Devuelve un vector vacio
    }

    Json::Value jUser = SliceToJson( val );

    std::vector<unsigned int> vConvs;
    for (unsigned int i = 0; i < jUser["IDConversaciones"].size(); ++i) {
        vConvs.push_back( jUser["IDConversaciones"][i].asUInt() );
    }

    return vConvs;
}


std::vector<unsigned int> RocaDB::GetMensajesConversacion(unsigned int conversacionID) {
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetConversationKey(conversacionID), &val );

    if (st.IsNotFound()) {  // No existe la conversación
        return std::vector<unsigned int>();
    }

    Json::Value jConv = SliceToJson( val );

    std::vector<unsigned int> vResul;
    for (unsigned int i = 0; i < jConv["IDMensajes"].size(); ++i) {
        unsigned int msgID = jConv["IDMensajes"][i].asUInt();

        vResul.push_back( msgID );
    }

    return vResul;
}

std::vector<std::string> RocaDB::GetParticipantesConversacion(unsigned int conversacionID){
    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetConversationKey(conversacionID), &val );

    if (st.IsNotFound()) {  // No existe la conversación
        return std::vector<std::string>();
    }

    Json::Value jConv = SliceToJson( val );

    std::vector<std::string> vResul;
    for (unsigned int i = 0; i < jConv["IDUsuarios"].size(); ++i) {
        std::string userID = jConv["IDUsuarios"][i].asString();

        vResul.push_back( userID );
    }

    return vResul;
}


unsigned int RocaDB::AgregarMensaje(std::string userID, unsigned int IDConversacion, std::string texto) {
    std::string conv;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), GetConversationKey(IDConversacion), &conv );

    if (st.IsNotFound()) {
        HL_ERROR( logger, "Se trató de insertar un mensaje en una conversación no existente" );
        return 0;   // La conversación no existe
    }

    unsigned int msgKey = GenerateNewID();  // Se generá una nueva clave para el mensaje

    // Se generá un nuevo mensaje
    Json::Value jMsg;
    jMsg["IDUsuario"] = userID;
    jMsg["Texto"] = texto;

    // Se agregá el id del mensaje a la conversación
    Json::Value jConv = SliceToJson( conv );
    jConv["IDMensajes"].append( msgKey );

    // Se guarda el mensaje
    st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetMessageKey(msgKey), JsonToSlice(jMsg) );
    if (!st.ok()) {
        HL_ERROR( logger, "Falló la inserción de un nuevo mensaje" );
        return 0;
    }

    // Se guarda la conversación
    st = this->m_rockdb->Put( rocksdb::WriteOptions(), GetConversationKey(IDConversacion), JsonToSlice(jConv) );
    if (!st.ok()) {
        HL_ERROR( logger, "Falló la inserción de un nuevo mensaje a una conversación" );
        return 0;
    }

    return msgKey;
}


std::string RocaDB::GetMensaje(unsigned int mensajeID) {
    std::string m;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(),GetMessageKey(mensajeID), &m );

    if (st.IsNotFound()) {
        return "";   // El mensaje no existe
    }

    Json::Value jMsg = SliceToJson(m);
    return jMsg["Texto"].asString();
}


std::string RocaDB::GetRemitente(unsigned int mensajeID) {
    std::string m;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(),GetMessageKey(mensajeID), &m );

    if (st.IsNotFound()) {
        return "";   // El mensaje no existe
    }

    Json::Value jMsg = SliceToJson(m);
    return jMsg["IDUsuario"].asString();
}


std::string RocaDB::GetConversationKey(unsigned int convID) const {
    return std::string( "C/" + convID );
}


std::string RocaDB::GetMessageKey(unsigned int msgID) const {
    return std::string( "M/" + msgID );
}


//------------------------ Ultimos mensajes ----------------------------- 


unsigned int RocaDB::GetIDUltimoMensaje(std::string userID, unsigned int conversacionID) {
    std::string umKey = GetUltimoReciboKey(userID, conversacionID);

    std::string val;
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), umKey, &val );

    if ( st.IsNotFound() ) {
        return 0;
    }

    Json::Value jMsg = SliceToJson(val);
    return jMsg.get("IDUltimoMensaje", 0).asUInt();
}


void RocaDB::SetIDUltimoMensaje(std::string userID, unsigned int conversacionID, unsigned int mensajeID) {
    Json::Value jMsg;
    jMsg["IDUltimoMensaje"] = mensajeID;

    std::string umKey = GetUltimoReciboKey(userID, conversacionID);

    this->m_rockdb->Put( rocksdb::WriteOptions(), umKey, JsonToSlice(jMsg) );
}


std::string RocaDB::GetUltimoReciboKey(std::string userID, unsigned int convID) const {
    return std::string( "UR/" + userID + std::to_string(convID) );
}


//---------------------------------------------------------------------


unsigned int RocaDB::GenerateNewID() {
    const std::string secuenceKey = "SecuenceKeyGenerator-9000";

    // Recupera el ultimo Id generado
    std::string val = "1";
    rocksdb::Status st = this->m_rockdb->Get( rocksdb::ReadOptions(), secuenceKey, &val );

    if ( st.IsNotFound() ) {
        val = "1";
    }
    unsigned int newGeneratedID = 1;
    // En base al anterior genera uno nuevo
    try{
    	 newGeneratedID = std::stoul(val) + 1;
    } catch (...) {
    	 HL_ERROR( logger, "Falló generar el nuevo id\n");
    	 newGeneratedID = 100;
    }
    // Guarda el nuevo Id y lo devuelve para ser usado
    this->m_rockdb->Put( rocksdb::WriteOptions(), secuenceKey, std::to_string(newGeneratedID) );

    return newGeneratedID;
}


//---------------------------------------------------------------------


std::string RocaDB::JsonToSlice(Json::Value j) const {
    // Crea un writer para el Json
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer( builder.newStreamWriter() );

    // Escribe el Json a un stream
    std::stringstream ss;
    writer->write( j, &ss );

    return ss.str();
}


Json::Value RocaDB::SliceToJson(rocksdb::Slice s) const {
    // Puntero al inicio y al final de los datos del slice
    const char* beg = s.data();
    const char* end = &beg[ s.size() ];

    // Crea un reader para el Json
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );

    // Copia los datos del slice al Json
    std::string errs = "";
    Json::Value jResul;
    bool exito = reader->parse( beg, end, &jResul, &errs );

    if (!exito) {
        HL_FATAL( logger, "Falló slice to Json:\n" + errs );
        throw std::runtime_error( "Error al parsear un slice a Json" );
    }

    return jResul;
}



