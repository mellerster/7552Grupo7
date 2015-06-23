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
 * Clase encargada de transformar la respuesta del servidor en objetos del cliente
 */
public class ConversacionParser {

    /**
     * Lee la respuesta del servidor y la tranforma en un vector de conversaciones
     * @param stream del servidor a leer
     * @return vector con las conversaciones, primero las no leidas y luego las leidas
     * @throws IOException
     */
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
                            Conversacion conversacion =readConversacionDeLista(reader);
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

    /**
     * Lee una conversacion de la lista, es un metodo interno para agrupar codigo.
     * @param reader el jsonreader con la información.
     * @return una conversacion con el último mensaje enviado de la misma.
     * @throws IOException
     */
    private Conversacion readConversacionDeLista(JsonReader reader) throws IOException{
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
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return new Conversacion(IdConversacion,new Mensaje(participantes.get(0),UltimoMensaje,leido),UsuarioProxy.getUsuario(),participantes.get(0));
    }

    /**
     * Lee una conversacion completa
     * @param reader jsonreader con la información
     * @return Una conversacion con todos sus mensajes.
     * @throws IOException
     */
    private Conversacion readConversacion(JsonReader reader) throws IOException {
        int IdConversacion = -1;
        Usuario usuarioConversacionCon = null;
        List<Mensaje> mensajes = new ArrayList<>();
        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "IDConversacion":
                    IdConversacion = reader.nextInt();
                    break;
                case "IDUsuario":
                    usuarioConversacionCon = new Usuario(reader.nextString());
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
        return new Conversacion(IdConversacion,mensajes,UsuarioProxy.getUsuario(),usuarioConversacionCon);
    }

    /**
     * Metodo publico para leer una conversacion con todos sus mensajes
     * @param stream el stream que envia el servidor
     * @return un objeto Conversacion completo
     * @throws IOException
     */
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

    /**
     * Metodo privado para parsear un mensaje
     * @param reader el jsonreader con la información a parsear
     * @return Un objeto Mensaje con el usuario remitente y el cuerpo del mismo
     * @throws IOException
     */
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

    /**
     * Obtiene un listado de mensajes a partir del stream que envia el servidor
     * @param stream que envia el servidor con la información
     * @return Un listado tipado de objetos Mensaje
     * @throws IOException
     */
    public List<Mensaje> readMensajes(InputStream stream) throws IOException {
        List<Mensaje> mensajes = new ArrayList<>();
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        try{
		reader.beginObject();
		while(reader.hasNext()){
		    String name = reader.nextName();
		    switch (name) {
		        case "IDConversacion":
		            reader.skipValue();
		            break;
		        case "Mensajes":
		            reader.beginArray();
		            while (reader.hasNext()) {
		                Mensaje mensaje = readMensaje(reader);
		                mensajes.add(mensaje);
		            }
		            reader.endArray();
		            break;
		        default:
		            reader.skipValue();
		    }
		}
        } finally {
        	reader.close();
        }
        
        return mensajes;
    }
}
