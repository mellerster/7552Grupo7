package com.example.appmaker.mensajero;

import android.content.SharedPreferences;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by diego on 12/06/15.
 */
public class ConversacionProxy extends ProxyBase {
    //TODO: Cambiar valores devueltos por los metodos

    public ConversacionProxy(SharedPreferences sharedPref){
        super(sharedPref);
    }

    public Conversacion[] getConversaciones(){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversaciones?Token=" + String.valueOf(token);
        Conversacion[] conversaciones = new Conversacion[]{};
        return conversaciones;
    }

    public void getConversacion(int id_conversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(id_conversacion);

    }

    public void getConversacion(String nombreUsuario){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idUsuario=" + nombreUsuario;
    }

    public void getMensajesNuevos(int id_conversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(id_conversacion);
    }

    public void enviarMensaje(Mensaje mensaje){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes"; //TODO: ver si mensaje o mensajes
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", token);
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
                Log.i("MensajerO", "");
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
    }

    public void enviarBroadcast(Mensaje mensaje){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "broadcast";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", token);
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
                Log.i("MensajerO", "");
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
    }

}
