package com.example.appmaker.mensajero;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

/**
 * Created by diego on 07/05/15.
 */
public class MainActivity extends ActionBarActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        String usuarioGuardado= sharedPref.getString("usuario","");
        if(!usuarioGuardado.isEmpty()){
            Log.d("AutoLogin","Se autologeo con el usuario:" + usuarioGuardado);
            String contraseniaGuardada = sharedPref.getString("contrasenia","");
            new UsuarioProxy().login(new Usuario(usuarioGuardado,contraseniaGuardada));
            Intent listaUsuariosConectadosIntent = new Intent("com.example.appmaker.mensajero.ListaUsuariosConectadosActivity");
            startActivity(listaUsuariosConectadosIntent);
            finish();
        }

        Button btnIniciarSesion = (Button)findViewById(R.id.iniciar_sesion_button);
        btnIniciarSesion.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent autentificacionIntent =new Intent("com.example.appmaker.mensajero.AutentificacionActivity");
                startActivity(autentificacionIntent );
                finish();
            }
        });

        Button btnRegistrarse = (Button)findViewById(R.id.crear_nueva_cuenta_button);
        btnRegistrarse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent registracionIntent =new Intent("com.example.appmaker.mensajero.RegistracionActivity");
                startActivity(registracionIntent);
                finish();
            }
        });
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
}
