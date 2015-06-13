package com.example.appmaker.mensajero;

import android.text.Html;
import android.text.Spanned;

/**
 * Clase que representa un mensaje que envia un remitente.
 */
public class Mensaje {

    private static final String CODIGO_COLOR_MENSAJE_PROPIO = "009DA5";
    private static final String CODIGO_COLOR_MENSAJE_AJENO = "00A555";

    private Usuario remitente;
    private String mensaje;
    private boolean leido;

    public Mensaje(Usuario remitente, String mensaje) {
        this.remitente = remitente;
        this.mensaje = mensaje;
        this.leido = true;
    }

    public Mensaje(Usuario remitente, String mensaje, boolean leido){
        this.remitente = remitente;
        this.mensaje = mensaje;
        this.leido = leido;
    }

    @Override
    /**
     * @return representacion del mensaje para ser mostrada en una conversacion
     */
    public String toString() {
       return remitente.getNombre() +" dice" + ": \n" + mensaje + "\n\n";
    }

    /**
     *
     * @return si el remitente pasado por parametro es igual al remitente de este mensaje devuelve
     * el mensaje formateado para un remitente propio, caso contrario lo hace para un remitente
     * ajeno
     */
    public String getStringSegunRemitente(String remitente) {
        if (this.remitente.getNombre().equals(remitente)) {
            return getStringRemitentePropioSinFormatear();
        }
        return getStringRemitenteAjenoSinFormatear();
    }

    /**
     *
     * @return representacion del mensaje para ser mostrada en una conversacion cuando el remitente
     * es el usuario de la aplicacion
     */
    public Spanned getStringRemitentePropio() {
        return getMensajeFormateado(CODIGO_COLOR_MENSAJE_PROPIO);
    }

    /**
     *
     * @return representacion del mensaje para ser mostrada en una conversacion cuando el remitente
     * es un contacto del usuario de la aplicacion
     */
    public Spanned getStringRemitenteAjeno() {
        return getMensajeFormateado(CODIGO_COLOR_MENSAJE_AJENO);
    }

    private Spanned getMensajeFormateado(String codigoColor) {
        String texto = "<font color=#" + codigoColor + ">" + remitente +" dice" + ": <br>" + mensaje +
                "<br><br></font>";
        return Html.fromHtml(texto);
    }

    /**
     *
     * @return representacion del mensaje para ser mostrada en una conversacion cuando el remitente
     * es el usuario de la aplicacion sin formatear
     */
    public String getStringRemitentePropioSinFormatear() {
        return getMensajeSinFormatear(CODIGO_COLOR_MENSAJE_PROPIO);
    }

    /**
     *
     * @return representacion del mensaje para ser mostrada en una conversacion cuando el remitente
     * es un contacto del usuario de la aplicacion sin formatear
     */
    public String getStringRemitenteAjenoSinFormatear() {
        return getMensajeSinFormatear(CODIGO_COLOR_MENSAJE_AJENO);
    }

    private String getMensajeSinFormatear(String codigoColor) {
        String texto = "<font color=#" + codigoColor + ">" + remitente +" dice" + ": <br>" + mensaje +
                "<br><br></font>";
        return texto;
    }

    public Usuario getRemitente() {
        return remitente;
    }

    public String getMensaje() {
        return mensaje;
    }

    public boolean fueLeido(){
        return this.leido;
    }
}
