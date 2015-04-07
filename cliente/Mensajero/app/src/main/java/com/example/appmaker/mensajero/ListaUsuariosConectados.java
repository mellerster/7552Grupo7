package com.example.appmaker.mensajero;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.view.View.OnClickListener;
import java.util.LinkedList;
import java.util.List;


public class ListaUsuariosConectados extends ActionBarActivity {
    String tag = "Events"; // Tag para usar Log.d y poder filtrar por este tag

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lista_usuarios_conectados);
        List<Usuario> usuarios = obtenerUsuarios();
        MostrarUsuarios(usuarios);
    }

    //TODO:Llamar al proxy y obtener el listado desde la API
    private List<Usuario> obtenerUsuarios() {
        List<Usuario> usuarios = new LinkedList<Usuario>();
        usuarios.add(new Usuario("diego", "diego"));
        usuarios.add(new Usuario("cesar", "cesar"));
        usuarios.add(new Usuario("ramiro", "ramiro"));
        usuarios.add(new Usuario("tomas", "tomas"));
        return usuarios;
    }

    //TODO: Mostar mas información como pide el enunciado y en un diseño mejor
    private void MostrarUsuarios(List<Usuario> usuarios) {
        LinearLayout gridUsuarios = (LinearLayout) findViewById(R.id.gridUsuarios);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.FILL_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        for (Usuario usuario : usuarios) {
            TextView nombre = new TextView(this);
            nombre.setText(usuario.getNombre());
            nombre.setLayoutParams(params);
            nombre.setOnClickListener(usuarioClickListener);
            gridUsuarios.addView(nombre);
        }
    }

    private OnClickListener usuarioClickListener = new OnClickListener()
    {
        public void onClick(View v)
        {
            String nombreUsuario = ((TextView)v).getText().toString();
            Intent verEstadoIntent =new Intent("com.example.appmaker.mensajero.VerEstado");
            Bundle extras = new Bundle();
            extras.putString("usuario",nombreUsuario);
            verEstadoIntent.putExtras(extras);
            startActivity(verEstadoIntent);
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
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
