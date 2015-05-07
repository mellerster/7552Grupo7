package com.example.appmaker.mensajero;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;

/**
 * Created by diego on 07/05/15.
 */
public class MainActivity extends Activity {
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
}
