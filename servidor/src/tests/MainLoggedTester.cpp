#define CATCH_CONFIG_RUNNER
#include "include/catch.hpp"

#include "humblelogging/api.h"

HUMBLE_LOGGER( logger, "default" );


int main( int argc, char* const argv[] ) {
    // Sets up the logger
    auto &fac = humble::logging::Factory::getInstance();
    fac.setDefaultFormatter( new humble::logging::PatternFormatter("%date [%lls] %filename:%line -> %m\n") );
    fac.registerAppender( new humble::logging::FileAppender("testers.log", false) );
    fac.changeGlobalLogLevel( humble::logging::LogLevel::All );

    // Run the tests
    int result = Catch::Session().run( argc, argv );

    return result;
}

