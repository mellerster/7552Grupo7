package com.example.appmaker.mensajero;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.text.Layout;
import android.text.Spanned;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.List;

/**
 * Muestra una pantalla donde se ve la conversacion que se ha tenido con un contacto y un campo para
 * continuar enviandole mensajes.
 */
public class ConversacionActivity  extends ActionBarActivity {

    private TextView conversacion;
    private EditText nuevoMensaje;
    private Button enviarButton;
    private String usuarioConvesacionCon = "";

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
        String usuario = "";
        Bundle extras =getIntent().getExtras();
        if(extras != null) {
            usuario = extras.getString("usuario");
            getSupportActionBar().setTitle(usuario);
        }
        new ConversacionMensajesAPI().execute(usuario);
        inicializarNuevoMensaje();
        inicializarEnviarButton();
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    @Override
    protected void onPause() {
        super.onPause();
        seguirEscuchando = false;
    }

    @Override
    protected void onResume() {
        super.onResume();
        seguirEscuchando = true;
        if(conversacionMantenida != null && fueInicializado)
            escucharLlegadaDeMensajes();
    }

    private void inicializarConversacion() {
        conversacion.setText(conversacionMantenida.getStringFormateado());
        conversacion.setMovementMethod(new ScrollingMovementMethod());
        usuarioConvesacionCon =conversacionMantenida.getConversanteDos().getNombre();
        getSupportActionBar().setTitle(usuarioConvesacionCon);
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

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_conversacion, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_ver_estado){
            Intent estadoIntent = new Intent("com.example.appmaker.mensajero.VerEstadoActivity");
            Bundle extras = new Bundle();
            extras.putString("usuario", usuarioConvesacionCon);
            estadoIntent.putExtras(extras);
            startActivity(estadoIntent);
            finish();
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConversacionMensajesAPI extends AsyncTask<String, Boolean, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            try {
                String usuario = params[0];
                if(usuario == null || usuario.isEmpty())
                    conversacionMantenida = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getConversacion(Conversacion.actual.getIdConversacion());
                else
                    conversacionMantenida = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getConversacion(usuario);
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
