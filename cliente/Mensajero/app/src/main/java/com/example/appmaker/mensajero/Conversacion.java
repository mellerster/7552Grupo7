package com.example.appmaker.mensajero;

import java.util.List;

/**
 * Representa a una conversacion.
 */
public class Conversacion {

    private List<Mensaje> mensajes;
    // TODO ver de reemplazar por clases que los representen
    private String conversanteUno;
    private String conversanteDos;

    public Conversacion(List<Mensaje> mensajes, String conversanteUno, String conversanteDos) {
        this.mensajes = mensajes;

        this.conversanteUno = conversanteUno;
        this.conversanteDos = conversanteDos;
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

    public String getConversanteUno() {
        return conversanteUno;
    }

    public String getConversanteDos() {
        return conversanteDos;
    }

    /**
     *
     * @return cuerpo del ultimo mensaje de esta conversacion
     */
    public String getUltimoMensaje() {
        return mensajes.get(mensajes.size()-1).getMensaje();
    }
}
