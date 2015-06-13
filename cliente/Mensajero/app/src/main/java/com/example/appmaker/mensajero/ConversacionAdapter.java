package com.example.appmaker.mensajero;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

/**
 * Created by Tomás on 28/04/2015.
 */
public class ConversacionAdapter extends ArrayAdapter<Conversacion> {

    private Activity context;
    private Conversacion[] conversaciones;

    public ConversacionAdapter(Activity context, Conversacion[] conversaciones) {
        super(context, R.layout.conversacion_adapter, conversaciones);
        this.context = context;
        this.conversaciones = conversaciones;
    }
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) context
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View conversacionView = inflater.inflate(R.layout.conversacion_adapter, parent, false);
        TextView nombreContacto = (TextView) conversacionView.findViewById(R.id.nombre_contacto);
        nombreContacto.setText(conversaciones[position].getConversanteDos().getNombre());
        TextView ultimoMensaje = (TextView) conversacionView.findViewById(R.id.ultimo_mensaje);
        ultimoMensaje.setText(conversaciones[position].getUltimoMensaje());
        return conversacionView;
    }
}


