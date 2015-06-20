package com.example.appmaker.mensajero;

import android.content.Intent;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


public class RegistracionActivity extends ActionBarActivity {

    TextView txtNombre;
    TextView txtPassword;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registracion);

        txtNombre = (TextView)findViewById(R.id.txtUser);
        txtPassword = (TextView)findViewById(R.id.txtPassword);
        Button btn = (Button) findViewById(R.id.btnRegistrarse);
        btn.setOnClickListener(btnRegistrarseListener);
    }

    /**
     * Llama al activity de Lista Usuarios Conectados y le pasa el usuario registrado (y logueado)
     */
    private View.OnClickListener btnRegistrarseListener = new View.OnClickListener() {
        public void onClick(View v) {
            if(validarIngreso()) {
                new RegistrarUsuarioAPI().execute(txtNombre.getText().toString(), txtPassword.getText().toString());
            }
        }
    };

    /**
     * Valida que haya información en los campos
     * @return true si hay texto en ambos campos, false en caso contrario
     */
    private boolean validarIngreso(){
        txtNombre.setError(null);
        txtPassword.setError(null);
        boolean cancel = false;
        View focusView = null;
        String nombre = txtNombre.getText().toString();
        String password = txtPassword.getText().toString();

        if (TextUtils.isEmpty(password)) {
            txtPassword.setError(getString(R.string.error_contrasenia_vacia));
            focusView = txtPassword;
            cancel = true;
        }

        if (TextUtils.isEmpty(nombre)) {
            txtNombre.setError(getString(R.string.error_usuario_vacio));
            focusView = txtNombre;
            cancel = true;
        }

        if (cancel) {
            focusView.requestFocus();
            return false;
        } else {
            return true;
        }

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
        switch (id){
            case R.id.action_salir:
                finish();
                break;
        }
        //noinspection SimplifiableIfStatement

        return super.onOptionsItemSelected(item);
    }

    private class RegistrarUsuarioAPI extends AsyncTask<String, Usuario, Usuario> {
        @Override
        protected Usuario doInBackground(String... params) {
            Usuario result = null;
            try {
                result = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).registrar(params[0],params[1]);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return result;
        }

        protected void onPostExecute(Usuario result) {
            if (result == null) {
                Log.e("MensajerO", "Error al intentar registrarse en el servidor");
                Toast.makeText(getApplicationContext(), "No se pudo registrar el usuario en el servidor", Toast.LENGTH_LONG).show();
            }else {
                Intent listaUsuariosConectadosIntent = new Intent("com.example.appmaker.mensajero.ListasTabbedActivity");
                startActivity(listaUsuariosConectadosIntent);
                finish();
            }
        }

    } // end UsuarioAPI
}
