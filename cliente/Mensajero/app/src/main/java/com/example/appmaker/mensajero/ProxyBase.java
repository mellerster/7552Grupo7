package com.example.appmaker.mensajero;

import android.content.SharedPreferences;

/**
 * Created by diego on 12/06/15.
 * Clase base de los proxys
 */
public class ProxyBase {
    /**
     * Url base donde esta la ip o nombre del servidor
     */
    protected String url = "http://10.0.2.2";
    /**
     * Puerto al cual se conecta en el servidor
     */
    protected String puerto = "8080";
    /**
     * Concatenacion de la url y del puerto junto con el directorio donde esta la api
     */
    protected String urlBase = url+":"+puerto+"/grupo7/api/";

    /***
     * Constructor que obtiene las preferencias de la actividad para obtener la direccion y puerto del servidor
     * Tambien almacena la url base de la restAPI
     * @param sharedPref
     */
    public ProxyBase(SharedPreferences sharedPref){
        String urlBase = sharedPref.getString("urlBase", url);
        String puertoBase =sharedPref.getString("puertoBase", puerto);
        this.url = urlBase;
        this.puerto = puertoBase;
        this.urlBase = url+":"+puerto+"/grupo7/api/";
    }
}
