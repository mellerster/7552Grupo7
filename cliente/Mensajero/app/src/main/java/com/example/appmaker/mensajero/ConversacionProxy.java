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
import java.util.ArrayList;
import java.util.List;

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
        String NOMBRE_PROPIO = "Tomas";
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        Conversacion conversacionUno = new Conversacion(mensajes, NOMBRE_PROPIO, "Diego");
        Conversacion conversacionDos = new Conversacion(mensajes, NOMBRE_PROPIO, "Pablo");
        Conversacion conversacionTres = new Conversacion(mensajes, NOMBRE_PROPIO, "Juan");
        Conversacion conversacionCuatro = new Conversacion(mensajes, NOMBRE_PROPIO, "Matias");
        Conversacion conversacionCinco = new Conversacion(mensajes, NOMBRE_PROPIO, "Mariano");
        Conversacion conversacionSeis = new Conversacion(mensajes, NOMBRE_PROPIO, "Tomas");
        Conversacion conversacionSiete = new Conversacion(mensajes, NOMBRE_PROPIO, "Nahuel");
        Conversacion conversacionOcho = new Conversacion(mensajes, NOMBRE_PROPIO, "Victor");
        Conversacion conversacionNueve = new Conversacion(mensajes, NOMBRE_PROPIO, "Oscar");
        Conversacion conversacionDiez = new Conversacion(mensajes, NOMBRE_PROPIO, "Pedro");
        Conversacion conversacionOnce = new Conversacion(mensajes, NOMBRE_PROPIO, "Mateo");
        Conversacion conversacionDoce = new Conversacion(mensajes, NOMBRE_PROPIO, "Marcos");
        Conversacion conversacionCatorce = new Conversacion(mensajes, NOMBRE_PROPIO, "Lucas");
        Conversacion conversacionQuince = new Conversacion(mensajes, NOMBRE_PROPIO, "Romina");
        Conversacion conversacionDieciseis = new Conversacion(mensajes, NOMBRE_PROPIO, "Camila");
        Conversacion conversacionDecisiete = new Conversacion(mensajes, NOMBRE_PROPIO, "Agustina");
        Conversacion conversacionDeciocho = new Conversacion(mensajes, NOMBRE_PROPIO, "Carolina");
        Conversacion conversacionDecinueve = new Conversacion(mensajes, NOMBRE_PROPIO, "Florencia");
        Conversacion conversacionVeinte = new Conversacion(mensajes, NOMBRE_PROPIO, "Abril");
        Conversacion array[] = new Conversacion[] {conversacionUno, conversacionDos,
                conversacionTres, conversacionCuatro, conversacionCinco, conversacionCinco,
                conversacionSeis, conversacionSiete, conversacionOcho, conversacionNueve,
                conversacionDiez, conversacionOnce, conversacionDoce, conversacionCatorce,
                conversacionQuince, conversacionDieciseis, conversacionDecisiete,
                conversacionDeciocho, conversacionDecinueve, conversacionVeinte};
        return array;
    }

    public Conversacion getConversacion(int id_conversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(id_conversacion);
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        return new Conversacion(mensajes, UsuarioProxy.getUsuario().getNombre(), "Diego");
    }

    public Conversacion getConversacion(String nombreUsuario){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idUsuario=" + nombreUsuario;
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        return new Conversacion(mensajes, UsuarioProxy.getUsuario().getNombre(), "Diego");
    }

    public List<Mensaje> getMensajesNuevos(int id_conversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(id_conversacion);
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        return mensajes;
    }

    public boolean enviarMensaje(Mensaje mensaje){
        boolean statusOk = false;
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
                statusOk = true;
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
        return statusOk;
    }

    public boolean enviarBroadcast(Mensaje mensaje){
        boolean statusOk = false;
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
                statusOk = true;
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
        return statusOk;
    }

}
