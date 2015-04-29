package com.example.appmaker.mensajero;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

/**
 * Muestra todas las conversaciones que el usuario ha mantenido y permite seleccionar alguna para
 * continuarla.
 */
public class ConversacionesActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversaciones);
        Conversacion[] conversaciones = inicializarConverciones();
        ConversacionAdapter conversacionAdapter = new ConversacionAdapter(this, conversaciones);
        ListView listview = (ListView) findViewById(R.id.lista_conversaciones);
        listview.setAdapter(conversacionAdapter);
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
        Conversacion array[] = new Conversacion[] {conversacionUno, conversacionDos,
                conversacionTres, conversacionCuatro, conversacionCinco};
        return array;
    }

}

