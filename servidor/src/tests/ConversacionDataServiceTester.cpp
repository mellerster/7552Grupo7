#include <vector>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "helpers/IPosicionador.hpp"
#include "DataService.hpp"

#include "Conversacion.hpp"



TEST_CASE ( "Listado de convesaciones" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::Close );

    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "Listar conversacion - todos los mensajes leidos" ) {
        std::vector<std::string> participantes;
        std::vector<unsigned int> DBConvs;
        std::vector<unsigned int> DBMsgs;

        DBConvs.push_back( 555 );
        DBMsgs.push_back( 444 );
        participantes.push_back( "pepa" );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 555 ).Return( DBMsgs );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 555 ).Return( 444 );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 444 ).Return( "Kick it up a notch!" );
        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 555 ).Return( participantes );
        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepe" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 1 == convs.size() );
        REQUIRE ( 555 == convs.front().IDConversacion );
        REQUIRE ( "pepe: Kick it up a notch!"  == convs.front().UltimoMensaje );
        REQUIRE ( convs.front().UltimoMensajeLeido );
    }

    SECTION ( "Listar conversacion - mensaje sin leer" ) {
        std::vector<std::string> participantes;
        participantes.push_back( "pepa" );

        std::vector<unsigned int> DBConvs;
        std::vector<unsigned int> DBMsgs;

        DBConvs.push_back( 555 );
        DBMsgs.push_back( 444 );
        DBMsgs.push_back( 445 );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 555 ).Return( DBMsgs );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 555 ).Return( 444 );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 444 ).Return( "Kick it up a notch!" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 445 ).Return( "I gotta an evil love" );
        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 555 ).Return( participantes );
        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepe" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 1 == convs.size() );
        REQUIRE ( 555 == convs.front().IDConversacion );
        REQUIRE ( "pepe: I gotta an evil love"  == convs.front().UltimoMensaje );
        REQUIRE_FALSE ( convs.front().UltimoMensajeLeido );
    }

    SECTION ( "Listar conversaciones - todos los mensajes leidos" ) {
        std::vector<unsigned int> DBConvs;
        DBConvs.push_back( 111 );
        DBConvs.push_back( 222 );

        std::vector<unsigned int> DBMsgs1;
        std::vector<unsigned int> DBMsgs2;
        DBMsgs1.push_back( 444 );
        DBMsgs2.push_back( 555 );

        std::vector<std::string> participantes;
        participantes.push_back( "pepa" );
        participantes.push_back( "peitoa" );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 111 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 222 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 111 ).Return( 444 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 222 ).Return( 555 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 444 ).Return( "I know what we are gonna do today" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 555 ).Return( "Hey Ferb!" );

        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 111 ).Return( participantes );
        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 222 ).Return( participantes );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepe" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        
        REQUIRE ( 111 == convs.front().IDConversacion );
        REQUIRE ( 222 == convs.back().IDConversacion );
        
        REQUIRE ( "pepe: I know what we are gonna do today"  == convs.front().UltimoMensaje );
        REQUIRE ( "pepe: Hey Ferb!"  == convs.back().UltimoMensaje );

        REQUIRE ( convs.front().UltimoMensajeLeido );
        REQUIRE ( convs.back().UltimoMensajeLeido );
    }

    SECTION ( "Listar conversaciones - todos los mensajes sin leer" ) {
        std::vector<unsigned int> DBConvs;
        DBConvs.push_back( 1 );
        DBConvs.push_back( 2 );

        std::vector<unsigned int> DBMsgs1;
        DBMsgs1.push_back( 11 );
        DBMsgs1.push_back( 12 );

        std::vector<unsigned int> DBMsgs2;
        DBMsgs2.push_back( 22 );
        DBMsgs2.push_back( 23 );

        std::vector<std::string> participantes;
        participantes.push_back( "pepa" );
        participantes.push_back( "peitoa" );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );

        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 1 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 2 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 1 ).Return( 11 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 2 ).Return( 22 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 12 ).Return( "what'cha doing" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 23 ).Return( "You're going down!" );

        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 1 ).Return( participantes );
        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 2 ).Return( participantes );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepe" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        REQUIRE ( 1 == convs.front().IDConversacion );
        REQUIRE ( 2 == convs.back().IDConversacion );

        REQUIRE ( "pepe: what'cha doing"  == convs.front().UltimoMensaje );
        REQUIRE ( "pepe: You're going down!"  == convs.back().UltimoMensaje );

        REQUIRE_FALSE ( convs.front().UltimoMensajeLeido );
        REQUIRE_FALSE ( convs.back().UltimoMensajeLeido );
    }

    SECTION ( "Listar conversaciones - mensajes mezclados" ) {
        std::vector<unsigned int> DBConvs;
        DBConvs.push_back( 1 );
        DBConvs.push_back( 2 );

        std::vector<unsigned int> DBMsgs1;
        std::vector<unsigned int> DBMsgs2;
        DBMsgs1.push_back( 11 );
        DBMsgs2.push_back( 22 );
        DBMsgs2.push_back( 222 );

        std::vector<std::string> participantes;
        participantes.push_back( "pepa" );
        participantes.push_back( "peitoa" );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );

        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 1 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 2 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 1 ).Return( 11 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 2 ).Return( 22 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 11 ).Return( "The days are longer" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 222 ).Return( "The nights are shorter" );

        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 1 ).Return( participantes );
        mocker.OnCall( mockedDB, IDB::GetParticipantesConversacion ).With( 2 ).Return( participantes );

        mocker.OnCall( mockedDB, IDB::GetRemitente ).Return( "pepe" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        REQUIRE ( 1 == convs.front().IDConversacion );
        REQUIRE ( 2 == convs.back().IDConversacion );

        REQUIRE ( "pepe: The days are longer"  == convs.front().UltimoMensaje );
        REQUIRE ( "pepe: The nights are shorter"  == convs.back().UltimoMensaje );

        REQUIRE ( convs.front().UltimoMensajeLeido );
        REQUIRE_FALSE ( convs.back().UltimoMensajeLeido );
    }

}


TEST_CASE ( "Get conversacion por usuarios" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::Close );

    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int tok_1 = ds.StartSession( "pepe", "1234" );
    unsigned int tok_2 = ds.StartSession( "pepa", "4321" );

    SECTION ( "Existe conversacion" ) {
        std::vector<unsigned int> v1;
        v1.push_back( 5 );

        std::vector<unsigned int> v2;
        v2.push_back( 5 );

        mocker.autoExpect = false;
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepe" ).Return( v1 );
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepa" ).Return( v2 );
        mocker.NeverCall( mockedDB, IDB::CreateNewConversacion );

        // Act
        unsigned int convID = ds.GetConversacion( tok_1, "pepa" );

        // Assert
        REQUIRE ( 5 == convID );
    }

    SECTION ( "Existe conversacion" ) {
        std::vector<unsigned int> v1;
        v1.push_back( 9 );
        v1.push_back( 5 );
        v1.push_back( 3 );

        std::vector<unsigned int> v2;
        v1.push_back( 4 );
        v2.push_back( 5 );

        mocker.autoExpect = false;
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepe" ).Return( v1 );
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepa" ).Return( v2 );
        mocker.NeverCall( mockedDB, IDB::CreateNewConversacion );

        // Act
        unsigned int convID = ds.GetConversacion( tok_2, "pepe" );

        // Assert
        REQUIRE ( 5 == convID );
    }

    SECTION ( "No existe conversacion" ) {
        std::vector<unsigned int> v1;
        v1.push_back( 9 );

        std::vector<unsigned int> v2;
        v2.push_back( 5 );

        mocker.autoExpect = false;
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepe" ).Return( v1 );
        mocker.ExpectCall( mockedDB, IDB::GetConversaciones ).With( "pepa" ).Return( v2 );
        mocker.ExpectCall( mockedDB, IDB::CreateNewConversacion ).Return( 999 );

        // Act
        unsigned int convID = ds.GetConversacion( tok_2, "pepe" );

        // Assert
        REQUIRE ( 999 == convID );
    }

}


TEST_CASE ( "Get participantes de una conversacion" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::Close );

    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int tok_1 = ds.StartSession( "pepe", "1234" );
    unsigned int tok_2 = ds.StartSession( "pepa", "4321" );

    SECTION ( "No hay conversacion con los participantes" ) {
        std::vector<std::string> vecPartis;
        mocker.ExpectCall( mockedDB, IDB::GetParticipantesConversacion ).Return( vecPartis );

        // Act
        std::vector<std::string> vecParticipantes = ds.GetParticipantes( tok_1, 5 );

        // Assert
        REQUIRE ( vecPartis.empty() );
    }

    SECTION ( "Hay una conversacion con los participantes" ) {
        std::vector<std::string> vecPartis;
        vecPartis.push_back( "pepe" );
        vecPartis.push_back( "pepa" );

        mocker.ExpectCall( mockedDB, IDB::GetParticipantesConversacion ).Return( vecPartis );

        SECTION ( "pedido de Pepe" ) {
            // Act
            std::vector<std::string> vecParticipantes = ds.GetParticipantes( tok_1, 5 );

            REQUIRE ( 1 == vecParticipantes.size() );
            REQUIRE ( "pepa" == vecParticipantes.front() );
        }

        SECTION ( "pedido de Pepa" ) {
            // Act
            std::vector<std::string> vecParticipantes = ds.GetParticipantes( tok_2, 5 );

            REQUIRE ( 1 == vecParticipantes.size() );
            REQUIRE ( "pepe" == vecParticipantes.front() );
        }
    }
}


