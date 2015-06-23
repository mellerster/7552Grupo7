#include <vector>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "helpers/IPosicionador.hpp"
#include "DataService.hpp"

#include "Mensaje.hpp"



TEST_CASE ( "Listado de mensajes" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::Close );

    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "obtener mensaje" ) {
        std::vector<unsigned int> vecMsjs;
        vecMsjs.push_back( 890 );

        mocker.ExpectCall( mockedDB, IDB::GetMensajesConversacion ).With( 9 ).Return( vecMsjs );
        mocker.ExpectCall( mockedDB, IDB::GetMensaje ).With( 890 ).Return( "Come home Perry" );
        mocker.ExpectCall( mockedDB, IDB::GetRemitente ).With( 890 ).Return( "Gravity" );

        // Act
        std::vector<Mensaje> vecRes = ds.GetMensajes( token, 9 );

        // Assert
        REQUIRE ( 1 == vecRes.size() );

        REQUIRE ( "Come home Perry" == vecRes.front().Texto );
        REQUIRE ( "Gravity" == vecRes.front().IDRemitente );
    }

    SECTION ( "obtener mensajes" ) {
        std::vector<unsigned int> vecMsjs;
        vecMsjs.push_back( 890 );
        vecMsjs.push_back( 891 );

        mocker.ExpectCall( mockedDB, IDB::GetMensajesConversacion ).With( 9 ).Return( vecMsjs );
        mocker.ExpectCall( mockedDB, IDB::GetMensaje ).With( 890 ).Return( "Come home Perry" );
        mocker.ExpectCall( mockedDB, IDB::GetRemitente ).With( 890 ).Return( "Gravity" );

        mocker.ExpectCall( mockedDB, IDB::GetMensaje ).With( 891 ).Return( "Summer rocks!" );
        mocker.ExpectCall( mockedDB, IDB::GetRemitente ).With( 891 ).Return( "Evil" );

        // Act
        std::vector<Mensaje> vecRes = ds.GetMensajes( token, 9 );

        // Assert
        REQUIRE ( 2 == vecRes.size() );

        REQUIRE ( "Come home Perry" == vecRes.front().Texto );
        REQUIRE ( "Gravity" == vecRes.front().IDRemitente );

        REQUIRE ( "Summer rocks!" == vecRes.back().Texto );
        REQUIRE ( "Evil" == vecRes.back().IDRemitente );
    }

    SECTION ( "no hay mensajes" ) {
        mocker.ExpectCall( mockedDB, IDB::GetMensajesConversacion ).With( 9 ).Return( std::vector<unsigned int>() );
        mocker.NeverCall( mockedDB, IDB::GetMensaje );
        mocker.NeverCall( mockedDB, IDB::GetRemitente );

        // Act
        std::vector<Mensaje> vecRes = ds.GetMensajes( token, 9 );

        // Assert
        REQUIRE ( 0 == vecRes.size() );
    }
}


TEST_CASE ( "Obtener los mensajes no leidos" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::Close );

    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "Todos los mensajes son no leidos" ) {
        std::vector<unsigned int> lMensajes;
        lMensajes.push_back( 55 );
        lMensajes.push_back( 60 );

        mocker.OnCall( mockedDB, IDB::SetIDUltimoMensaje );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).Return( 0 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).Return( lMensajes );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 55 ).Return( "At all the same stuff" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 60 ).Return( "When our robot armies march" );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 55 ).Return( "pepa" );
        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 60 ).Return( "pepe" );

        // Act
        std::vector<Mensaje> vecMensajes = ds.GetMensajesNoLeidos( token, 9 );

        // Assert
        REQUIRE ( 2 == vecMensajes.size() );

        REQUIRE ( "pepa" == vecMensajes.front().IDRemitente );
        REQUIRE ( "At all the same stuff" == vecMensajes.front().Texto );

        REQUIRE ( "pepe" == vecMensajes.back().IDRemitente );
        REQUIRE ( "When our robot armies march" == vecMensajes.back().Texto );
    }

    SECTION ( "Hay mensajes no leidos" ) {
        std::vector<unsigned int> lMensajes;
        lMensajes.push_back( 55 );
        lMensajes.push_back( 60 );

        mocker.OnCall( mockedDB, IDB::SetIDUltimoMensaje );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).Return( 55 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).Return( lMensajes );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 55 ).Return( "pepa" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 55 ).Return( "At all the same stuff" );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 60 ).Return( "pepe" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 60 ).Return( "When our robot armies march" );

        // Act
        std::vector<Mensaje> vecMensajes = ds.GetMensajesNoLeidos( token, 9 );

        // Assert
        REQUIRE ( 1 == vecMensajes.size() );

        REQUIRE ( "pepe" == vecMensajes.front().IDRemitente );
        REQUIRE ( "When our robot armies march" == vecMensajes.front().Texto );
    }

    SECTION ( "No hay mensajes no leidos" ) {
        std::vector<unsigned int> lMensajes;
        lMensajes.push_back( 55 );
        lMensajes.push_back( 60 );

        mocker.OnCall( mockedDB, IDB::SetIDUltimoMensaje );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).Return( 60 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).Return( lMensajes );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 55 ).Return( "At all the same stuff" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 60 ).Return( "When our robot armies march" );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 55 ).Return( "pepa" );
        mocker.OnCall( mockedDB, IDB::GetRemitente ).With( 60 ).Return( "pepe" );

        // Act
        std::vector<Mensaje> vecMensajes = ds.GetMensajesNoLeidos( token, 9 );

        // Assert
        REQUIRE ( vecMensajes.empty() );
    }

    SECTION ( "Setea el ultimo mensaje recuperado como leido" ) {
        std::vector<unsigned int> lMensajes;
        lMensajes.push_back( 55 );
        lMensajes.push_back( 60 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).Return( 55 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).Return( lMensajes );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).Return( "Rock me Amadeus!" );
        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepa" );

        mocker.ExpectCall( mockedDB, IDB::SetIDUltimoMensaje ).With( "pepe", 9, 60 );

        // Act
        std::vector<Mensaje> vecMensajes = ds.GetMensajesNoLeidos( token, 9 );

        // Assert
        REQUIRE_FALSE ( vecMensajes.empty() );
    }
}


