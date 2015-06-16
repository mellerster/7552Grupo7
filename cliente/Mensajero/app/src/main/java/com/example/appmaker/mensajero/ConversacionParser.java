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
        List<Conversacion> conversaciones = new ArrayList<>();
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
                            conversaciones.add(readConversacion(reader));
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

        return conversaciones.toArray(new Conversacion[conversaciones.size()]);
    }

    private Conversacion readConversacion(JsonReader reader) throws IOException{
        int IdConversacion = -1;
        String UltimoMensaje = "";
        boolean leido = true;
        List<Usuario> participantes = new ArrayList<>();
        //TODO: SACAR
        participantes.add(new Usuario("Jose"));
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
                case "Mensajes":
                    //TODO: Leer mensajes
                    reader.skipValue();
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return new Conversacion(IdConversacion,new Mensaje(participantes.get(0),UltimoMensaje,leido),UsuarioProxy.getUsuario(),participantes.get(0));
    }
}
