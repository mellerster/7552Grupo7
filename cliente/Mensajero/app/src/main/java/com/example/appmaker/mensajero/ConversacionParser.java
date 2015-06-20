package com.example.appmaker.mensajero;

import android.util.JsonReader;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by diego on 16/06/15.
 */
public class ConversacionParser {

    public Conversacion[] readConversaciones(InputStream stream) throws IOException{
        List<Conversacion> conversacionesNoLeidas = new ArrayList<>();
        List<Conversacion> conversacionesLeidas = new ArrayList<>();
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();
                switch (name) {
                    case "Status":
                        String status = reader.nextString();
                        if (!status.equals("OK")) {
                            Log.e("MensajerO", "Status es: " + status);
                            throw new EstadoRecibidoInvalidoException();
                        }
                        break;
                    case "Conversaciones":
                        reader.beginArray();
                        while (reader.hasNext()) {
                            Conversacion conversacion =readConversacion(reader);
                            if(!conversacion.getMensajes().isEmpty()){
                                if(conversacion.getMensajes().get(0).fueLeido()){
                                    conversacionesLeidas.add(conversacion);
                                }else {
                                    conversacionesNoLeidas.add(conversacion);
                                }
                            } else {
                                conversacionesLeidas.add(conversacion);
                            }
                        }
                        reader.endArray();
                        break;
                    default:
                        reader.skipValue();
                        break;
                }
            }
        } finally {
            reader.close();
        }
        conversacionesNoLeidas.addAll(conversacionesLeidas);
        return conversacionesNoLeidas.toArray(new Conversacion[conversacionesNoLeidas.size()]);
    }

    private Conversacion readConversacion(JsonReader reader) throws IOException{
        int IdConversacion = -1;
        String UltimoMensaje = "";
        boolean leido = true;
        List<Usuario> participantes = new ArrayList<>();
        List<Mensaje> mensajes = new ArrayList<>();
        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "IDConversacion":
                    IdConversacion = reader.nextInt();
                    break;
                case "UltimoMensaje":
                    UltimoMensaje = reader.nextString();
                    break;
                case "UltimoMensajeLeido":
                    leido = reader.nextBoolean();
                    break;
                case "Participantes":
                    reader.beginArray();
                    while (reader.hasNext()) {
                        String nombreUsuario =reader.nextString();
                        if(!nombreUsuario.equals(UsuarioProxy.getUsuario().getNombre()))
                            participantes.add(new Usuario(nombreUsuario));
                    }
                    reader.endArray();
                    break;
                case "IDUsuario":
                    participantes.add(new Usuario(reader.nextString()));
                    break;
                case "Mensajes":
                    reader.beginArray();
                    while (reader.hasNext()){
                        mensajes.add(readMensaje(reader));
                    }
                    reader.endArray();
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        //TODO: SACAR CUANDO DEVUELVA LOS PARTICIPANTES O EL IDUSUARIO CORRECTAMENTE
        participantes.add(new Usuario("Jose"));
        return new Conversacion(IdConversacion,new Mensaje(participantes.get(0),UltimoMensaje,leido),UsuarioProxy.getUsuario(),participantes.get(0));
    }

    public Conversacion readConversacion(InputStream stream) throws IOException{
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        Conversacion conversacion = null;
        try {
            conversacion = readConversacion(reader);
        } finally {
            reader.close();
        }
        return  conversacion;
    }

    private Mensaje readMensaje(JsonReader reader) throws IOException{
        String idRemitente = "";
        String mensajeCuerpo = "";
        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "IDRemitente":
                    idRemitente = reader.nextString();
                    break;
                case "Mensaje":
                    mensajeCuerpo = reader.nextString();
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return new Mensaje(new Usuario(idRemitente),mensajeCuerpo);
    }
}
