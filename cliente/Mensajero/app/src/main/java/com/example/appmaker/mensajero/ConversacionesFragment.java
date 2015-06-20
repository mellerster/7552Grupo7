package com.example.appmaker.mensajero;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ImageButton;
import android.widget.ListView;

import java.util.List;


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
    private static int demora = 5000;
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
        demora = PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext()).getInt("tiempoConversaciones",15000);
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
        asignarListenersABotones();
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

    private void asignarListenersABotones() {
        ImageButton btnMiPerfil = (ImageButton)viewFragment.findViewById(R.id.btnMiPerfil);
        btnMiPerfil.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent("com.example.appmaker.mensajero.ConfigurarPerfilActivity"));
            }
        });

        ImageButton btnCheckin = (ImageButton)viewFragment.findViewById(R.id.btnCheckin);
        btnCheckin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent("com.example.appmaker.mensajero.CheckinActivity"));
            }
        });

        ImageButton btnBroadcast = (ImageButton)viewFragment.findViewById(R.id.btnBroadcast);
        btnBroadcast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent("com.example.appmaker.mensajero.BroadcastActivity"));
            }
        });

        ImageButton btnCerrarSesion = (ImageButton)viewFragment.findViewById(R.id.btnCerrarSesion);
        btnCerrarSesion.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new UsuarioLogoutAPI().execute();
            }
        });
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

    private class UsuarioLogoutAPI extends AsyncTask<String, Void, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            //showProgress(true);
            Boolean success = true;
            try {
                new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext())).logout(UsuarioProxy.getUsuario());
            } catch (Exception e) {
                System.out.println(e.getMessage());
                success = false;
            }
            return success;
        }

        protected void onPostExecute(Boolean success) {
            //Borro los datos del usuario conectado
            SharedPreferences preferenciasCompartidas = PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext());
            SharedPreferences.Editor editorPreferenciasCompartidas = preferenciasCompartidas.edit();
            editorPreferenciasCompartidas.putString("usuario", "");
            editorPreferenciasCompartidas.putString("contrasenia", "");
            editorPreferenciasCompartidas.apply();
            //Envío a la pantalla de login
            Intent autentificacionIntent =new Intent("com.example.appmaker.mensajero.AutentificacionActivity");
            startActivity(autentificacionIntent);
            getActivity().finish();
        }

    } // end UsuarioLogoutAPI
}
