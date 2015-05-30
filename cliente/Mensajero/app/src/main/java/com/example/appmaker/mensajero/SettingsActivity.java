package com.example.appmaker.mensajero;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class SettingsActivity extends ActionBarActivity {
    EditText txtUrl;
    EditText txtPuerto;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        txtUrl = (EditText) findViewById(R.id.txtUrlBase);
        txtPuerto = (EditText) findViewById(R.id.txtPuertoBase);

        cargarAjustes();

        Button btn = (Button) findViewById(R.id.guardar_ajustes_button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                guardarAjustes();
            }
        });
    }

    private void cargarAjustes() {
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        String urlBase = sharedPref.getString("urlBase", "");
        txtUrl.setText(urlBase);
        String puertoBase =sharedPref.getString("puertoBase", "");
        txtPuerto.setText(puertoBase);
    }

    private void guardarAjustes() {
        if(validarDatos()){
            SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
            SharedPreferences.Editor editorPreferenciasCompartidas = sharedPref.edit();
            if(!txtUrl.getText().toString().isEmpty())
                editorPreferenciasCompartidas.putString("urlBase", txtUrl.getText().toString());
            if(!txtPuerto.getText().toString().isEmpty())
                editorPreferenciasCompartidas.putString("puertoBase",txtPuerto.getText().toString());

            editorPreferenciasCompartidas.commit();
            Toast.makeText(getApplicationContext(), "Todos los cambios guardados", Toast.LENGTH_LONG).show();
        }
    }

    private boolean validarDatos(){
        txtUrl.setError(null);
        txtPuerto.setError(null);

        String url = txtUrl.getText().toString();
        String puerto = txtPuerto.getText().toString();

        boolean cancel = false;
        View focusView = null;

        if (TextUtils.isEmpty(url)) {
            txtUrl.setError("La url o ip no puede estar vacia");
            focusView = txtUrl;
            cancel = true;
        }

        if (TextUtils.isEmpty(puerto)) {
            txtPuerto.setError("El puerto no puede estar vacio");
            focusView = txtPuerto;
            cancel = true;
        }

        if (cancel) {
            focusView.requestFocus();
        }
        return !cancel;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_settings, menu);
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
