package com.example.appmaker.mensajero;

import android.app.Activity;
import android.content.Intent;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversaciones);
        conversaciones = inicializarConverciones();
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
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        ImageButton btnListaUsuariosConectados = (ImageButton)findViewById(R.id.btnListaUsuariosConectados);
        btnListaUsuariosConectados.setOnClickListener(verListaUsuariosConectadosListener);
    }

    private Conversacion[] inicializarConverciones() {
        // TODO conectarse con el servidor para obtejerlas
        // TODO traer los datos del servidor
        return new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getConversaciones();
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

}

