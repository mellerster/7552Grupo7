package com.example.appmaker.mensajero;

import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.View;
import android.widget.Button;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class CheckinActivity extends FragmentActivity {

    private GoogleMap mapa;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_checkin);
        setUpMapSiEsNecesario();
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
        //TODO reemplazar por codigo que busque la posicion mediante GPS, para poder probarlo en el emulador lo dejo asi por ahora
        return new LatLng(-34.617529, -58.368208);
    }

    private void configurarBoton() {
        Button realizarCheckin = (Button) findViewById(R.id.realizar_checkin_button);
        realizarCheckin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO enviar al servidor la location del usuario para que la registre y hacerlo tambien localmente
                Usuario usuario = UsuarioProxy.getUsuario();
                usuario.setPosicion(getLocation().latitude,getLocation().longitude);
            }
        });
    }

}
