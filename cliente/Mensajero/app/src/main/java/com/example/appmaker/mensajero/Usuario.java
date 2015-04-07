package com.example.appmaker.mensajero;

import android.media.Image;

/**
 * Created by diego on 07/04/15.
 */
public class Usuario {
    private String nombre;
    private String password;
    private Image foto;

    public Usuario(String nombre, String password){
        this.nombre = nombre;
        this.password = password;
    }

    public String getNombre(){
        return this.nombre;
    }

    public String getPassword(){
        return this.password;
    }

    public Image getFoto(){
        return this.foto;
    }

    public void setFoto(Image foto){
        this.foto = foto;
    }

    public String toString(){
        return this.getNombre();
    }

}
