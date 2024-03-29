#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "handlers/dtos/BaseDTO.hpp"
#include "handlers/dtos/LoginDTO.hpp"
#include "handlers/dtos/BroadcastDTO.hpp"
#include "handlers/dtos/PerfilDTO.hpp"
#include "handlers/dtos/MensajeDTO.hpp"
#include "handlers/dtos/CheckinDTO.hpp"
#include "handlers/dtos/ListUsersDTO.hpp"
#include "handlers/dtos/UserStatusDTO.hpp"
#include "handlers/dtos/SentMensajeDTO.hpp"
#include "handlers/dtos/RegistrationDTO.hpp"
#include "handlers/dtos/ConversationDTO.hpp"
#include "handlers/dtos/ListaMensajesDTO.hpp"
#include "handlers/dtos/ListConversationsDTO.hpp"



TEST_CASE ( "BaseDTO - Codificar a JSON" ){
    BaseDTO dto;
    dto.Status = "OK";

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El status es extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string stat = parsed.get("Status", "X").asString();
        REQUIRE ( dto.Status == stat );
    }
}


TEST_CASE ( "BaseDTO - Decodificar desde JSON" ){
    Json::Value j;
    j["Status"] = "OK";

    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( BaseDTO dto(j) );
    }

    SECTION ( "Carga el Status" ) {
        BaseDTO dto(j);

        REQUIRE ( dto.Status == "OK" );
    }
}


TEST_CASE ( "UserStatus - Codificar a JSON" ) {
    // Arrange
    UserStatusDTO dto;
    dto.Nombre = "Pepe";
    dto.Estado = "Testeando";
    dto.Foto = ":-)";
    dto.CheckInFechaHora = "15/05/15 a las 10:15:13 hs.";

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El nombre fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string name = parsed.get("Nombre", "nope").asString();
        REQUIRE ( name == dto.Nombre );
    }

    SECTION ( "El estado fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string status = parsed.get("Estado", "fail").asString();
        REQUIRE ( status == dto.Estado );
    }

    SECTION ( "La foto fue extraida" ) {
        Json::Value parsed = dto.ToJSON();

        std::string foto = parsed.get("Foto", "X-(").asString();
        REQUIRE ( dto.Foto == foto );
    }

    SECTION ( "CheckInFechaHora fue extraida" ) {
        Json::Value parsed = dto.ToJSON();

        std::string lastDate = parsed.get("CheckInFechaHora", "0000/00/00").asString();
        REQUIRE ( lastDate == dto.CheckInFechaHora);
    }
}


TEST_CASE ( "UserStatus - Decodificar desde JSON" ) {
    Json::Value jUserStatus;
    jUserStatus["Nombre"] = "jason";
    jUserStatus["Estado"] = "Testeando";
    jUserStatus["Foto"] = ":-p";


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( UserStatusDTO dto( jUserStatus ) );
    }

    SECTION ( "Carga los datos" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Nombre != "" );
        REQUIRE ( dto.Estado != "" );
        REQUIRE ( dto.Foto != "" );
    }

    SECTION ( "Carga el nombre correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Nombre == "jason" );
    }

    SECTION ( "Carga el estado correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Estado == "Testeando" );
    }

    SECTION ( "Carga la foto correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Foto == ":-p" );
    }
}



TEST_CASE ( "ListUsers - Codificar a JSON" ) {
    // Arrange
    ListUsersDTO dto;
    dto.Token = 123456;

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El token fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        unsigned int token = parsed.get("Token", 0).asUInt();
        REQUIRE ( token == dto.Token );
    }

    SECTION ( "No hay estados" ) {
        Json::Value parsed = dto.ToJSON();

        Json::Value usus = parsed["Usuarios"];
        REQUIRE ( usus.type() == Json::ValueType::nullValue );
    }

    SECTION ( "Si hay estado" ) {
        UserStatusDTO stat;
        stat.Nombre = "Hola";

        dto.Usuarios.push_back( stat );

        Json::Value parsed = dto.ToJSON();
        Json::Value usus = parsed["Usuarios"];

        REQUIRE ( usus.type() == Json::ValueType::arrayValue );
        REQUIRE ( usus.size() == 1 );
        REQUIRE ( usus[0].get("Nombre", "chau") == stat.Nombre );
    }

    SECTION ( "Si hay estados varios" ) {
        UserStatusDTO stat1;
        UserStatusDTO stat2;
        UserStatusDTO stat3;

        stat1.Nombre = "Hola";
        stat2.Nombre = "Mundo";
        stat3.Nombre = "JSON!";

        dto.Usuarios.push_back( stat1 );
        dto.Usuarios.push_back( stat2 );
        dto.Usuarios.push_back( stat3 );

        Json::Value parsed = dto.ToJSON();
        Json::Value usus = parsed["Usuarios"];

        REQUIRE ( usus.type() == Json::ValueType::arrayValue );
        REQUIRE ( usus.size() == 3 );
        REQUIRE ( usus[0].get("Nombre", "fail1") == stat1.Nombre );
        REQUIRE ( usus[1].get("Nombre", "fail2") == stat2.Nombre );
        REQUIRE ( usus[2].get("Nombre", "fail3") == stat3.Nombre );
    }

}



TEST_CASE ( "ListUsers - Decodificar desde JSON" ) {
    Json::Value jListUsers;
    jListUsers["Token"] = 999;


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( ListUsersDTO dto(jListUsers) );
    }

    SECTION ( "Carga el token" ) {
        ListUsersDTO dto( jListUsers );

        REQUIRE ( dto.Token == 999 );
    }

    SECTION ( "No hay lista de usuarios" ) {
        ListUsersDTO dto( jListUsers );

        REQUIRE ( dto.Usuarios.size() == 0 );
    }

    SECTION ( "Carga un estado de usuario" ) {
        UserStatusDTO stat1;
        stat1.Nombre = "pepe_1";
        jListUsers["Usuarios"][0] = stat1.ToJSON();

        ListUsersDTO dto( jListUsers );

        REQUIRE ( dto.Usuarios.size() == 1 );
        REQUIRE ( dto.Usuarios[0].Nombre == stat1.Nombre );
    }

    SECTION ( "Carga varios estados de usuario" ) {
        UserStatusDTO stat1;
        UserStatusDTO stat2;
        UserStatusDTO stat3;

        stat1.Nombre = "pepe_1";
        stat2.Nombre = "pepe_2";
        stat3.Nombre = "pepe_3";

        jListUsers["Usuarios"][0] = stat1.ToJSON();
        jListUsers["Usuarios"][1] = stat2.ToJSON();
        jListUsers["Usuarios"][2] = stat3.ToJSON();

        ListUsersDTO dto( jListUsers );

        REQUIRE ( dto.Usuarios.size() == 3 );
        REQUIRE ( dto.Usuarios[0].Nombre == stat1.Nombre );
        REQUIRE ( dto.Usuarios[1].Nombre == stat2.Nombre );
        REQUIRE ( dto.Usuarios[2].Nombre == stat3.Nombre );
    }

}


TEST_CASE ( "Login - Codificar a JSON" ) {
    LoginDTO dto;
    dto.NombreUsuario = "kamina";
    dto.Password = "Simon";

    SECTION ( "Parseo exitoso" ){
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El nombre de usuario fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string nomUsu = parsed.get("NombreUsuario", "xxx").asString();
        REQUIRE ( nomUsu == dto.NombreUsuario );
    }

    SECTION ( "El password fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string pass = parsed.get("Password", "yyy").asString();
        REQUIRE ( pass == dto.Password );
    }

}


TEST_CASE ( "Login - Decodificar desde JSON" ) {
    Json::Value j;
    j["NombreUsuario"] = "Yoko";
    j["Password"] = "Nia";


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( LoginDTO dto(j) );
    }

    SECTION ( "Carga el nombre usuario" ) {
        LoginDTO dto(j);

        REQUIRE ( dto.NombreUsuario == "Yoko" );
    }

    SECTION ( "Carga el password" ) {
        LoginDTO dto(j);

        REQUIRE ( dto.Password == "Nia" );
    }
}


TEST_CASE ( "Registration DTO - codificar a JSON" ){
    RegistrationDTO dto;
    dto.NombreUsuario = "Kaname";
    dto.Password = "Chidori";

    SECTION ( "Parseo exitoso" ){
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El nombre de usuario fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string nomUsu = parsed.get("NombreUsuario", "xxx").asString();
        REQUIRE ( nomUsu == dto.NombreUsuario );
    }

    SECTION ( "El password fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string pass = parsed.get("Password", "yyy").asString();
        REQUIRE ( pass == dto.Password );
    }

}


TEST_CASE ( "Registration DTO - decodificar desde JSON" ){
    Json::Value j;
    j["NombreUsuario"] = "Yuki";
    j["Password"] = "Nagato";


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( 
                RegistrationDTO dto( j )
        );
    }

    SECTION ( "Carga el nombre usuario" ) {
        RegistrationDTO dto(j);

        REQUIRE ( dto.NombreUsuario == "Yuki" );
    }

    SECTION ( "Carga el password" ) {
        RegistrationDTO dto(j);

        REQUIRE ( dto.Password == "Nagato" );
    }
}


TEST_CASE ( "PerfilDTO - codificar a JSON" ) {
    PerfilDTO dto;
    dto.Token = 123;
    dto.Estado = "Borracho";
    dto.Foto = "123ABC";

    SECTION ( "Parseo exitoso" ) {
        Json::Value resul = dto.ToJSON();

        REQUIRE ( resul.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Extraccion de Token" ) {
        Json::Value resul = dto.ToJSON();

        unsigned int tok = resul.get("Token", 0).asUInt();
        REQUIRE ( dto.Token == tok );
    }

    SECTION ( "Extraccion de Estado" ) {
        Json::Value resul = dto.ToJSON();

        std::string est = resul.get("Estado", "X").asString();
        REQUIRE ( dto.Estado == est );
    }

    SECTION ( "Extraccion de Foto" ) {
        Json::Value resul = dto.ToJSON();

        std::string foto = resul.get("Foto", "X").asString();
        REQUIRE ( dto.Foto == foto );
    }
}


TEST_CASE ( "PerfilDTO - deCodificar desde JSON" ) {
    Json::Value j;
    j["Token"] = "123";
    j["Estado"] = "De paro";
    j["Foto"] = ":-)";

    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( 
                PerfilDTO dto( j )
        );
    }

    SECTION ( "Carga el token" ) {
        PerfilDTO dto(j);

        REQUIRE ( dto.Token == 123 );
    }

    SECTION ( "Carga el estado" ) {
        PerfilDTO dto(j);

        REQUIRE ( dto.Estado == "De paro" );
    }

    SECTION ( "Carga la foto" ) {
        PerfilDTO dto(j);

        REQUIRE ( dto.Foto == ":-)" );
    }
}


TEST_CASE ( "CheckinDTO - codificar a JSON" ) {
    CheckinDTO dto;
    dto.Token = 123;
    dto.Hora = "02:17";
    dto.Fecha = "2015/06/14";
    dto.Latitud = "456.458";
    dto.Longitud = "-6.77";
    dto.Descripcion = "algo cualquiera";

    SECTION ( "Parseo exitoso" ) {
        Json::Value resul = dto.ToJSON();

        REQUIRE ( resul.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Extraccion de Token" ) {
        Json::Value resul = dto.ToJSON();

        unsigned int tok = resul.get("Token", 0).asUInt();
        REQUIRE ( dto.Token == tok );
    }

    SECTION ( "Extraccion de Latitud" ) {
        Json::Value resul = dto.ToJSON();

        std::string lat = resul.get("Latitud", "x").asString();
        REQUIRE ( dto.Latitud == lat );
    }

    SECTION ( "Extraccion de Longitud" ) {
        Json::Value resul = dto.ToJSON();

        std::string longitud = resul.get("Longitud", "x").asString();
        REQUIRE ( dto.Longitud == longitud );
    }

    SECTION ( "Extraccion de Descripcion" ) {
        Json::Value resul = dto.ToJSON();

        std::string desc = resul.get("Descripcion", "x").asString();
        REQUIRE ( dto.Descripcion == desc );
    }

    SECTION ( "Extraccion de Fecha" ) {
        Json::Value resul = dto.ToJSON();

        std::string fec = resul.get("Fecha", "x").asString();
        REQUIRE ( dto.Fecha == fec );
    }

    SECTION ( "Extraccion de Hora" ) {
        Json::Value resul = dto.ToJSON();

        std::string hora = resul.get("Hora", "x").asString();
        REQUIRE ( dto.Hora == hora );
    }
}


TEST_CASE ( "CheckinDTO - deCodificar desde JSON" ) {
    Json::Value j;
    j["Token"] = "123";
    j["Latitud"] = "-78.12345";
    j["Longitud"] = "44.65432";
    j["Hora"] = "02:19";
    j["Fecha"] = "2015/06/14";
    j["Descripcion"] = "Superman!";

    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( 
                CheckinDTO dto( j )
        );
    }

    SECTION ( "Carga el token" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Token == 123 );
    }

    SECTION ( "Carga la latitud" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Latitud == "-78.12345" );
    }

    SECTION ( "Carga la longitud" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Longitud == "44.65432" );
    }

    SECTION ( "Carga la descripcion" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Descripcion == "Superman!" );
    }

    SECTION ( "Carga la fecha" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Fecha == "2015/06/14" );
    }

    SECTION ( "Carga la hora" ) {
        CheckinDTO dto(j);

        REQUIRE ( dto.Hora == "02:19" );
    }
}


TEST_CASE ( "Mensaje DTO - codificar" ) {
    MensajeDTO dto;
    dto.IDRemitente = "Monalisa";
    dto.Mensaje = "No necesito bendiciones...";

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El remitente es extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string rem = parsed.get("IDRemitente", "X").asString();
        REQUIRE ( dto.IDRemitente == rem );
    }

    SECTION ( "El mensaje es extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string men = parsed.get("Mensaje", "X").asString();
        REQUIRE ( dto.Mensaje == men );
    }
}


TEST_CASE ( "Mensaje DTO - De-codificar" ) {
    Json::Value j;
    j["IDRemitente"] = "Misaka";
    j["Mensaje"] = "Only my railgun";

    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( 
                MensajeDTO dto( j )
        );
    }

    SECTION ( "Remitente" ) {
        MensajeDTO dto(j);

        REQUIRE ( "Misaka" == dto.IDRemitente );
    }

    SECTION ( "Mensaje" ) {
        MensajeDTO dto(j);

        REQUIRE ( "Only my railgun" == dto.Mensaje );
    }
}


TEST_CASE ( "Lista de mensajes DTO - codificar" ) {
    ListaMensajesDTO dto;
    dto.Token = 456;
    dto.IDConversacion = 789;
    dto.IDUsuario = "pepe";

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Token" ) {
        Json::Value parsed = dto.ToJSON();

        unsigned int tok = parsed.get("Token", 0).asUInt();
        REQUIRE ( tok == dto.Token );
    }

    SECTION ( "IDConversacion" ) {
        Json::Value parsed = dto.ToJSON();

        unsigned int conv = parsed.get("IDConversacion", 0).asUInt();
        REQUIRE ( conv == dto.IDConversacion );
    }

    SECTION ( "IDUsuario" ) {
        Json::Value parsed = dto.ToJSON();

        std::string user = parsed.get("IDUsuario", "X").asString();
        REQUIRE ( user == dto.IDUsuario );
    }

    SECTION ( "Mensaje" ) {
        MensajeDTO m1;
        m1.Mensaje = "I can see the ending!";
        m1.IDRemitente = "Keima";

        dto.Mensajes.push_back( m1 );

        // Act
        Json::Value parsed = dto.ToJSON();
        Json::Value men = parsed["Mensajes"];

        // Assert
        REQUIRE ( men.type() == Json::ValueType::arrayValue );
        REQUIRE ( 1 == men.size() );

        REQUIRE ( m1.Mensaje == men[0].get("Mensaje", "x").asString() );
        REQUIRE ( m1.IDRemitente == men[0].get("IDRemitente", "x").asString() );
    }
}


TEST_CASE ( "Lista de mensajes DTO - De-codificar" ) {
    Json::Value j;
    j["Token"] = 123;
    j["IDConversacion"] = 456;
    j["IDUsuario"] = "Elsie";

    MensajeDTO m1;
    m1.Mensaje = "I can see the ending!";
    m1.IDRemitente = "Keima";

    j["Mensajes"][0] = m1.ToJSON();

    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( 
                ListaMensajesDTO dto( j )
        );
    }

    SECTION ( "Token y conversacion" ) {
        ListaMensajesDTO dto(j);

        REQUIRE ( 123 == dto.Token );
        REQUIRE ( 456 == dto.IDConversacion );
    }

    SECTION ( "ID usuario" ) {
        ListaMensajesDTO dto(j);

        REQUIRE ( "Elsie" == dto.IDUsuario );
    }

    SECTION ( "Mensajes" ) {
        ListaMensajesDTO dto(j);

        REQUIRE ( 1 == dto.Mensajes.size() );
        REQUIRE ( m1.Mensaje == dto.Mensajes.front().Mensaje );
        REQUIRE ( m1.IDRemitente == dto.Mensajes.front().IDRemitente );
    }
}


TEST_CASE ( "Conversaciones - codificar en JSON" ) {
    ConversationDTO dto;
    dto.Token = 123;
    dto.IDConversacion = 456;
    dto.UltimoMensaje = "I lost the beat";
    dto.UltimoMensajeLeido = false;
    dto.Participantes.push_back( "pepe" );
    dto.Participantes.push_back( "pepa" );

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Token e ID conversacion" ) {
        Json::Value j = dto.ToJSON();

        REQUIRE ( dto.Token == j.get("Token", 0).asUInt() );
        REQUIRE ( dto.IDConversacion == j.get("IDConversacion", 0).asUInt() );
    }

    SECTION ( "Mensajes" ) {
        Json::Value j = dto.ToJSON();

        REQUIRE ( dto.UltimoMensaje == j.get("UltimoMensaje", "x").asString() );
        REQUIRE ( dto.UltimoMensajeLeido == j.get("UltimoMensajeLeido", false).asBool() );
    }

    SECTION ( "Participantes" ) {
        Json::Value j = dto.ToJSON();

        REQUIRE ( j["Participantes"].type() == Json::ValueType::arrayValue );
        REQUIRE ( j["Participantes"].size() == 2 );

        REQUIRE ( j["Participantes"][0].asString() == "pepe" );
        REQUIRE ( j["Participantes"][1].asString() == "pepa" );
    }
}


TEST_CASE ( "Conversaciones - decodificar" ) {
    Json::Value j;
    j["Token"] = 123;
    j["IDConversacion"] = 456;
    j["UltimoMensaje"] = "Zany";
    j["UltimoMensajeLeido"] = true;

    j["Participantes"][0] = "Ferb";
    j["Participantes"][1] = "Not Ferb";

    SECTION ( "Funca" ) {
        REQUIRE_NOTHROW (
                ConversationDTO dto( j )
            );
    }

    SECTION ( "Token e id conversacion" ) {
        ConversationDTO dto( j );

        REQUIRE ( 123 == dto.Token );
        REQUIRE ( 456 == dto.IDConversacion );
    }

    SECTION ( "Mensajes" ) {
        ConversationDTO dto( j );

        REQUIRE ( dto.UltimoMensajeLeido );
        REQUIRE ( "Zany" == dto.UltimoMensaje );
    }

    SECTION ( "Participantes" ) {
        ConversationDTO dto( j );

        REQUIRE ( 2 == dto.Participantes.size() );
        REQUIRE ( "Ferb" == dto.Participantes[0] );
        REQUIRE ( "Not Ferb" == dto.Participantes[1] );
    }
}


TEST_CASE ( "Lista de conversaciones - codificar en JSON" ) {
    ConversationDTO c1;
    c1.IDConversacion = 456;
    c1.UltimoMensaje = "Take it a level or two";
    c1.UltimoMensajeLeido = true;

    ConversationDTO c2;
    c2.IDConversacion = 466;
    c2.UltimoMensaje = "Sneakers full of feet";
    c2.UltimoMensajeLeido = false;

    ListConversationsDTO dto;
    dto.Token = 789;
    dto.Conversaciones.push_back( c1 );
    dto.Conversaciones.push_back( c2 );

    SECTION ( "Parseo a JSON" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Token" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( dto.Token == parsed.get("Token", 0).asUInt() );
    }

    SECTION ( "Conversaciones" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed["Conversaciones"].type() == Json::ValueType::arrayValue );
        REQUIRE ( parsed["Conversaciones"].size() == 2 );
    }
}


TEST_CASE ( "Lista de conversaciones - decodificar" ) {
    ConversationDTO c1;
    c1.IDConversacion = 456;
    c1.UltimoMensaje = "Take it a level or two";
    c1.UltimoMensajeLeido = true;

    Json::Value j;
    j["Token"] = 147;
    j["Conversaciones"][0] = c1.ToJSON();

    SECTION ( "Parseo" ) {
        REQUIRE_NOTHROW (
            ListConversationsDTO dto( j )
        );
    }

    SECTION ( "Token" ) {
        ListConversationsDTO dto( j );
        REQUIRE ( 147 == dto.Token );
    }

    SECTION ( "conversaciones" ) {
        ListConversationsDTO dto( j );

        REQUIRE ( 1 == dto.Conversaciones.size() );

        REQUIRE ( c1.IDConversacion == dto.Conversaciones[0].IDConversacion );
        REQUIRE ( c1.UltimoMensaje == dto.Conversaciones[0].UltimoMensaje );
        REQUIRE ( c1.UltimoMensajeLeido == dto.Conversaciones[0].UltimoMensajeLeido );
    }
}


TEST_CASE ( "Enviar mensaje - codif" ) {
    SentMensajeDTO dto;
    dto.Token = 123;
    dto.ConversacionID = 456;
    dto.Texto = "Machanized melee";

    SECTION ( "Parseo a JSON" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Params" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( dto.Token == parsed.get("Token", 0).asUInt() );
        REQUIRE ( dto.Texto == parsed.get("Texto", "").asString() );
        REQUIRE ( dto.ConversacionID == parsed.get("IDConversacion", 0).asUInt() );
    }
}


TEST_CASE ( "Enviar mensaje - decodif" ) {
    Json::Value j;
    j["Token"] = 789;
    j["IDConversacion"] = 963;
    j["Texto"] = "Android armagedon";

    SECTION ( "Parseo" ) {
        REQUIRE_NOTHROW (
                SentMensajeDTO dto( j )
            );
    }

    SECTION ( "Parametros" ) {
        SentMensajeDTO dto( j );

        REQUIRE ( 789 == dto.Token );
        REQUIRE ( 963 == dto.ConversacionID );
        REQUIRE ( "Android armagedon" == dto.Texto );
    }
}


TEST_CASE ( "Broadcast - codif" ) {
    BroadcastDTO dto;
    dto.Token = 888;
    dto.Mensaje = "And make it an A";

    SECTION ( "parseo" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "Params" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( dto.Token == parsed.get("Token", 0).asUInt() );
        REQUIRE ( dto.Mensaje == parsed.get("Mensaje", "").asString() );
    }
}


TEST_CASE ( "Broadcast - decodif" ) {
    Json::Value j;
    j["Token"] = 456;
    j["Mensaje"] = "but you got that beat";

    SECTION ( "Parseo" ) {
        REQUIRE_NOTHROW (
            BroadcastDTO dto( j )
        );
    }

    SECTION ( "Params" ) {
        BroadcastDTO dto( j );

        REQUIRE ( 456 == dto.Token );
        REQUIRE ( "but you got that beat" == dto.Mensaje );
    }
}



