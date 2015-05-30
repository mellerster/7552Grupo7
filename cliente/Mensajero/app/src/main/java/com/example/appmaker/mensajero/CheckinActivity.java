package com.example.appmaker.mensajero;

import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class CheckinActivity extends FragmentActivity {

    private GoogleMap mapa;
    GPSTracker gps;
    Usuario usuario;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_checkin);
        setUpMapSiEsNecesario();
        usuario = new Usuario(UsuarioProxy.getUsuario());
        configurarBoton();
    }

    @Override
    protected void onResume() {
        super.onResume();
        setUpMapSiEsNecesario();
    }

    private void setUpMapSiEsNecesario() {
        if (mapa == null) {
            mapa = ((SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map))
                    .getMap();
            if (mapa != null) {
                setUpMap();
            }
        }
    }

    private void setUpMap() {
        LatLng location = getLocation();
        mapa.addMarker(new MarkerOptions().position(location).title(getString(R.string.mi_posicion)));
        mapa.moveCamera(CameraUpdateFactory.newLatLng(location));
    }

    private LatLng getLocation() {
        //Utilizacion de la clase de http://www.androidhive.info/2012/07/android-gps-location-manager-tutorial
        gps = new GPSTracker(CheckinActivity.this);
        double latitude = -34.617529;
        double longitude = -58.368208;
        // check if GPS enabled
        if(gps.canGetLocation()){

            latitude = gps.getLatitude();
            longitude = gps.getLongitude();
            gps.stopUsingGPS();
            // \n is for new line
            //TODO:Quitar es solo para debbug
            Toast.makeText(getApplicationContext(), "Your Location is - \nLat: " + latitude + "\nLong: " + longitude, Toast.LENGTH_LONG).show();
        }else{
            // can't get location
            // GPS or Network is not enabled
            // Ask user to enable GPS/network in settings
            gps.showSettingsAlert();
        }
        /*

        Para poder probar la aplicacion con el emulador se debe hacer lo siguiente en una consola
        telnet localhost 5554
        geo fix -34.617529 -58.368208
        Esto envia la latitud y longitud deseada al dispositivo

        */
        return new LatLng(latitude, longitude);
    }

    private void configurarBoton() {
        Button realizarCheckin = (Button) findViewById(R.id.realizar_checkin_button);
        realizarCheckin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO enviar al servidor la location del usuario para que la registre y hacerlo tambien localmente
                usuario.setPosicion(getLocation().latitude,getLocation().longitude);
                new CheckInAPI().execute();
            }
        });
    }

    private class CheckInAPI extends AsyncTask<String, Boolean, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            boolean result = false;
            try {
                usuario = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).realizarCheckin(usuario);
                result = true;
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return result;
        }

        protected void onPostExecute(Boolean result) {
            if (!result) {
                Log.e("MensajerO", "Error al intentar guardar la posicion en el servidor");
                Toast.makeText(getApplicationContext(), "Error al intentar guardar la posicion en el servidor", Toast.LENGTH_LONG).show();
            }else {
                Toast.makeText(getApplicationContext(), "Todos los cambios guardados", Toast.LENGTH_LONG).show();
            }
        }

    } // end CheckInAPI

}
