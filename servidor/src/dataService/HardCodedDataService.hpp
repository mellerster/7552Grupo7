#ifndef HARDCODED_DATA_SERVICE_H
#define HARDCODED_DATA_SERVICE_H

#include <string>
#include <vector>

#include "IDataService.hpp"



/** Una implementación temporal del acceso a la base de datos.
 * */
class HardCodedDataService : public IDataService {
    public:
        virtual bool Open();
        virtual void Close();

        virtual unsigned int startSession(std::string nombreUsuario, std::string password);
        virtual bool IsTokenActive(unsigned int tok);
        virtual bool RegisterNewUser(std::string nombreUsuario, std::string password);

        virtual std::vector<UserStatus> ListActiveUsers();
};


#endif

