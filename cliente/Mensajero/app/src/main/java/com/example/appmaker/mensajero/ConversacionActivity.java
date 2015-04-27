package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

/**
 * Muestra una pantalla donde se ve la conversacion que se ha tenido con un contacto y un campo para
 * continuar enviandole mensajes.
 */
public class ConversacionActivity  extends Activity {

    private EditText conversacion;
    private EditText nuevoMensaje;
    private Button enviarButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversacion);

        conversacion = (EditText) findViewById(R.id.conversacion);
        conversacion.setEnabled(false);
        nuevoMensaje = (EditText) findViewById(R.id.nuevo_mensaje);
        enviarButton = (Button) findViewById(R.id.boton_enviar);
    }

}
