package com.example.appmaker.mensajero;

import android.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

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

    private List<Usuario> obtenerUsuarios() {
        List<Usuario> usuarios = new LinkedList<Usuario>();
        usuarios.add(new Usuario("diego", "diego"));
        usuarios.add(new Usuario("cesar", "cesar"));
        usuarios.add(new Usuario("ramiro", "ramiro"));
        usuarios.add(new Usuario("tomas", "tomas"));
        return usuarios;
    }

    private void MostrarUsuarios(List<Usuario> usuarios) {
        LinearLayout gridUsuarios = (LinearLayout) findViewById(R.id.gridUsuarios);
        for (Usuario usuario : usuarios) {
            TextView nombre = new TextView(this);
            nombre.setText(usuario.getNombre());
            LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.FILL_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT);
            nombre.setLayoutParams(params);
            gridUsuarios.addView(nombre);
        }
    }


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
