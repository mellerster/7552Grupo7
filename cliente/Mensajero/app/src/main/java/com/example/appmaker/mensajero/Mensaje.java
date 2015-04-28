package com.example.appmaker.mensajero;

/**
 * Clase que representa un mensaje que envia un remitente.
 */
public class Mensaje {

    private String remitente;
    private String mensaje;

    public Mensaje(String remitente, String mensaje) {
        this.remitente = remitente;
        this.mensaje = mensaje;
    }

    @Override
    /**
     * @return representacion del mensaje para ser mostrada en una conversacion
     */
    public String toString() {
       return remitente +" dice" + ": \n" + mensaje + "\n\n";
    }

}
