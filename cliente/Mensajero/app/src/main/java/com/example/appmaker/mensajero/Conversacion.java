package com.example.appmaker.mensajero;

import android.text.Html;
import android.text.Spanned;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Representa a una conversacion.
 */
public class Conversacion implements Serializable {

    public static Conversacion actual;
    private long idConversacion;

    private List<Mensaje> mensajes;
    private Usuario conversanteUno;
    private Usuario conversanteDos;

    public Conversacion(long idConversacion, List<Mensaje> mensajes, Usuario conversanteUno, Usuario conversanteDos) {
        this.mensajes = mensajes;
        this.conversanteUno = conversanteUno;
        this.conversanteDos = conversanteDos;
        this.idConversacion = idConversacion;
    }

    public Conversacion(long idConversacion, Mensaje mensaje, Usuario conversanteUno, Usuario conversanteDos){
        this.mensajes = new ArrayList<Mensaje>();
        this.mensajes.add(mensaje);
        this.conversanteUno = conversanteUno;
        this.conversanteDos = conversanteDos;
        this.idConversacion = idConversacion;
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
            resultado += mensaje.getStringSegunRemitente(conversanteUno.getNombre());
        }
        return Html.fromHtml(resultado);
    }

    private Spanned inicializarConversacion() {
        if (mensajes.get(0).getRemitente().equals(conversanteUno)) {
            return mensajes.get(0).getStringRemitentePropio();
        }
        return mensajes.get(0).getStringRemitenteAjeno();
    }

    public Usuario getConversanteUno() {
        return conversanteUno;
    }

    public Usuario getConversanteDos() {
        return conversanteDos;
    }

    /**
     *
     * @return cuerpo del ultimo mensaje de esta conversacion
     */
    public Spanned getUltimoMensaje() {
        String textoMensaje = "";
        if(mensajes.size() > 0) {
            Mensaje ultimoMensaje = mensajes.get(mensajes.size() - 1);
            if (ultimoMensaje.fueLeido()) {
                textoMensaje = ultimoMensaje.getMensaje();
            } else {
                textoMensaje = "<b>" + ultimoMensaje.getMensaje() + "</b>";
            }
        }
        return Html.fromHtml(textoMensaje);
    }

    /**
     *
     * @return el id de la conversacion para comunicacion con el servidor
     */
    public long getIdConversacion(){
        return this.idConversacion;
    }
}
