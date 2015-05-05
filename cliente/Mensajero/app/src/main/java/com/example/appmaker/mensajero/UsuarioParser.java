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
                            ///TODO: Crear Excepcion: EstadoRecibidoInvalidoException
                            Log.e("Obtencion Listado Usuarios Conectados", "Status es: " + status);
                            throw new IOException();
                        }
                        break;
                    case "Usuarios":
                        reader.beginArray();

                        while (reader.hasNext()) {
                            usuarios.add(readUsuarioListado(reader));
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

    public Usuario readUsuarioListado(JsonReader reader) throws IOException {
        Usuario usuario = null;

        reader.beginObject();
        while (reader.hasNext()) {
            String name = reader.nextName();
            switch (name) {
                case "Nombre":
                    usuario = new Usuario(reader.nextString());
                    usuario.conectar();
                    break;
                default:
                    reader.skipValue();
            }
        }
        reader.endObject();
        return usuario;
    }
}
