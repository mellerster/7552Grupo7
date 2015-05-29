#include "RocaDB.hpp"


RocaDB::RocaDB() : m_rockdb(nullptr) {
}


RocaDB::~RocaDB() {
    Close();
}


void RocaDB::Open(std::string fileName) {
    rocksdb::Options opt;
    opt.create_if_missing = true;

    rocksdb::Status st = rocksdb::DB::Open( opt, fileName, &this->m_rockdb );
    // TODO: Checkear el estado...
}


void RocaDB::Close() {
    if (this->m_rockdb != nullptr) {
        delete this->m_rockdb;

        this->m_rockdb = nullptr;
    }
}


bool RocaDB::ExistsUser(std::string userID);
bool RocaDB::CreateUser(std::string userID, std::string password);
bool RocaDB::StoreUserUbicacion(std::string userID, std::string latitud, std::string longitud);
bool RocaDB::LoadUserUbicacion(std::string userID, std::string &latitud, std::string &longitud);
bool RocaDB::StoreUserFoto(std::string userID, std::string foto);
bool RocaDB::LoadUserFoto(std::string userID, std::string &foto);

unsigned int CRocaDB::reateNewConversacion(std::vector<std::string> listaUsuarios);
std::vector<unsigned int> RocaDB::GetMensajesConversacion(unsigned int conversacionID);
unsigned int RocaDB::AgregarMensaje(std::string userID, unsigned int IDConversacion, std::string texto);
std::string RocaDB::GetMensaje(unsigned int mensajeID);

unsigned int RocaDB::GetIDUltimoMensaje(std::string userID, unsigned int conversacionID);
void RocaDB::SetIDUltimoMensaje(std::string userID, unsigned int conversacionID, unsigned int mensajeID);

    /*
    cout << "Abriendo la base de datos... ";
    rocksdb::DB* db;
    rocksdb::Options opt;
    opt.create_if_missing = true;

    rocksdb::Status st = rocksdb::DB::Open( opt, "testDB.bin", &db );
    cout << st.ToString() << "!" << endl;
    cout << endl;

    delete db;
    */
