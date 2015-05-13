package com.example.appmaker.mensajero;

import android.text.Html;
import android.text.Spanned;

import java.io.Serializable;
import java.util.List;

/**
 * Representa a una conversacion.
 */
public class Conversacion implements Serializable {

    public static Conversacion actual;

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

    /**
     *
     * @return representacion de toda la conversacion en un unico String formateado mediante html
     */
    public Spanned getStringFormateado() {
        String resultado = "";
        for (Mensaje mensaje : mensajes) {
            resultado += mensaje.getStringSegunRemitente(conversanteUno);
        }
        return Html.fromHtml(resultado);
    }

    private Spanned inicializarConversacion() {
        if (mensajes.get(0).getRemitente().equals(conversanteUno)) {
            return mensajes.get(0).getStringRemitentePropio();
        }
        return mensajes.get(0).getStringRemitenteAjeno();
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
