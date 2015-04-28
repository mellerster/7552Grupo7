package com.example.appmaker.mensajero;

import java.util.ArrayList;
import java.util.List;

/**
 * Representa a una conversacion.
 */
public class Conversacion {

    private List<Mensaje> mensajes;

    public Conversacion() {
        mensajes = new ArrayList<Mensaje>();
    }

    /**
     *
     * @param mensaje sera agregado a los mensajes de la conversacion
     */
    public void agregarMensaje(Mensaje mensaje) {
        mensajes.add(mensaje);
    }

    /**
     *
     * @return todos los mensajes de esta conversacion
     */
    public List<Mensaje> getMensajes() {
        return mensajes;
    }

    @Override
    /**
     *
     * @return representacion de toda la conversacion en un unico String
     */
    public String toString() {
        String resultado = "";
        for (Mensaje mensaje : mensajes) {
            resultado += mensaje.toString();
        }
        return resultado;
    }

}
