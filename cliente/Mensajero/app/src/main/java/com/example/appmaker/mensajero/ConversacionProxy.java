package com.example.appmaker.mensajero;

import android.content.SharedPreferences;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
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

    public ConversacionProxy(SharedPreferences sharedPref){
        super(sharedPref);
    }

    /**
     * Obtiene el listado de chats del servidor
     * @return listado de conversaciones con el ultimo mensaje de la conversacion
     */
    public Conversacion[] getConversaciones(){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversaciones";
        Conversacion[] conversaciones = null;
        HttpURLConnection urlConnection = null;
        try {
            urlString += "?Token=" + String.valueOf(token);
            URL url = new URL(urlString);
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setRequestProperty("Content-Type", "application/json");
            Log.i("MensajerO","Obtengo Listado de Conversaciones: ");
            int HttpResult = urlConnection.getResponseCode();
            if (HttpResult == HttpURLConnection.HTTP_OK) {
                InputStream streamAParsear;
                streamAParsear = urlConnection.getInputStream();
                ConversacionParser parser = new ConversacionParser();
                conversaciones = parser.readConversaciones(streamAParsear);
                Log.i("MensajerO", "Información obtenida correctamente");
            } else {
                Log.e("MensajerO", urlConnection.getResponseMessage());
            }
        } catch (EstadoRecibidoInvalidoException e){
            Log.e("MensajerO", e.getMessage());
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
            Log.e("MensajerO", "No se pudo parsar correctamente las conversaciones");
        } finally {
            if (urlConnection != null)
                urlConnection.disconnect();
        }

        return conversaciones;
    }

    /**
     * Obtiene una conversacion y todos sus mensajes por el id de la conversacion
     * @param idConversacion a buscar en el servidor
     * @return La conversacion cargada con todos los mensajes que mande el servidor
     */
    public Conversacion getConversacion(long idConversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(idConversacion);
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<>();
        mensajes.add(mensajeUno);
        return new Conversacion(idConversacion,mensajes, UsuarioProxy.getUsuario(), new Usuario("Jose"));
    }

    /**
     * Obtiene una conversacion y todos sus mensajes por el nombre de usuario
     * @param nombreUsuario a buscar en el servidor la conversacion
     * @return La conversacion cargada con todos los mensajes que mande el servidor
     */
    public Conversacion getConversacion(String nombreUsuario){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idUsuario=" + nombreUsuario;
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<>();
        mensajes.add(mensajeUno);
        return new Conversacion(-1,mensajes, UsuarioProxy.getUsuario(), new Usuario(nombreUsuario));
    }

    /**
     * Obtiene todos los mensajes que no obtuve todavía de la conversacion actual
     * @param idConversacion identificador de la conversacion en el servidor
     * @return Un listado con los mensajes no leidos
     */
    public List<Mensaje> getMensajesNuevos(long idConversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(idConversacion);
        Usuario otro = new Usuario("Juan001");
        List<Mensaje> mensajes = new ArrayList<>();
        mensajes.add(new Mensaje(otro, "Todo bien, vos?"));
        mensajes.add(new Mensaje(UsuarioProxy.getUsuario(), "Bien tambien, Chau"));
        mensajes.add(new Mensaje(otro, "Chau"));
        mensajes.add(new Mensaje(UsuarioProxy.getUsuario(), "Hola, que tal?"));
        return mensajes;
    }

    /**
     * Envia un mensaje a otro usuario via servidor
     * @param mensaje con el texto a enviar
     * @param conversacion para referenciar a la conversacion actual
     * @return Un booleano para ver si el servidor respondio correctamente
     */
    public boolean enviarMensaje(Mensaje mensaje, Conversacion conversacion){
        boolean statusOk = false;
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", token);
            params.put("Mensaje", mensaje.getMensaje());
            params.put("Conversacion", conversacion.getIdConversacion());
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


    /**
     * Envia un mensaje a todos los usuarios que se encuentran activos en el servidor
     * @param mensaje con el texto a enviar
     * @return Un booleano para ver si el servidor respondio correctamente
     */
    public boolean enviarBroadcast(Mensaje mensaje){
        boolean statusOk = false;
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "broadcast";
        JSONObject params = new JSONObject();
        HttpURLConnection urlConnection = null;
        try {
            params.put("Token", token);
            params.put("Mensaje", mensaje.getMensaje());
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
