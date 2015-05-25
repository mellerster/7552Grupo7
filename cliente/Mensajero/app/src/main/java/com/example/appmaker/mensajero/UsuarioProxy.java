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
                    usuario.conectar();
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
     * Envia al servidor los datos del usuario para guardar
     * @param usuario a actualizar sus datos
     * @return true si el servido actualizo correctamente los datos, false en caso contrario
     */
    public boolean actualizarPerfil(Usuario usuario) {
        String urlString = urlBase + "usuarios";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        InputStream streamAParsear = null;
        boolean statusOk = false;
        try {
            params.put("Token", usuario.getToken());
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
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                parser.parseStatus();
                if (parser.getStatusOk()) {
                    UsuarioProxy.usuario = new Usuario(usuario);
                    Log.i("MensajerO", "Perfil Actualizado correctamente");
                    statusOk = true;
                } else {
                    Log.e("MensajerO", "El servidor devolvio estado ERR");
                }
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

    public Usuario realizarCheckin(Usuario usuario){
        //TODO: Ver uri a llamar
        String urlString = urlBase + "usuarios";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        InputStream streamAParsear = null;
        try {
            params.put("Token", usuario.getToken());
            params.put("Latitud", usuario.getLatitud());
            params.put("Longitud", usuario.getLongitud());
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
                streamAParsear = urlConnection.getInputStream();
                UsuarioParser parser = new UsuarioParser(streamAParsear);
                usuario.setCheckin(parser.parseCheckin());
                if (parser.getStatusOk()) {
                    UsuarioProxy.usuario = new Usuario(usuario);
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


