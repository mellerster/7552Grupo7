package com.example.appmaker.mensajero;

import android.util.JsonReader;
import android.util.Log;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by diego on 19/04/15.
 */
///TODO: Conectar con el server y traer el datos reales
public class UsuarioProxy {

    /**
     * Usuario que tiene el token para hablar con el servidor
     */
    private static Usuario usuario;

    /**
     * Obtiene el usuario con el token para hablar con el servidor
     *
     * @return usuario que tiene el token
     */
    public static Usuario getUsuario() {
        return usuario;
    }

    /**
     * Trae del servidor la lista de usuarios conectados
     *
     * @return Un List tipado de Usuario
     */
    public List<Usuario> getUsuariosConectados() {
        //Mockup de Usuarios
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
        List<Usuario> usuarios = parsearJSon(jsonRecibido);
        return usuarios;
    }

    private List<Usuario> parsearJSon(String jsonRecibido) {
        InputStream in = new ByteArrayInputStream(jsonRecibido.getBytes());
        String token = "";
        List<Usuario> usuarios = new ArrayList<>();
        try {
            JsonReader reader = new JsonReader(new InputStreamReader(in, "UTF-8"));
            try {
                reader.beginObject();
                while (reader.hasNext()) {
                    String name = reader.nextName();
                    switch (name) {
                        case "Status":
                            String status = reader.nextString();
                            if (!status.equals("OK")) {
                                ///TODO: Crear Excepcion: EstadoRecibidoInvalidoException
                                Log.e("Obtencion Listado Usuarios Conectados", "Status es: " + status);
                                throw new Exception();
                            }
                            break;
                        case "Token":
                            token = reader.nextString();
                            break;
                        case "Usuarios":
                            reader.beginArray();

                            while (reader.hasNext()) {
                                usuarios.add(readUsuarioListado(reader));
                            }
                            reader.endArray();
                            break;

                    }
                }
            } finally {
                reader.close();
            }
        } catch (Exception ex) {
            Log.e("Leer Listado de Usuarios Conectados", ex.toString());
        }
        return usuarios;
    }

    public Usuario readUsuarioListado(JsonReader reader) throws IOException {
        Usuario usuario = null;

        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "Nombre":
                    usuario = new Usuario(reader.nextString());
                    usuario.conectar();
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return usuario;
    }

    /**
     * Autentica a un usuario en el servidor
     *
     * @param usuario que debe tener la información necesaria para autenticar
     * @return Devuelve el Usuario con la información del servidor
     */
    public Usuario login(Usuario usuario) {
        usuario.conectar();
        UsuarioProxy.usuario = usuario;
        return usuario;
    }

    /**
     * Marca en el servidor que el usuario aparecera como desconectado
     *
     * @param usuario a desconectar
     * @return el usuario desconectado
     */
    public Usuario logout(Usuario usuario) {
        usuario.desconectar();
        UsuarioProxy.usuario.desconectar();
        return usuario;
    }

    /**
     * Registra y Autentifica a un usuario en el servidor
     *
     * @param username nombre del usuario
     * @param password contraseña del usuario
     * @return el Usuario autentificado
     */
    public Usuario registrar(String username, String password) {
        Usuario user = new Usuario(username, password);
        user.conectar();
        UsuarioProxy.usuario = user;
        return user;
    }

    /**
     * Trae el estado completo de un usuario
     *
     * @param username nombre del usuario
     * @return el Usuario con todos sus datos para mostrar
     */
    public Usuario verEstado(String username) {
        return new Usuario(username);
    }

    /**
     * Envia la foto de perfil del usuario al servidor
     *
     * @param usuario con una foto de perfil nueva.
     */
    public void cargarFoto(Usuario usuario) {
        UsuarioProxy.usuario = usuario;
        ///TODO: Enviar foto al server
    }

}
