package com.example.appmaker.mensajero;

import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.view.View.OnClickListener;
import java.util.List;


public class ListaUsuariosConectadosActivity extends ActionBarActivity {
    String tag = "Events"; // Tag para usar Log.d y poder filtrar por este tag
    LinearLayout gridUsuarios;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lista_usuarios_conectados);
        gridUsuarios = (LinearLayout) findViewById(R.id.gridUsuarios);

        List<Usuario> usuarios = new UsuarioProxy().getUsuariosConectados();
        MostrarUsuarios(usuarios);

        TextView lblListaConversaciones = (TextView)findViewById(R.id.lblListaConversaciones);
        lblListaConversaciones.setOnClickListener(verListaConversacionesListener);
    }

    private void MostrarUsuarios(List<Usuario> usuarios) {
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        for (Usuario usuario : usuarios) {
            agregarUsuarioALista(usuario,params);
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
                Intent configurarPerfilIntent = new Intent("com.example.appmaker.mensajero.ConfigurarPerfilActivity");
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
                new UsuarioProxy().logout(UsuarioProxy.getUsuario());
                finish();
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
