package com.example.appmaker.mensajero;

import android.test.InstrumentationTestCase;
import java.io.ByteArrayInputStream;
import java.util.List;

/**
 * Created by diego on 07/05/15.
 */
public class UsuarioParserTest extends InstrumentationTestCase {
    public UsuarioParserTest() {
    }

    public void testObtenerListadoUsuariosConectados() throws Exception{
        String jsonRecibido = "\n" +
                "{\n" +
                "\t\"Status\" : \"OK\",\n" +
                "\t\"Token\" : 0,\n" +
                "\t\"Usuarios\" : \n" +
                "\t[\n" +
                "\t\t{\n" +
                "\t\t\t\"Estado\" : \"Testing\",\n" +
                "\t\t\t\"Nombre\" : \"pepe\",\n" +
                "\t\t\t\"Status\" : \"OK\",\n" +
                "\t\t\t\"Token\" : 0,\n" +
                "\t\t\t\"UltimaActividadFecha\" : \"2015/12/31\",\n" +
                "\t\t\t\"UltimaActividadHora\" : \"00:00\"\n" +
                "\t\t},\n" +
                "\t\t{\n" +
                "\t\t\t\"Estado\" : \"Testing\",\n" +
                "\t\t\t\"Nombre\" : \"pepe\",\n" +
                "\t\t\t\"Status\" : \"OK\",\n" +
                "\t\t\t\"Token\" : 0,\n" +
                "\t\t\t\"UltimaActividadFecha\" : \"2015/12/31\",\n" +
                "\t\t\t\"UltimaActividadHora\" : \"00:00\"\n" +
                "\t\t},\n" +
                "\t\t{\n" +
                "\t\t\t\"Estado\" : \"Testing\",\n" +
                "\t\t\t\"Nombre\" : \"pepe\",\n" +
                "\t\t\t\"Status\" : \"OK\",\n" +
                "\t\t\t\"Token\" : 0,\n" +
                "\t\t\t\"UltimaActividadFecha\" : \"2015/12/31\",\n" +
                "\t\t\t\"UltimaActividadHora\" : \"00:00\"\n" +
                "\t\t}\n" +
                "\t]\n" +
                "}";
        UsuarioParser parser = new UsuarioParser(new ByteArrayInputStream(jsonRecibido.getBytes()));
        List<Usuario> usuarios = null;
        try {
            usuarios = parser.getListadoUsuariosConectados();
        } catch (Exception ex) {
        }
        assertEquals(usuarios.size(), 3);
        assertEquals(usuarios.get(0).estaConectado(),true);
    }

    public void testListadoUsuariosConectadosEstadoError(){
        String jsonRecibido = "\n" +
                "{\n" +
                "\t\"Status\" : \"ERR\",\n" +
                "\t\"Token\" : 0,\n" +
                "\t\"Usuarios\" : \n" +
                "\t[\n" +
                "\t]\n" +
                "}";
        UsuarioParser parser = new UsuarioParser(new ByteArrayInputStream(jsonRecibido.getBytes()));
        List<Usuario> usuarios = null;
        try {
            usuarios = parser.getListadoUsuariosConectados();
            fail("El json trajo estado ERR debio tirar excepcion");
        } catch (EstadoRecibidoInvalidoException ex) {
            assertNotNull(ex);
        } catch (Exception ex){
            fail("El json trajo estado ERR debio tirar excepcion");
        }

    }
}
