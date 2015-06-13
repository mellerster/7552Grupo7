package com.example.appmaker.mensajero;

import android.content.SharedPreferences;

/**
 * Created by diego on 12/06/15.
 */
public class ProxyBase {
    protected String url = "http://10.0.2.2";
    protected String puerto = "8080";
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
