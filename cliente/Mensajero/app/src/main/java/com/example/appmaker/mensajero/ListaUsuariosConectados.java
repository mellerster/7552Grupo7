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
        List<Usuario> usuarios = new UsuarioProxy().getUsuariosConectados();
        MostrarUsuarios(usuarios);

        TextView lblListaConversaciones = (TextView)findViewById(R.id.lblListaConversaciones);
        lblListaConversaciones.setOnClickListener(verListaConversacionesListener);
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

    private OnClickListener verListaConversacionesListener = new OnClickListener()
    {
        public void onClick(View v)
        {
            ///TODO: Llamar a la activity para mostrar Lista de Conversaciones
            Log.d(tag,"Ver Lista de Conversaciones");
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
            case R.id.action_mi_perfil:
                Intent configurarPerfilIntent = new Intent("com.example.appmaker.mensajero.ConfigurarPerfil");
                startActivity(configurarPerfilIntent);
                break;
            case R.id.action_enviar_mensaje_broadcast:
                ///TODO: Llamar a la activity de Broadcast
                Log.d(tag,"Enviar Mensaje de Broadcast");
                break;
            case R.id.action_checkin:
                ///TODO: Llamar a la activity de Checkin
                Log.d(tag,"Realizar Checkin");
                break;
            case R.id.action_salir:
                ///TODO: Realizar logout y Salir
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
