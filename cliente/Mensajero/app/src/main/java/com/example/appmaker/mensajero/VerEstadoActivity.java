package com.example.appmaker.mensajero;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.TextView;


public class VerEstadoActivity extends ActionBarActivity {

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
        //Cargo el Nombre
        TextView txtNombre = (TextView)findViewById(R.id.txtNombre);
        txtNombre.setText(usuario.getNombre());
        //Cargo el Estado
        TextView txtEstado = (TextView)findViewById(R.id.txtEstado);
        txtEstado.setText(usuario.estaConectado() ? "Conectado" : "Desconectado");
        //Cargo el Checkin
        ///TODO: Cargar el último check in cuando este programada esa funcionalidad
        TextView txtUltimoCheckin = (TextView)findViewById(R.id.txtUltimoCheckin);
        txtUltimoCheckin.setText("El 15 de Septiembre de 2015 a las 14:30hs en Facultad de Ingeniería, UBA");
        //Cargo la imagen
        ImageView ivFoto = (ImageView)findViewById(R.id.imgFoto);
        ivFoto.setImageResource(R.drawable.no_user);
        if(usuario.getFoto() != null){
            ivFoto.setImageBitmap(usuario.getFotoBitmap());
        }
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
            Intent conversacionIntent = new Intent("com.example.appmaker.mensajero.ConversacionActivity");
            Bundle extras = new Bundle();
            extras.putString("usuario",usuario.getNombre());
            conversacionIntent.putExtras(extras);
            startActivity(conversacionIntent);
            Log.d("Event","Se quiere enviar un mensaje a " + usuario.getNombre());
        }

        return super.onOptionsItemSelected(item);
    }
}
