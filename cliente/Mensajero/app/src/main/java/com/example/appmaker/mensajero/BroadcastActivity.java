package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
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
                String mensaje =  nuevoMensaje.getText().toString();
                new EnviarMensajeAPI().execute(mensaje);
                nuevoMensaje.setText("");
            }
        }
    }

    private class EnviarMensajeAPI extends AsyncTask<String, Boolean, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            try {
                String mensaje = params[0];
                return new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).enviarBroadcast(new Mensaje(UsuarioProxy.getUsuario(), mensaje));
            } catch (Exception e) {
                System.out.println(e.getMessage());
                return false;
            }
        }

        protected void onPostExecute(Boolean devolvioAlgo) {
            if(devolvioAlgo) {
                Toast.makeText(getApplicationContext(), "Mensaje Enviado a todos los usuarios conectados correctamente", Toast.LENGTH_LONG).show();
            } else {
                Toast.makeText(getApplicationContext(), "No se pudo enviar el mensaje", Toast.LENGTH_LONG).show();
            }
        }

    } // end EnviarMensajeAPI


}
