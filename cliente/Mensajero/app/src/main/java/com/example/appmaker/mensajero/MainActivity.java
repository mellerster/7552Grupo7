package com.example.appmaker.mensajero;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;

/**
 * Created by diego on 07/05/15.
 */
public class MainActivity extends ActionBarActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        InicializarPreferencias(sharedPref);

        String usuarioGuardado= sharedPref.getString("usuario","");

        if(!usuarioGuardado.isEmpty()){
            Log.d("AutoLogin","Se autologeo con el usuario:" + usuarioGuardado);
            String contraseniaGuardada = sharedPref.getString("contrasenia","");
            new AutentificacionTask(usuarioGuardado,contraseniaGuardada).execute();
        } else {

            Button btnIniciarSesion = (Button) findViewById(R.id.iniciar_sesion_button);
            btnIniciarSesion.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent autentificacionIntent = new Intent("com.example.appmaker.mensajero.AutentificacionActivity");
                    startActivity(autentificacionIntent);
                    finish();
                }
            });

            Button btnRegistrarse = (Button) findViewById(R.id.crear_nueva_cuenta_button);
            btnRegistrarse.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent registracionIntent = new Intent("com.example.appmaker.mensajero.RegistracionActivity");
                    startActivity(registracionIntent);
                    finish();
                }
            });

            Button btnAjustes = (Button) findViewById(R.id.ajustes_button);
            btnAjustes.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View view) {
                    Intent settingsIntent = new Intent("com.example.appmaker.mensajero.SettingsActivity");
                    startActivity(settingsIntent);
                }
            });
        }
    }

    private void InicializarPreferencias(SharedPreferences sharedPref) {
        String urlBase = sharedPref.getString("urlBase", "");
        String puertoBase =sharedPref.getString("puertoBase", "");
        int tiempoEsperaListadoConversaciones = sharedPref.getInt("tiempoConversaciones",-1);
        int tiempoEsperaEnConversacion= sharedPref.getInt("tiempoConversacion",-1);
        int tiempoEsperaListadoUsuarios= sharedPref.getInt("tiempoUsuarios",-1);
        SharedPreferences.Editor editorPreferenciasCompartidas = sharedPref.edit();
        if(urlBase.isEmpty())
            editorPreferenciasCompartidas.putString("urlBase", "http://10.0.2.2");
        if(puertoBase.isEmpty())
            editorPreferenciasCompartidas.putString("puertoBase","8080");
        if(tiempoEsperaListadoConversaciones == -1){
            editorPreferenciasCompartidas.putInt("tiempoConversaciones",15000);
        }
        if(tiempoEsperaEnConversacion == -1){
            editorPreferenciasCompartidas.putInt("tiempoConversacion",5000);
        }
        if(tiempoEsperaListadoUsuarios == -1){
            editorPreferenciasCompartidas.putInt("tiempoUsuarios",15000);
        }

        editorPreferenciasCompartidas.apply();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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
                finish();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * Representa un task asincronico para la autentificacion del usuario.
     */
    public class AutentificacionTask extends AsyncTask<Void, Void, Boolean> {

        private final String usuario;
        private final String contrasenia;

        AutentificacionTask(String usuario, String contrasenia) {
            this.usuario = usuario;
            this.contrasenia = contrasenia;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            Usuario usuario = null;
            usuario = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).login(new Usuario(this.usuario, this.contrasenia));
            return (usuario != null );
        }

        @Override
        protected void onPostExecute(final Boolean success) {
            if (success) {
                Intent listaUsuariosConectadosIntent = new Intent("com.example.appmaker.mensajero.ListasTabbedActivity");
                startActivity(listaUsuariosConectadosIntent);
                finish();
            }
        }

        @Override
        protected void onCancelled() {
        }
    }
}
