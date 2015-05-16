package com.example.appmaker.mensajero;

import android.os.AsyncTask;
import android.util.JsonReader;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by diego on 19/04/15.
 */
///TODO: Conectar con el server y traer el datos reales
public class UsuarioProxy {
    String urlBase = "http://10.0.2.2:8080/grupo7/api/";
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
        ///TODO: Obtener json del servidor
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
        String urlString = urlBase + "usuarios";
        Log.d("MensajerO", urlString);
        List<Usuario> usuarios = null;
        InputStream streamAParsear = null;
        try {
            URL url = new URL(urlString);
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
            streamAParsear = new BufferedInputStream(urlConnection.getInputStream());
            Log.i("MensajerO","Conexión al servidor exitosa");
        } catch (Exception ex) {
            Log.e("MensajerO","No fue posible conectarse al servidor");
            Log.e("MensajerO", ex.toString());
        }
        try {
            UsuarioParser parser = new UsuarioParser(streamAParsear);
            usuarios = parser.getListadoUsuariosConectados();
            Log.i("MensajerO","Lista de Usuarios Logueados traida y parseada");
        }catch (IOException ex){
            Log.e("MensajerO", ex.toString());
        }
        return usuarios;
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

    private class UsuarioAPI extends AsyncTask<String, String, String> {
        public InputStream stream = null;
        public boolean tieneResultado = false;

        @Override
        protected String doInBackground(String... params) {
            String urlString = params[0]; // URL to call
            String resultToDisplay = "";
            InputStream in = null;

            // HTTP Get
            try {
                Log.d("MensajerO", urlString);
                tieneResultado = false;
                URL url = new URL(urlString);
                HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
                in = new BufferedInputStream(urlConnection.getInputStream());
                Log.d("MensajerO", in.toString());
            } catch (Exception e) {
                System.out.println(e.getMessage());
                return e.getMessage();
            }
            stream = in;
            return resultToDisplay;
        }

        protected void onPostExecute(String result) {
            tieneResultado = true;
        }

    } // end UsuarioAPI
}


