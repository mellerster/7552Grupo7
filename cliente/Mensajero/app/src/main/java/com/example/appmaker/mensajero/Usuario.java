package com.example.appmaker.mensajero;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.Image;
import android.util.Base64;

/**
 * Created by diego on 07/04/15.
 */
public class Usuario {
    private String nombre;
    private String password;
    private byte[] foto;
    private boolean conectado;

    public Usuario(){
    }

    public Usuario(String nombre, String password){
        this.nombre = nombre;
        this.password = password;
    }

    public Usuario(String nombre){
        this.nombre = nombre;
    }

    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    public String getNombre(){
        return this.nombre;
    }

    public String getPassword(){
        return this.password;
    }

    public byte[] getFoto(){
        return this.foto;
    }

    public Bitmap getFotoBitmap() {
        return BitmapFactory.decodeByteArray(foto, 0, foto.length);
    }

    public String getFotoBase64(){
        return Base64.encodeToString(getFoto(), Base64.DEFAULT);
    }

    public void setFoto(byte[] foto){
        this.foto = foto;
    }

    public void setFoto(String base64){
        this.foto = Base64.decode(base64,Base64.DEFAULT);
    }

    public String toString(){
        return this.getNombre();
    }

    public void conectar(){
        this.conectado = true;
    }

    public void desconectar(){
        this.conectado = false;
    }

    public boolean estaConectado(){
        return (conectado == true);
    }

}
