#ifndef IDATA_SERVICE_H
#define IDATA_SERVICE_H



/** La interfaz que todos los servicdios de persistencia de datos deben implementar.
 * */
class IDataService {
    public:

        /** Abre la conexion con la base de datos.
         *
         * @return  "true" si la connexion fue abrierta exitosamente, "false" sino.
         * */
        virtual bool Open() = 0;


        /** Cierra la conexion con la base de datos.
         * */
        virtual void Close() = 0;
};


#endif

