package com.example.appmaker.mensajero;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ImageButton;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

/**
 * Muestra todas las conversaciones que el usuario ha mantenido y permite seleccionar alguna para
 * continuarla.
 */
public class ConversacionesActivity extends Activity {

    Conversacion[] conversaciones;
    private boolean seguirEscuchando = true;
    private static final int demora = 5000;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversaciones);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        ImageButton btnListaUsuariosConectados = (ImageButton)findViewById(R.id.btnListaUsuariosConectados);
        btnListaUsuariosConectados.setOnClickListener(verListaUsuariosConectadosListener);
        escucharLlegadaDeMensajes();
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
        escucharLlegadaDeMensajes();
    }

    private void cargarConversaciones() {
        ConversacionAdapter conversacionAdapter = new ConversacionAdapter(this, conversaciones);
        ListView lista = (ListView) findViewById(R.id.lista_conversaciones);
        lista.setAdapter(conversacionAdapter);
        lista.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Conversacion.actual = conversaciones[position];
                Intent configurarPerfilIntent = new Intent("com.example.appmaker.mensajero.ConversacionActivity");
                startActivity(configurarPerfilIntent);
            }
        });
    }

    private void inicializarConversaciones(Conversacion[] conversaciones) {
        this.conversaciones = conversaciones;
    }

    private View.OnClickListener verListaUsuariosConectadosListener = new View.OnClickListener()
    {
        public void onClick(View v)
        {
            Intent conversacionesIntent = new Intent("com.example.appmaker.mensajero.ListaUsuariosConectadosActivity");
            startActivity(conversacionesIntent);
            finish();
        }
    };

    private void escucharLlegadaDeMensajes() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (seguirEscuchando) {
                    new ListaChatsAPI().execute();
                    try {
                        Thread.sleep(demora);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    private class ListaChatsAPI extends AsyncTask<String, Conversacion[], Conversacion[]> {
        @Override
        protected Conversacion[] doInBackground(String... params) {
            Conversacion array[] = null;
            try {
                array = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getConversaciones();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return array;
        }

        protected void onPostExecute(Conversacion[] conversaciones) {
            inicializarConversaciones(conversaciones);
            cargarConversaciones();
        }

    } // end ListaChatsAPI

}

