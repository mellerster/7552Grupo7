package com.example.appmaker.mensajero;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;


public class Registracion extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registracion);

        Button btn = (Button) findViewById(R.id.btnRegistrarse);
        btn.setOnClickListener(btnRegistrarseListener);
    }

    private View.OnClickListener btnRegistrarseListener = new View.OnClickListener() {
        public void onClick(View v) {

            if(validarIngreso()) {
                ///TODO: Pasar el usuario que se registro
                Intent listaUsuariosConectadosIntent = new Intent("com.example.appmaker.mensajero.ListaUsuariosConectados");
                startActivity(listaUsuariosConectadosIntent);
            }
        }
    };

    ///TODO:Validar que ingrese un usuario y una contraseña en los campos
    ///TODO:Llamar al proxy para que valide los datos del usuario
    private boolean validarIngreso(){
        return true;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_registracion, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
