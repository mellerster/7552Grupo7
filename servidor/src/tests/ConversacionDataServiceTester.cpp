#include <vector>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "helpers/IPosicionador.hpp"
#include "DataService.hpp"

#include "Mensaje.hpp"
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
        std::vector<unsigned int> DBConvs;
        std::vector<unsigned int> DBMsgs;

        DBConvs.push_back( 555 );
        DBMsgs.push_back( 444 );

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 555 ).Return( DBMsgs );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 555 ).Return( 444 );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 444 ).Return( "Kick it up a notch!" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 1 == convs.size() );
        REQUIRE ( 555 == convs.front().IDConversacion );
        REQUIRE ( "Kick it up a notch!"  == convs.front().UltimoMensaje );
        REQUIRE ( convs.front().UltimoMensajeLeido );
    }

    SECTION ( "Listar conversacion - mensaje sin leer" ) {
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

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 1 == convs.size() );
        REQUIRE ( 555 == convs.front().IDConversacion );
        REQUIRE ( "I gotta an evil love"  == convs.front().UltimoMensaje );
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

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 111 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 222 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 111 ).Return( 444 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 222 ).Return( 555 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 444 ).Return( "I know what we are gonna do today" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 555 ).Return( "Hey Ferb!" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        
        REQUIRE ( 111 == convs.front().IDConversacion );
        REQUIRE ( 222 == convs.back().IDConversacion );
        
        REQUIRE ( "I know what we are gonna do today"  == convs.front().UltimoMensaje );
        REQUIRE ( "Hey Ferb!"  == convs.back().UltimoMensaje );

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

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );

        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 1 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 2 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 1 ).Return( 11 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 2 ).Return( 22 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 12 ).Return( "what'cha doing" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 23 ).Return( "You're going down!" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        REQUIRE ( 1 == convs.front().IDConversacion );
        REQUIRE ( 2 == convs.back().IDConversacion );

        REQUIRE ( "what'cha doing"  == convs.front().UltimoMensaje );
        REQUIRE ( "You're going down!"  == convs.back().UltimoMensaje );

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

        mocker.OnCall( mockedDB, IDB::GetConversaciones ).Return( DBConvs );

        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 1 ).Return( DBMsgs1 );
        mocker.OnCall( mockedDB, IDB::GetMensajesConversacion ).With( 2 ).Return( DBMsgs2 );

        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 1 ).Return( 11 );
        mocker.OnCall( mockedDB, IDB::GetIDUltimoMensaje ).With( "pepe", 2 ).Return( 22 );

        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 11 ).Return( "The days are longer" );
        mocker.OnCall( mockedDB, IDB::GetMensaje ).With( 222 ).Return( "The nights are shorter" );

        // Act
        std::vector<Conversacion> convs = ds.ListActiveConversations( token );

        // Assert
        REQUIRE ( 2 == convs.size() );
        REQUIRE ( 1 == convs.front().IDConversacion );
        REQUIRE ( 2 == convs.back().IDConversacion );

        REQUIRE ( "The days are longer"  == convs.front().UltimoMensaje );
        REQUIRE ( "The nights are shorter"  == convs.back().UltimoMensaje );

        REQUIRE ( convs.front().UltimoMensajeLeido );
        REQUIRE_FALSE ( convs.back().UltimoMensajeLeido );
    }

}


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


