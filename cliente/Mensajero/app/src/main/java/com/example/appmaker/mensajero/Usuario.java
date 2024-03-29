package com.example.appmaker.mensajero;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

/**
 * Created by diego on 07/04/15.
 * Clase que contiene toda la información de un usuario, para pasarla entre las activities
 * o contra el servidor.
 */
public class Usuario {
    private String nombre;
    private String password;
    private byte[] foto;
    private boolean conectado;
    private long token;
    private double latitud;
    private double longitud;
    private String checkin;
    private String CheckInFechaHora;

    public Usuario(){
    }

    public Usuario(Usuario original){
        this.nombre = original.nombre;
        this.password = original.password;
        this.foto = original.foto;
        this.conectado = original.conectado;
        this.token = original.token;
        this.checkin = original.checkin;
        this.longitud = original.longitud;
        this.latitud = original.latitud;
        this.CheckInFechaHora = original.CheckInFechaHora;
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

    public long getToken() {
        return token;
    }

    public void setToken(long token) {
        this.token = token;
    }

    public void setPosicion(double latitud, double longitud){
        this.latitud = latitud;
        this.longitud = longitud;
    }

    public double getLatitud(){
        return latitud;
    }

    public double getLongitud(){
        return longitud;
    }

    public String getCheckin() {
        return checkin;
    }

    public void setCheckin(String checkin) {
        this.checkin = checkin;
    }

    public String getCheckInFechaHora() {
        return CheckInFechaHora;
    }

    public void setCheckInFechaHora(String checkInFechaHora) {
        CheckInFechaHora = checkInFechaHora;
    }
}
