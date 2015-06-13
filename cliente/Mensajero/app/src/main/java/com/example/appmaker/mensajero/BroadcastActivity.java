package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class BroadcastActivity extends Activity {
    private EditText nuevoMensaje;
    private Button enviarButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_broadcast);

        nuevoMensaje = (EditText) findViewById(R.id.nuevo_mensaje);
        nuevoMensaje.requestFocus();

        enviarButton = (Button) findViewById(R.id.boton_enviar_broadcast);
        enviarButton.setOnClickListener(new EnviarMensajeListener());
    }

    private class EnviarMensajeListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if (nuevoMensaje.getText().length() > 0) {
                // TODO enviar al servidor y recepcion de OK
                Mensaje mensajeEnviado = new Mensaje(UsuarioProxy.getUsuario(), nuevoMensaje.getText().toString());
                nuevoMensaje.setText("");
                Toast.makeText(getApplicationContext(), "Mensaje Enviado a todos los usuarios conectados correctamente", Toast.LENGTH_LONG).show();
            }
        }
    }


}
