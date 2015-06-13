package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.text.Layout;
import android.text.Spanned;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.List;

/**
 * Muestra una pantalla donde se ve la conversacion que se ha tenido con un contacto y un campo para
 * continuar enviandole mensajes.
 */
public class ConversacionActivity  extends Activity {

    private TextView conversacion;
    private EditText nuevoMensaje;
    private Button enviarButton;

    private Conversacion conversacionMantenida;
    private static final int demora = 5000;
    private boolean seguirEscuchando = true;
    private boolean fueInicializado = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversacion);
        conversacionMantenida = null;
        conversacion = (TextView) findViewById(R.id.conversacion);
        new ConversacionMensajesAPI().execute();
        inicializarNuevoMensaje();
        inicializarEnviarButton();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    @Override
    protected void onPause() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    @Override
    protected void onResume() {
        super.onDestroy();
        seguirEscuchando = true;
        if(conversacionMantenida != null && fueInicializado)
            escucharLlegadaDeMensajes();
    }

    private void inicializarConversacion() {
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

                while (seguirEscuchando) {
                    List<Mensaje> mensajesRecibidos = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getMensajesNuevos(conversacionMantenida.getIdConversacion());
                    for(final Mensaje mensajeRecibido : mensajesRecibidos){
                        conversacion.post(new Runnable() {
                            @Override
                            public void run() {
                                if(mensajeRecibido.getRemitente().getNombre().equals(UsuarioProxy.getUsuario().getNombre())){
                                    agregarTextoAConversacion(mensajeRecibido.getStringRemitentePropio());
                                }else {
                                    agregarTextoAConversacion(mensajeRecibido.getStringRemitenteAjeno());
                                }
                            }
                        });
                    }
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

    private class ConversacionMensajesAPI extends AsyncTask<String, Boolean, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            try {
                conversacionMantenida = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getConversacion(Conversacion.actual.getIdConversacion());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return conversacionMantenida != null;
        }

        protected void onPostExecute(Boolean devolvioAlgo) {
            if(devolvioAlgo) {
                inicializarConversacion();
                escucharLlegadaDeMensajes();
                fueInicializado = true;
            }
        }

    } // end ConversacionMensajesAPI

}
