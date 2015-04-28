package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.ArrayList;
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
    //TODO ver de reemplazar por clase como en Conversacion
    private String nombrePropio;
    private static final int demora = 5000;
    private boolean seguirEscuchando = true;

    /**
     * Inicializa la conversacion con la conversacion previa entre estos dos usuarios.
     */
    private void inicializarAtributosConversacion() {
        // TODO traer los datos del servidor
        String NOMBRE_PROPIO = "Tomas";
        String NOMBRE_AJENO = "Diego";
        Mensaje mensajeUno = new Mensaje(NOMBRE_PROPIO, "Hola, como andas?");
        Mensaje mensajeDos = new Mensaje(NOMBRE_AJENO, "Hola, bien y vos?");
        Mensaje mensajeTres = new Mensaje(NOMBRE_PROPIO, "Todo bien. Bueno chau!");
        Mensaje mensajeCuatro = new Mensaje(NOMBRE_AJENO, "Chau!");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        mensajes.add(mensajeDos);
        mensajes.add(mensajeTres);
        mensajes.add(mensajeCuatro);
        nombrePropio = NOMBRE_PROPIO;
        conversacionMantenida = new Conversacion(mensajes, NOMBRE_PROPIO, NOMBRE_AJENO);
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
        conversacion.setText(conversacionMantenida.toString());
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
                Mensaje mensajeEnviado = new Mensaje(nombrePropio, nuevoMensaje.getText().toString());
                conversacion.append(mensajeEnviado.toString());
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
                    final Mensaje mensajeRecibido = new Mensaje(NOMBRE_AJENO,
                            "Hola soy Diego" + Integer.toString(ciclo));
                    ++ciclo;
                    conversacion.post(new Runnable() {
                        @Override
                        public void run() {
                            conversacion.append(mensajeRecibido.toString());
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

}
