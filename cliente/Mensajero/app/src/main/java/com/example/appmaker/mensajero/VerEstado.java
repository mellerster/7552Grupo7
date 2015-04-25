package com.example.appmaker.mensajero;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;


public class VerEstado extends ActionBarActivity {

    Usuario usuario;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_estado);
        String nombreUsuario = "";
        Bundle extras = getIntent().getExtras();
        if (extras!=null)
        {
            nombreUsuario = extras.getString("usuario");
        }
        usuario = new UsuarioProxy().verEstado(nombreUsuario);
        cargarDatosUsuario();

    }

    private void cargarDatosUsuario(){
        TextView txtNombre = (TextView)findViewById(R.id.txtNombre);
        txtNombre.setText(usuario.getNombre());
        ///TODO: cargar el resto de los datos
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_estado, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_volver) {
            finish();
        }else if (id == R.id.action_enviar_mensaje){
            ///TODO: llamar a la pantalla de conversación y enviarle el usuario a quien le quiere enviar el mensaje
            Log.d("Event","Se quiere enviar un mensaje a " + usuario.getNombre());
        }else if (id == R.id.action_salir){
            ///TODO: Cerrar Sesión desde el proxy y salir de la app.
        }

        return super.onOptionsItemSelected(item);
    }
}
