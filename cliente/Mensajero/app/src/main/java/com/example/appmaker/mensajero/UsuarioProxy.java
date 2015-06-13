package com.example.appmaker.mensajero;

import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
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

public class UsuarioProxy extends ProxyBase {


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
     * Crea un proxy para comunicarse con el servidor
     * @param sharedPref que tiene la actividad para saber a donde conectarse
     */
    public UsuarioProxy(SharedPreferences sharedPref){
        super(sharedPref);
    }

    /**
     * Trae del servidor la lista de usuarios conectados
     *
     * @return Un List tipado de Usuario
     */
    public List<Usuario> getUsuariosConectados() {
        String urlString = urlBase + "usuarios?Token=" + String.valueOf(getUsuario().getToken());
        Log.d("MensajerO", urlString);
        List<Usuario> usuarios = null;
        InputStream streamAParsear = null;
        HttpURLConnection urlConnection = null;
        try {
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
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
        } finally {
            if (urlConnection != null)
                urlConnection.disconnect();
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
        Usuario user = null;
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
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
                InputStream streamAParsear;
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                usuario.setToken(parser.readLoginResponse());
                if(parser.getStatusOk()) {
                    usuario.conectar();
                    user = new Usuario(usuario);
                    UsuarioProxy.usuario = new Usuario(usuario);
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

        return user;
    }

    /**
     * Hace que el token sea invalido en el servidor
     *
     * @param usuario a desconectar
     * @return el usuario desconectado
     */
    public void logout(Usuario usuario) {
        String urlString = urlBase + "sesion";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", usuario.getToken());
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setRequestMethod("DELETE");
            urlConnection.setRequestProperty("Content-Type", "application/json");
            OutputStreamWriter out = new   OutputStreamWriter(urlConnection.getOutputStream());
            out.write(params.toString());
            out.close();

            int HttpResult =urlConnection.getResponseCode();
            if(HttpResult ==HttpURLConnection.HTTP_OK) {
                    UsuarioProxy.usuario = null;
                    Log.i("MensajerO", "Usuario DesLogueado correctamente");
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
    }

    /**
     * Registra y Autentifica a un usuario en el servidor
     *
     * @param username nombre del usuario
     * @param password contraseña del usuario
     * @return el Usuario autentificado
     */
    public Usuario registrar(String username, String password) {
        Usuario user = null;
        String urlString = urlBase + "usuarios";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("NombreUsuario", username);
            params.put("Password", password);
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setRequestMethod("POST");
            urlConnection.setRequestProperty("Content-Type", "application/json");
            OutputStreamWriter out = new OutputStreamWriter(urlConnection.getOutputStream());
            out.write(params.toString());
            out.close();
            int HttpResult = urlConnection.getResponseCode();
            if (HttpResult == HttpURLConnection.HTTP_CREATED) {
                Log.i("MensajerO", "Registración realizada correctamente");
                user = new Usuario(username,password);
                //Hago el login de usuario
                login(user);
            } else {
                Log.e("MensajerO", urlConnection.getResponseMessage());
            }
        } catch (EstadoRecibidoInvalidoException e){
            Log.e("MensajerO", e.getMessage());
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
        return user;
    }

    /**
     * Trae el estado completo de un usuario
     *
     * @param username nombre del usuario
     * @return el Usuario con todos sus datos para mostrar
     */
    public Usuario verEstado(String username) {
        String urlString = urlBase + "usuario";
        HttpURLConnection urlConnection = null;
        Usuario aDevolver = null;
        try {
            urlString += "?Token=" + usuario.getToken() + "&Nombre=" + username;
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setRequestProperty("Content-Type", "application/json");
            Log.i("MensajerO","Intento obtener informacion de: " + username);
            int HttpResult = urlConnection.getResponseCode();
            if (HttpResult == HttpURLConnection.HTTP_OK) {
                InputStream streamAParsear;
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                aDevolver = parser.leerUsuario();
                if (parser.getStatusOk()) {
                    Log.i("MensajerO", "Información obtenida correctamente");
                } else {
                    Log.e("MensajerO", "El servidor devolvio estado ERR");
                }
            } else {
                Log.e("MensajerO", urlConnection.getResponseMessage());
            }
        } catch (EstadoRecibidoInvalidoException e){
            Log.e("MensajerO", e.getMessage());
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (urlConnection != null)
                urlConnection.disconnect();
        }

        return aDevolver;
    }

    /**
     * Envia al servidor los datos del usuario para guardar
     * @param usuario a actualizar sus datos
     * @return true si el servido actualizo correctamente los datos, false en caso contrario
     */
    public boolean actualizarPerfil(Usuario usuario) {
        String urlString = urlBase + "usuarios";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        boolean statusOk = false;
        try {
            params.put("Token", getUsuario().getToken());
            if(usuario.getFoto() != null)
                params.put("Foto", usuario.getFotoBase64());
            params.put("Estado", usuario.estaConectado() ? "C" : "D");
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setRequestMethod("PUT");
            urlConnection.setRequestProperty("Content-Type", "application/json");
            OutputStreamWriter out = new OutputStreamWriter(urlConnection.getOutputStream());
            out.write(params.toString());
            out.close();

            int HttpResult = urlConnection.getResponseCode();
            if (HttpResult == HttpURLConnection.HTTP_OK) {
                Log.i("MensajerO", "Perfil Actualizado correctamente");
                statusOk = true;
            } else {
                statusOk = false;
                Log.e("MensajerO", urlConnection.getResponseMessage());
            }
        } catch (EstadoRecibidoInvalidoException e){
            Log.e("MensajerO", e.getMessage());
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

        return statusOk;
    }

    /**
     * Envia al servidor la latitud y longitud del usuario y espera la respuesta del mismo
     * @param usuario el usuario con los datos a enviar
     * @return el usuario con la descripcion del lugar mas cercano al que se encuentra
     */
    public Usuario realizarCheckin(Usuario usuario){
        String urlString = urlBase + "checkin";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", getUsuario().getToken());
            params.put("Latitud", usuario.getLatitud());
            params.put("Longitud", usuario.getLongitud());
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setRequestMethod("POST");
            urlConnection.setRequestProperty("Content-Type", "application/json");
            OutputStreamWriter out = new OutputStreamWriter(urlConnection.getOutputStream());
            out.write(params.toString());
            out.close();

            int HttpResult = urlConnection.getResponseCode();
            if (HttpResult == HttpURLConnection.HTTP_OK) {
                InputStream streamAParsear;
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                usuario.setCheckin(parser.parseCheckin());
                if (parser.getStatusOk()) {
                    Log.d("MensajerO","El servidor devolvio la ubicacion: " + usuario.getCheckin());
                    UsuarioProxy.usuario.setCheckin(usuario.getCheckin());
                    Log.i("MensajerO", "Checkin realizado correctamente");
                } else {
                    Log.e("MensajerO", "El servidor devolvio estado ERR");
                }
            } else {
                Log.e("MensajerO", urlConnection.getResponseMessage());
            }
        } catch (EstadoRecibidoInvalidoException e){
            Log.e("MensajerO", e.getMessage());
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
}


