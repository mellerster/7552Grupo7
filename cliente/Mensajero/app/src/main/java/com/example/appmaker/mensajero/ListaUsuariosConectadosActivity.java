package com.example.appmaker.mensajero;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Build;
import android.preference.PreferenceManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.view.View.OnClickListener;
import java.util.List;


public class ListaUsuariosConectadosActivity extends Activity {
    String tag = "MensajerO"; // Tag para usar Log.d y poder filtrar por este tag
    LinearLayout gridUsuarios;
    private View mProgressView;
    private View mListaUsuariosFormView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lista_usuarios_conectados);
        gridUsuarios = (LinearLayout) findViewById(R.id.gridUsuarios);

        new ListaUsuariosAPI().execute();

        ImageButton btnListaConversaciones = (ImageButton)findViewById(R.id.btnListaConversaciones);
        btnListaConversaciones.setOnClickListener(verListaConversacionesListener);

        mListaUsuariosFormView = findViewById(R.id.form_lista_usuarios);
        mProgressView = findViewById(R.id.lista_usuarios_progress);

        asignarListenersABotones();
    }

    private void asignarListenersABotones() {
        ImageButton btnMiPerfil = (ImageButton)findViewById(R.id.btnMiPerfil);
        btnMiPerfil.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent("com.example.appmaker.mensajero.ConfigurarPerfilActivity"));
            }
        });

        ImageButton btnCheckin = (ImageButton)findViewById(R.id.btnCheckin);
        btnCheckin.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent("com.example.appmaker.mensajero.CheckinActivity"));
            }
        });

        ImageButton btnBroadcast = (ImageButton)findViewById(R.id.btnBroadcast);
        btnBroadcast.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                //startActivity(new Intent("com.example.appmaker.mensajero.CheckinActivity"));
                ///TODO: Llamar a la activity de Broadcast
                Log.d(tag, "Enviar Mensaje de Broadcast");
            }
        });

        ImageButton btnCerrarSesion = (ImageButton)findViewById(R.id.btnCerrarSesion);
        btnCerrarSesion.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).logout(UsuarioProxy.getUsuario());
                //Borro los datos del usuario conectado
                SharedPreferences preferenciasCompartidas = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
                SharedPreferences.Editor editorPreferenciasCompartidas = preferenciasCompartidas.edit();
                editorPreferenciasCompartidas.putString("usuario", "");
                editorPreferenciasCompartidas.putString("contrasenia", "");
                editorPreferenciasCompartidas.apply();
                //Envío a la pantalla de login
                Intent autentificacionIntent =new Intent("com.example.appmaker.mensajero.AutentificacionActivity");
                startActivity(autentificacionIntent );
                finish();
            }
        });
    }

    private void MostrarUsuarios(List<Usuario> usuarios) {
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        if(usuarios != null) {
            for (Usuario usuario : usuarios) {
                agregarUsuarioALista(usuario, params);
            }
        }
    }

    private void agregarUsuarioALista(Usuario usuario,LinearLayout.LayoutParams params){
        int fotoWidth = 100;
        int fotoHeight = 100;
        LinearLayout llUsuario = new LinearLayout(this);
        llUsuario.setLayoutParams(params);
        llUsuario.setOrientation(LinearLayout.HORIZONTAL);
        // Muestro la foto
        ImageView ivFoto = new ImageView(this);
        ///TODO: Cambiar la foto por el icono de la app si en algun momento tenemos uno
        ivFoto.setImageResource(R.drawable.no_user);
        LinearLayout.LayoutParams fotoParams = new LinearLayout.LayoutParams(fotoWidth,fotoHeight);
        ivFoto.setLayoutParams(fotoParams);
        if(usuario.getFoto() != null){
            ivFoto.setImageBitmap(Bitmap.createScaledBitmap(usuario.getFotoBitmap(), fotoWidth, fotoHeight, true));
        }
        llUsuario.addView(ivFoto);
        // Muestro el nombre
        TextView tvNombre = new TextView(this);
        tvNombre.setText(usuario.getNombre());
        llUsuario.setOnClickListener(usuarioClickListener);
        llUsuario.addView(tvNombre);
        gridUsuarios.addView(llUsuario);
    }

    private OnClickListener usuarioClickListener = new OnClickListener()
    {
        public void onClick(View v)
        {
            String nombreUsuario = ((TextView)((LinearLayout)v).getChildAt(1)).getText().toString();
            Intent verEstadoIntent =new Intent("com.example.appmaker.mensajero.VerEstadoActivity");
            Bundle extras = new Bundle();
            extras.putString("usuario",nombreUsuario);
            verEstadoIntent.putExtras(extras);
            startActivity(verEstadoIntent);
        }
    };

    private OnClickListener verListaConversacionesListener = new OnClickListener()
    {
        public void onClick(View v)
        {
            Intent conversacionesIntent = new Intent("com.example.appmaker.mensajero.ConversacionesActivity");
            startActivity(conversacionesIntent);
            finish();
        }
    };


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_lista_usuarios_conectados, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        switch (id){
            case R.id.action_salir:
                new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).logout(UsuarioProxy.getUsuario());
                finish();
                break;
        }
        return super.onOptionsItemSelected(item);
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
                usuarios = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).getUsuariosConectados();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return usuarios;
        }

        protected void onPostExecute(List<Usuario> usuarios) {
            //showProgress(false);
            MostrarUsuarios(usuarios);
        }

    } // end UsuarioAPI
}
