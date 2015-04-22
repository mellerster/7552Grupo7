#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "handlers/dtos/UserStatusDTO.hpp"



TEST_CASE ( "Codificar a JSON", "[DTOs][JSON]" ) {
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


TEST_CASE ( "Decodificar desde JSON", "[DTOs][JSON]" ) {
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



