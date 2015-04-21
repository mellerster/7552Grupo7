#ifndef EMPTY_REQUEST_H
#define EMPTY_REQUEST_H

#include <memory>
#include <vector>
#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Codec.hpp"



/** Representa un request nulo.
 * */
class EmptyRequest : public RequestHandler {
    public:
        EmptyRequest(IDataService &service, std::unique_ptr<Codec> codec);
        virtual ~EmptyRequest();

        virtual std::unique_ptr<Response> GetResponseData();
};


#endif

