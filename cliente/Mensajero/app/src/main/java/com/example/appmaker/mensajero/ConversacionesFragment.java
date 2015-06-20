package com.example.appmaker.mensajero;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;


/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link ConversacionesFragment.OnFragmentInteractionListener} interface
 * to handle interaction events.
 * Use the {@link ConversacionesFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ConversacionesFragment extends Fragment {
    Conversacion[] conversaciones;
    private boolean seguirEscuchando = true;
    private static final int demora = 5000;
    private View viewFragment;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment ConversacionesFragment.
     */
    public static ConversacionesFragment newInstance() {
        ConversacionesFragment fragment = new ConversacionesFragment();
        return fragment;
    }

    public ConversacionesFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    @Override
    public void onPause() {
        super.onDestroy();
        seguirEscuchando = false;
    }

    @Override
    public void onResume() {
        super.onDestroy();
        seguirEscuchando = true;
        escucharLlegadaDeMensajes();
    }

    private void cargarConversaciones() {
        ConversacionAdapter conversacionAdapter = new ConversacionAdapter(getActivity(), conversaciones);
        ListView lista = (ListView) viewFragment.findViewById(R.id.lista_conversaciones);
        lista.setAdapter(conversacionAdapter);
        lista.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Conversacion.actual = conversaciones[position];
                Intent conversacionIntent = new Intent("com.example.appmaker.mensajero.ConversacionActivity");
                startActivity(conversacionIntent);
            }
        });
    }

    private void inicializarConversaciones(Conversacion[] conversaciones) {
        this.conversaciones = conversaciones;
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_conversaciones, container, false);
        viewFragment = v;
        //escucharLlegadaDeMensajes();
        return v;
    }

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
                array = new ConversacionProxy(PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext())).getConversaciones();
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
