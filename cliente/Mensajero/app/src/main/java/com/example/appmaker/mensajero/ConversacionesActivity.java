package com.example.appmaker.mensajero;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
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
    }

    private Conversacion[] inicializarConverciones() {
        // TODO conectarse con el servidor para obtejerlas
        // TODO traer los datos del servidor
        String NOMBRE_PROPIO = "Tomas";
        Mensaje mensajeUno = new Mensaje(NOMBRE_PROPIO, "Hola, como andas?");
        Mensaje mensajeDos = new Mensaje("Diego", "Hola, bien y vos?");
        Mensaje mensajeTres = new Mensaje(NOMBRE_PROPIO, "Todo bien. Bueno chau!");
        Mensaje mensajeCuatro = new Mensaje("Diego", "Chau!");
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        mensajes.add(mensajeUno);
        mensajes.add(mensajeDos);
        mensajes.add(mensajeTres);
        mensajes.add(mensajeCuatro);
        Conversacion conversacionUno = new Conversacion(mensajes, NOMBRE_PROPIO, "Diego");
        Conversacion conversacionDos = new Conversacion(mensajes, NOMBRE_PROPIO, "Pablo");
        Conversacion conversacionTres = new Conversacion(mensajes, NOMBRE_PROPIO, "Juan");
        Conversacion conversacionCuatro = new Conversacion(mensajes, NOMBRE_PROPIO, "Matias");
        Conversacion conversacionCinco = new Conversacion(mensajes, NOMBRE_PROPIO, "Mariano");
        Conversacion conversacionSeis = new Conversacion(mensajes, NOMBRE_PROPIO, "Tomas");
        Conversacion conversacionSiete = new Conversacion(mensajes, NOMBRE_PROPIO, "Nahuel");
        Conversacion conversacionOcho = new Conversacion(mensajes, NOMBRE_PROPIO, "Victor");
        Conversacion conversacionNueve = new Conversacion(mensajes, NOMBRE_PROPIO, "Oscar");
        Conversacion conversacionDiez = new Conversacion(mensajes, NOMBRE_PROPIO, "Pedro");
        Conversacion conversacionOnce = new Conversacion(mensajes, NOMBRE_PROPIO, "Mateo");
        Conversacion conversacionDoce = new Conversacion(mensajes, NOMBRE_PROPIO, "Marcos");
        Conversacion conversacionCatorce = new Conversacion(mensajes, NOMBRE_PROPIO, "Lucas");
        Conversacion conversacionQuince = new Conversacion(mensajes, NOMBRE_PROPIO, "Romina");
        Conversacion conversacionDieciseis = new Conversacion(mensajes, NOMBRE_PROPIO, "Camila");
        Conversacion conversacionDecisiete = new Conversacion(mensajes, NOMBRE_PROPIO, "Agustina");
        Conversacion conversacionDeciocho = new Conversacion(mensajes, NOMBRE_PROPIO, "Carolina");
        Conversacion conversacionDecinueve = new Conversacion(mensajes, NOMBRE_PROPIO, "Florencia");
        Conversacion conversacionVeinte = new Conversacion(mensajes, NOMBRE_PROPIO, "Abril");
        Conversacion array[] = new Conversacion[] {conversacionUno, conversacionDos,
                conversacionTres, conversacionCuatro, conversacionCinco, conversacionCinco,
                conversacionSeis, conversacionSiete, conversacionOcho, conversacionNueve,
                conversacionDiez, conversacionOnce, conversacionDoce, conversacionCatorce,
                conversacionQuince, conversacionDieciseis, conversacionDecisiete,
                conversacionDeciocho, conversacionDecinueve, conversacionVeinte};
        return array;
    }

}

