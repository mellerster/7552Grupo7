package com.example.appmaker.mensajero;

import android.util.JsonReader;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by diego on 04/05/15.
 */
public class UsuarioParser {
    Usuario usuario;
    InputStream stream;

    public UsuarioParser(Usuario usuario) {
        this.usuario = usuario;
    }

    public UsuarioParser(InputStream inputStream) {
        this.stream = inputStream;
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
                        if (!status.equals("OK")) {
                            Log.e("Obtencion Listado Usuarios Conectados", "Status es: " + status);
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
                    reader.skipValue();
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

    public Usuario readEstadoUsuario() throws  IOException {
        JsonReader reader = new JsonReader(new InputStreamReader(stream, "UTF-8"));
        Usuario usuario = null;
        try {
            readUsuario(reader);
        }
        finally {
            reader.close();
        }
        return usuario;
    }
}
