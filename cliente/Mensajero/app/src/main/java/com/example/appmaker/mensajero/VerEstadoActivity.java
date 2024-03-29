package com.example.appmaker.mensajero;

import android.content.Intent;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;


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
        new VerEstadoAPI().execute(nombreUsuario);
        Button btnEnviarMensaje = (Button) findViewById(R.id.btnNuevoMensaje);
        btnEnviarMensaje.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent conversacionIntent = new Intent("com.example.appmaker.mensajero.ConversacionActivity");
                Bundle extras = new Bundle();
                extras.putString("usuario", usuario.getNombre());
                conversacionIntent.putExtras(extras);
                startActivity(conversacionIntent);
                finish();
            }
        });
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setTitle(nombreUsuario);
    }

    private void cargarDatosUsuario(){
        //Cargo el Nombre
        TextView txtNombre = (TextView)findViewById(R.id.txtNombre);
        txtNombre.setText(usuario.getNombre());
        //Cargo el Estado
        TextView txtEstado = (TextView)findViewById(R.id.txtEstado);
        txtEstado.setText(usuario.estaConectado() ? "Conectado" : "Desconectado");
        //Cargo el Checkin
        TextView txtUltimoCheckin = (TextView)findViewById(R.id.txtUltimoCheckin);
        if(!usuario.getCheckin().isEmpty()) {
            String ultimoCheckin = "El " + usuario.getCheckInFechaHora() +
                    " en " + usuario.getCheckin();
            txtUltimoCheckin.setText(ultimoCheckin);
        }
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
        if (id == R.id.action_enviar_mensaje){
            Intent conversacionIntent = new Intent("com.example.appmaker.mensajero.ConversacionActivity");
            Bundle extras = new Bundle();
            extras.putString("usuario", usuario.getNombre());
            conversacionIntent.putExtras(extras);
            startActivity(conversacionIntent);
            finish();
        }

        return super.onOptionsItemSelected(item);
    }

    private class VerEstadoAPI extends AsyncTask<String, Usuario, Usuario> {
        @Override
        protected Usuario doInBackground(String... params) {
            try {
                usuario = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).verEstado(params[0]);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return usuario;
        }

        protected void onPostExecute(Usuario user) {
            //showProgress(false);
            if(user != null) {
                usuario = user;
                cargarDatosUsuario();
            } else {
                Toast.makeText(getApplicationContext(), "No se pudo obtener los datos del usuario en el servidor", Toast.LENGTH_LONG).show();
                Log.e("MensajerO","No se pudo obtener los datos del usuario del servidor");
            }
        }

    } // end UsuarioAPI
}
