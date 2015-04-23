#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "handlers/dtos/UserStatusDTO.hpp"
#include "handlers/dtos/ListUsersDTO.hpp"



TEST_CASE ( "UserStatus - Codificar a JSON", "[DTOs][JSON]" ) {
    // Arrange
    UserStatusDTO dto;
    dto.Nombre = "Pepe";
    dto.Estado = "Testeando";
    dto.UltimaActividadHora = "10:15";
    dto.UltimaActividadFecha = "1816/07/09";

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

    SECTION ( "La ultima fecha de actividad fue extraida" ) {
        Json::Value parsed = dto.ToJSON();

        std::string lastDate = parsed.get("UltimaActividadFecha", "0000/00/00").asString();
        REQUIRE ( lastDate == dto.UltimaActividadFecha );
    }


    SECTION ( "La ultima hora de actividad fue extraida" ) {
        Json::Value parsed = dto.ToJSON();

        std::string lastTime = parsed.get("UltimaActividadHora", "00:00").asString();
        REQUIRE ( lastTime == dto.UltimaActividadHora );
    }
}


TEST_CASE ( "UserStatus - Decodificar desde JSON", "[DTOs][JSON]" ) {
    Json::Value jUserStatus;
    jUserStatus["Nombre"] = "jason";
    jUserStatus["Estado"] = "Testeando";
    jUserStatus["UltimaActividadHora"] = "18:23";
    jUserStatus["UltimaActividadFecha"] = "1995/11/27";


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( UserStatusDTO dto( jUserStatus ) );
    }

    SECTION ( "Carga los datos" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Nombre != "" );
        REQUIRE ( dto.Estado != "" );
        REQUIRE ( dto.UltimaActividadHora != "" );
        REQUIRE ( dto.UltimaActividadFecha != "" );
    }

    SECTION ( "Carga el nombre correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Nombre == "jason" );
    }

    SECTION ( "Carga el estado correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.Estado == "Testeando" );
    }

    SECTION ( "Carga la ultima hora de actividad correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.UltimaActividadHora == "18:23" );
    }

    SECTION ( "Carga la ultima fecha de actividad correctamente" ) {
        UserStatusDTO dto( jUserStatus );

        REQUIRE ( dto.UltimaActividadFecha == "1995/11/27" );
    }
}



TEST_CASE ( "ListUsers - Codificar a JSON", "[DTOs][JSON]" ) {
    // Arrange
    ListUsersDTO dto;
    dto.Token = "123456";

    SECTION ( "El parseo es exitoso" ) {
        Json::Value parsed = dto.ToJSON();

        REQUIRE ( parsed.type() != Json::ValueType::nullValue );
    }

    SECTION ( "El token fue extraido" ) {
        Json::Value parsed = dto.ToJSON();

        std::string token = parsed.get("Token", "nope").asString();
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



TEST_CASE ( "ListUsers - Decodificar desde JSON", "[DTOs][JSON]" ) {
    Json::Value jListUsers;
    jListUsers["Token"] = "jason";


    SECTION ( "No Explota" ) {
        REQUIRE_NOTHROW ( ListUsersDTO dto(jListUsers) );
    }

    SECTION ( "Carga el token" ) {
        ListUsersDTO dto( jListUsers );

        REQUIRE ( dto.Token == "jason" );
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

