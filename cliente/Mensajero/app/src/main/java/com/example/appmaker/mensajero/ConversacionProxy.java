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

    public ConversacionProxy(SharedPreferences sharedPref){
        super(sharedPref);
    }

    public Conversacion[] getConversaciones(){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversaciones?Token=" + String.valueOf(token);
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Ultimo Mensaje");
        Conversacion conversacionUno = new Conversacion(1,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Diego"));
        mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Ultimo Mensaje No Leido",false);
        Conversacion conversacionDos = new Conversacion(2,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Pablo"));
        Conversacion conversacionTres = new Conversacion(3,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Juan"));
        mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Ultimo Mensaje");
        Conversacion conversacionCuatro = new Conversacion(4,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Matias"));
        Conversacion conversacionCinco = new Conversacion(5,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Mariano"));
        Conversacion conversacionSeis = new Conversacion(6,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Tomas"));
        Conversacion conversacionSiete = new Conversacion(7,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Nahuel"));
        Conversacion conversacionOcho = new Conversacion(8,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Victor"));
        Conversacion conversacionNueve = new Conversacion(9,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Oscar"));
        Conversacion conversacionDiez = new Conversacion(10,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Pedro"));
        Conversacion conversacionOnce = new Conversacion(11,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Mateo"));
        Conversacion conversacionDoce = new Conversacion(12,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Marcos"));
        Conversacion conversacionCatorce = new Conversacion(14,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Lucas"));
        Conversacion conversacionQuince = new Conversacion(15,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Romina"));
        Conversacion conversacionDieciseis = new Conversacion(16,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Camila"));
        Conversacion conversacionDecisiete = new Conversacion(17,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Agustina"));
        Conversacion conversacionDeciocho = new Conversacion(18,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Carolina"));
        Conversacion conversacionDecinueve = new Conversacion(19,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Florencia"));
        Conversacion conversacionVeinte = new Conversacion(20,mensajeUno, UsuarioProxy.getUsuario(), new Usuario("Abril"));
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
        return new Conversacion(-1,mensajes, UsuarioProxy.getUsuario(), new Usuario("Diego"));
    }

    public Conversacion getConversacion(String nombreUsuario){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "conversacion?Token=" + String.valueOf(token);
        urlString += "&idUsuario=" + nombreUsuario;
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        return new Conversacion(-1,mensajes, UsuarioProxy.getUsuario(), new Usuario("Diego"));
    }

    public List<Mensaje> getMensajesNuevos(int idConversacion){
        long token = UsuarioProxy.getUsuario().getToken();
        String urlString = urlBase + "mensajes?Token=" + String.valueOf(token);
        urlString += "&idConversacion=" + String.valueOf(idConversacion);
        Mensaje mensajeUno = new Mensaje(UsuarioProxy.getUsuario(), "Hola, como andas?");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        return mensajes;
    }

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
