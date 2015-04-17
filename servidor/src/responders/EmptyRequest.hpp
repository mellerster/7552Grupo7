#ifndef EMPTY_REQUEST_H
#define EMPTY_REQUEST_H

#include <vector>
#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "ICodec.hpp"



/** Representa un request nulo.
 * */
class EmptyRequest : public RequestHandler {
    public:
        EmptyRequest(IDataService &service, ICodec &codec);
        virtual ~EmptyRequest();

        void LoadParameters(std::string queryString, const char* data, size_t data_len);
        virtual std::vector<char> GetResponseData();
};


#endif

