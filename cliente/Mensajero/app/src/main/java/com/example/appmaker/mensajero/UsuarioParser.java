package com.example.appmaker.mensajero;

import android.system.Os;
import android.util.JsonReader;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by diego on 04/05/15.
 */
public class UsuarioParser {
    Usuario usuario;
    InputStream stream;
    boolean statusOk = false;

    public UsuarioParser(InputStream inputStream) {
        this.stream = inputStream;
    }

    public boolean getStatusOk(){
        return this.statusOk;
    }

    public List<Usuario> getListadoUsuariosConectados() throws IOException {
        List<Usuario> usuarios = new ArrayList<>();
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();
                switch (name) {
                    case "Status":
                        String status = reader.nextString();
                        statusOk = true;
                        if (!status.equals("OK")) {
                            Log.e("MensajerO", "Status es: " + status);
                            statusOk = false;
                            throw new EstadoRecibidoInvalidoException();
                        }
                        break;
                    case "Usuarios":
                        reader.beginArray();
                        while (reader.hasNext()) {
                            usuarios.add(readUsuario(reader));
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
        return usuarios;
    }

    public Usuario readUsuario(JsonReader reader) throws IOException {
        Usuario usuario = new Usuario();
        usuario.conectar();

        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "Nombre":
                    usuario.setNombre(reader.nextString());
                    break;
                case "Estado":
                    String estado = reader.nextString();
                    if(estado.equals("C")){
                        usuario.conectar();
                    }else {
                        usuario.desconectar();
                    }
                    break;
                case "Checkin":
                    usuario.setCheckin(reader.nextString());
                    break;
                case "Foto":
                    String base64 = reader.nextString();
                    usuario.setFoto(base64);
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return usuario;
    }


    /**
     * Obtiene el status y el token del usuario
     * @return El token correspondiente al login
     * @throws IOException dado que tiene que leer un json
     */
    public long readLoginResponse() throws  IOException {
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        long token = 0;
        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();
                switch (name) {
                    case "Status":
                        String status = reader.nextString();
                        statusOk = true;
                        if (!status.equals("OK")) {
                            Log.e("MensajerO", "Status es: " + status);
                            statusOk = false;
                            throw new EstadoRecibidoInvalidoException();
                        }
                        break;
                    case "Token":
                        token = reader.nextLong();
                        Log.d("Token",Long.toString(token));
                        break;
                    default:
                        reader.skipValue();
                }
            }
        }
        finally {
            reader.close();
        }
        return token;
    }

    public void parseStatus() throws  IOException {
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();
                switch (name) {
                    case "Status":
                        String status = reader.nextString();
                        statusOk = true;
                        if (!status.equals("OK")) {
                            Log.e("MensajerO", "Status es: " + status);
                            statusOk = false;
                            throw new EstadoRecibidoInvalidoException();
                        }
                        break;
                    default:
                        reader.skipValue();
                }
            }
        }
        finally {
            reader.close();
        }

    }

    public String parseCheckin() throws  IOException {
        String checkin = "";
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();
                switch (name) {
                    case "Status":
                        String status = reader.nextString();
                        statusOk = true;
                        if (!status.equals("OK")) {
                            Log.e("MensajerO", "Status es: " + status);
                            statusOk = false;
                            throw new EstadoRecibidoInvalidoException();
                        }
                        break;
                    case "Checkin":
                        checkin = reader.nextString();
                        break;
                    default:
                        reader.skipValue();
                }
            }
        }
        finally {
            reader.close();
        }
        return checkin;
    }

    public Usuario leerUsuario() throws IOException {
        return this.readUsuario(new JsonReader(new InputStreamReader(stream, "UTF-8")));
    }
}
