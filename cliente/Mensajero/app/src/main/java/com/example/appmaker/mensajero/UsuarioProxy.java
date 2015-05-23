package com.example.appmaker.mensajero;

import android.os.AsyncTask;
import android.util.JsonReader;
import android.util.Log;

import org.apache.http.HttpResponse;
import org.apache.http.ParseException;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicHeader;
import org.apache.http.protocol.HTTP;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
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
        String urlString = urlBase + "usuarios";
        Log.d("MensajerO", urlString);
        List<Usuario> usuarios = null;
        InputStream streamAParsear = null;
        try {
            URL url = new URL(urlString);
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
            streamAParsear = urlConnection.getInputStream();
            Log.i("MensajerO", "Conexión al servidor exitosa");
        } catch (Exception ex) {
            Log.e("MensajerO", "No fue posible conectarse al servidor");
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
        String urlString = urlBase + "sesion";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        InputStream streamAParsear = null;
        try {
            params.put("Token", "0");
            params.put("NombreUsuario", usuario.getNombre());
            params.put("Password", usuario.getPassword());
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setRequestMethod("PUT");
            urlConnection.setRequestProperty("Content-Type", "application/json");
            OutputStreamWriter out = new   OutputStreamWriter(urlConnection.getOutputStream());
            out.write(params.toString());
            out.close();

            int HttpResult =urlConnection.getResponseCode();
            if(HttpResult ==HttpURLConnection.HTTP_OK) {
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                usuario.setToken(parser.readLoginResponse());
                if(parser.getStatusOk()) {
                    UsuarioProxy.usuario = usuario;
                    Log.i("MensajerO", "Usuario Logueado correctamente");
                }
            }else{
                System.out.println(urlConnection.getResponseMessage());
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        } finally {
            if (urlConnection != null)
                urlConnection.disconnect();
        }

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


