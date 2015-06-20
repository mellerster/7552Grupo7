package com.example.appmaker.mensajero;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

public class ListadoUsuariosConectadosFragment extends Fragment {
    private boolean seguirEscuchando = true;
    private static int demora = 5000;
    LinearLayout gridUsuarios;
    private View mProgressView;
    private View mListaUsuariosFormView;
    private View viewFragment;
    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment ListadoUsuariosConectadosFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static ListadoUsuariosConectadosFragment newInstance() {
        ListadoUsuariosConectadosFragment fragment = new ListadoUsuariosConectadosFragment();
        return fragment;
    }

    public ListadoUsuariosConectadosFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        demora = PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext()).getInt("tiempoUsuarios",15000);
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
        escucharUsuariosConectados();
    }

    private void escucharUsuariosConectados() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (seguirEscuchando) {
                    new ListaUsuariosAPI().execute();
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

    private void MostrarUsuarios(List<Usuario> usuarios) {
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        params.setMargins(2,2,5,2);
        gridUsuarios.removeAllViews();
        if(usuarios != null) {
            for (Usuario usuario : usuarios) {
                if (!usuario.getNombre().equals(UsuarioProxy.getUsuario().getNombre())){
                    if(usuario.estaConectado())
                        agregarUsuarioALista(usuario, params);
                }
            }
        } else {
            Toast.makeText(getActivity().getApplicationContext(), "No se pudo obtener listado de usuarios del servidor", Toast.LENGTH_LONG).show();
        }
    }

    private void agregarUsuarioALista(Usuario usuario,LinearLayout.LayoutParams params){
        int fotoWidth = 100;
        int fotoHeight = 100;
        LinearLayout llUsuario = new LinearLayout(getActivity());
        llUsuario.setLayoutParams(params);
        llUsuario.setOrientation(LinearLayout.HORIZONTAL);
        // Muestro la foto
        ImageView ivFoto = new ImageView(getActivity());
        ///TODO: Cambiar la foto por el icono de la app si en algun momento tenemos uno
        ivFoto.setImageResource(R.drawable.no_user);
        LinearLayout.LayoutParams fotoParams = new LinearLayout.LayoutParams(fotoWidth,fotoHeight);
        ivFoto.setLayoutParams(fotoParams);
        if(usuario.getFotoBitmap() != null){
            ivFoto.setImageBitmap(Bitmap.createScaledBitmap(usuario.getFotoBitmap(), fotoWidth, fotoHeight, true));
        }
        llUsuario.addView(ivFoto);
        // Muestro el nombre
        TextView tvNombre = new TextView(getActivity());
        tvNombre.setText(usuario.getNombre());
        llUsuario.setOnClickListener(usuarioClickListener);
        llUsuario.addView(tvNombre);
        gridUsuarios.addView(llUsuario);
    }

    private View.OnClickListener usuarioClickListener = new View.OnClickListener()
    {
        public void onClick(View v)
        {
            String nombreUsuario = ((TextView)((LinearLayout)v).getChildAt(1)).getText().toString();
            Intent verEstadoIntent = new Intent("com.example.appmaker.mensajero.VerEstadoActivity");
            Bundle extras = new Bundle();
            extras.putString("usuario",nombreUsuario);
            verEstadoIntent.putExtras(extras);
            startActivity(verEstadoIntent);
        }
    };

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_listado_usuarios_conectados, container, false);
        viewFragment = v;
        gridUsuarios = (LinearLayout) v.findViewById(R.id.gridUsuarios);

        mListaUsuariosFormView = v.findViewById(R.id.form_lista_usuarios);
        mProgressView = v.findViewById(R.id.lista_usuarios_progress);

        //new ListaUsuariosAPI().execute();

        asignarListenersABotones();
        return v;
    }


    /**
     * Muestra el progreso.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    public void showProgress(final boolean show) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            int shortAnimTime = getResources().getInteger(android.R.integer.config_shortAnimTime);

            mListaUsuariosFormView.setVisibility(show ? View.GONE : View.VISIBLE);
            mListaUsuariosFormView.animate().setDuration(shortAnimTime).alpha(
                    show ? 0 : 1).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mListaUsuariosFormView.setVisibility(show ? View.GONE : View.VISIBLE);
                }
            });

            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
            mProgressView.animate().setDuration(shortAnimTime).alpha(
                    show ? 1 : 0).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
                }
            });
        } else {
            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
            mListaUsuariosFormView.setVisibility(show ? View.GONE : View.VISIBLE);
        }
    }

    private class ListaUsuariosAPI extends AsyncTask<String, List<Usuario>, List<Usuario>> {
        @Override
        protected List<Usuario> doInBackground(String... params) {
            //showProgress(true);
            List<Usuario> usuarios = null;
            try {
                usuarios = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getActivity().getBaseContext())).getUsuariosConectados();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return usuarios;
        }

        protected void onPostExecute(List<Usuario> usuarios) {
            //showProgress(false);
            MostrarUsuarios(usuarios);
        }

    } // end ListaUsuariosAPI
    //
    private class UsuarioLogoutAPI extends AsyncTask<String, Void, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            //showProgress(true);
            List<Usuario> usuarios = null;
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
            startActivity(autentificacionIntent );
            getActivity().finish();
        }

    } // end UsuarioLogoutAPI

}
