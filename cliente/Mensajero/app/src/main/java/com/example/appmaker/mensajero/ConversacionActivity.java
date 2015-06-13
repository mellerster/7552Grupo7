package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.text.Layout;
import android.text.Spanned;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

/**
 * Muestra una pantalla donde se ve la conversacion que se ha tenido con un contacto y un campo para
 * continuar enviandole mensajes.
 */
public class ConversacionActivity  extends Activity {

    private TextView conversacion;
    private EditText nuevoMensaje;
    private Button enviarButton;

    private Conversacion conversacionMantenida;
    //TODO ver de reemplazar por clase como en Conversacion
    private String nombrePropio;
    private static final int demora = 5000;
    private boolean seguirEscuchando = true;

    /**
     * Inicializa la conversacion con la conversacion previa entre estos dos usuarios.
     */
    private void inicializarAtributosConversacion() {
        conversacionMantenida = Conversacion.actual;
        nombrePropio = conversacionMantenida.getConversanteUno().getNombre();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversacion);

        inicializarConversacion();
        inicializarNuevoMensaje();
        inicializarEnviarButton();
        escucharLlegadaDeMensajes();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    private void inicializarConversacion() {
        conversacion = (TextView) findViewById(R.id.conversacion);
        inicializarAtributosConversacion();
        conversacion.setText(conversacionMantenida.getStringFormateado());
        conversacion.setMovementMethod(new ScrollingMovementMethod());
    }

    private void inicializarNuevoMensaje() {
        nuevoMensaje = (EditText) findViewById(R.id.nuevo_mensaje);
        nuevoMensaje.requestFocus();
    }

    private void inicializarEnviarButton() {
        enviarButton = (Button) findViewById(R.id.boton_enviar);
        enviarButton.setOnClickListener(new EnviarMensajeListener());
    }

    private class EnviarMensajeListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if (nuevoMensaje.getText().length() > 0) {
                // TODO enviar al servidor y recepcion de OK
                Mensaje mensajeEnviado = new Mensaje(UsuarioProxy.getUsuario(), nuevoMensaje.getText().toString());
                agregarTextoAConversacion(mensajeEnviado.getStringRemitentePropio());
                nuevoMensaje.setText("");
            }
        }
    }

    private void escucharLlegadaDeMensajes() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                //TODO en este ciclo preguntarle al servidor si hay nuevo mensaje
                int ciclo = 1;
                String NOMBRE_AJENO = "Diego";
                while (seguirEscuchando) {
                    final Mensaje mensajeRecibido = new Mensaje(new Usuario(NOMBRE_AJENO),
                            "Hola soy Diego" + Integer.toString(ciclo));
                    ++ciclo;
                    conversacion.post(new Runnable() {
                        @Override
                        public void run() {
                            agregarTextoAConversacion(mensajeRecibido.getStringRemitenteAjeno());
                        }
                    });
                    try {
                        Thread.sleep(demora);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    /**
     * Agrega un nuevo mensaje a la conversacion y mueve el scroll hacia abajo automaticamente.
     * @param text sera agregado a la conversacion
     */
    private void agregarTextoAConversacion(Spanned text) {
        conversacion.append(text);
        final Layout layout = conversacion.getLayout();
        if(layout != null){
            int scrollDelta = layout.getLineBottom(conversacion.getLineCount() - 1) -
                conversacion.getScrollY() - conversacion.getHeight();
            if(scrollDelta > 0) {
                conversacion.scrollBy(0, scrollDelta);
            }
        }
    }

}
