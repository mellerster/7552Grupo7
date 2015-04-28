package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Scroller;
import android.text.method.ScrollingMovementMethod;

/**
 * Muestra una pantalla donde se ve la conversacion que se ha tenido con un contacto y un campo para
 * continuar enviandole mensajes.
 */
public class ConversacionActivity  extends Activity {

    private EditText conversacion;
    private EditText nuevoMensaje;
    private Button enviarButton;

    private Conversacion conversacionMantenida;
    private String nombrePropio;
    private String nombreAjeno;

    // TODO aca simulamos la obtencion de una conversacion ya existente
    private static String NOMBRE_PROPIO = "Tomas";
    private static String NOMBRE_AJENO = "Diego";
    private static final Mensaje mensajeUno = new Mensaje(NOMBRE_PROPIO, NOMBRE_AJENO, "Hola, como andas?");
    private static final Mensaje mensajeDos = new Mensaje(NOMBRE_AJENO, NOMBRE_PROPIO, "Hola, bien y vos?");
    private static final Mensaje mensajeTres = new Mensaje(NOMBRE_PROPIO, NOMBRE_AJENO, "Todo bien. Bueno chau!");
    private static final Mensaje mensajeCuatro = new Mensaje(NOMBRE_AJENO, NOMBRE_PROPIO, "Chau!");

    /**
     * Inicializa la conversacion con la conversacion previa entre estos dos usuarios.
     */
    private void inicializarAtributosConversacion() {
        nombrePropio = NOMBRE_PROPIO;
        nombreAjeno = NOMBRE_AJENO;
        conversacionMantenida = new Conversacion();
        conversacionMantenida.agregarMensaje(mensajeUno);
        conversacionMantenida.agregarMensaje(mensajeDos);
        //conversacionMantenida.agregarMensaje(mensajeCuatro);
        //conversacionMantenida.agregarMensaje(mensajeTres);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversacion);

        conversacion = (EditText) findViewById(R.id.conversacion);
        conversacion.setEnabled(false);
        inicializarAtributosConversacion();
        conversacion.setText(conversacionMantenida.toString());
        conversacion.setFocusableInTouchMode(true);
        conversacion.setScroller(new Scroller(ConversacionActivity.this));
        conversacion.setVerticalScrollBarEnabled(true);
        conversacion.setMovementMethod(new ScrollingMovementMethod());

        nuevoMensaje = (EditText) findViewById(R.id.nuevo_mensaje);
        nuevoMensaje.requestFocus();
        enviarButton = (Button) findViewById(R.id.boton_enviar);
        enviarButton.setOnClickListener(new EnviarMensajeListener());
    }

    private class EnviarMensajeListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if (nuevoMensaje.getText().length() > 0) {
                // TODO enviar al servidor y recepcion de OK
                conversacionMantenida.agregarMensaje(new Mensaje(nombrePropio, nombreAjeno,
                        nuevoMensaje.getText().toString()));
                conversacion.setText(conversacionMantenida.toString());
                nuevoMensaje.setText("");
            }
        }
    }

}
