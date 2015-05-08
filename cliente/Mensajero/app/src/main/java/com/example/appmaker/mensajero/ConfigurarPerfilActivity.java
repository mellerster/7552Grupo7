package com.example.appmaker.mensajero;

import android.graphics.Bitmap;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.view.View.OnClickListener;
import android.widget.Switch;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;

public class ConfigurarPerfilActivity extends ActionBarActivity {


    private static int RESULT_LOAD_IMAGE = 1;

    Usuario usuario;
    Switch swt;
    ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configurar_perfil);
        // Toma el usuario logueado del proxy
        usuario = UsuarioProxy.getUsuario();

        Button btn = (Button) findViewById(R.id.btnCambiarFoto);
        btn.setOnClickListener(cargarImagenListener);

        swt = (Switch) findViewById(R.id.swtEstado);
        swt.setOnClickListener(cambiarEstadoListener);

        imageView= (ImageView) findViewById(R.id.imgFoto);

        cargarDatosUsuario();
    }

    private void cargarDatosUsuario(){
        setEstadoSwitch(usuario.estaConectado());

        byte[] foto = usuario.getFoto();
        if(foto != null){
            imageView.setImageBitmap(usuario.getFotoBitmap());
        }

        TextView lblUsuarioLogueado = (TextView) findViewById(R.id.lblUsuarioLogueado);
        lblUsuarioLogueado.setText(usuario.getNombre());
    }

    private void setEstadoSwitch(boolean estado){
        swt.setChecked(estado);
        if (estado) {
            swt.setText("Conectado");
        } else {
            swt.setText("Desconectado");
        }
    }

    private OnClickListener cargarImagenListener = new OnClickListener() {
        public void onClick(View v) {
            Intent i = new Intent(
                    Intent.ACTION_PICK,
                    android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);

            startActivityForResult(i, RESULT_LOAD_IMAGE);
        }
    };

    private OnClickListener cambiarEstadoListener = new OnClickListener() {
        public void onClick(View v) {
            UsuarioProxy proxy = new UsuarioProxy();
            Switch swt =((Switch) v);
            if (usuario.estaConectado()) {
                proxy.logout(usuario);
                setEstadoSwitch(usuario.estaConectado());
            } else {
                proxy.login(usuario);
                setEstadoSwitch(usuario.estaConectado());
            }
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_configurar_perfil, menu);
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
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK && null != data) {
            byte[] b = getBytesFromLocalImage(data);
            usuario.setFoto(b);
            new UsuarioProxy().cargarFoto(usuario);
            imageView.setImageBitmap(usuario.getFotoBitmap());
            Log.d("Foto",usuario.getFotoBase64());
        }
    }

    /**
     * Obtiene el array de bytes de la imagen seleccionada desde el teléfono
     * @param data Intent que carga la imagen
     * @return tira de bytes de la imagen
     */
    private byte[] getBytesFromLocalImage(Intent data) {
        Uri selectedImage = data.getData();
        String[] filePathColumn = {MediaStore.Images.Media.DATA};
        Cursor cursor = getContentResolver().query(selectedImage, filePathColumn, null, null, null);
        cursor.moveToFirst();

        int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
        String picturePath = cursor.getString(columnIndex);
        cursor.close();

        Bitmap bp = BitmapFactory.decodeFile(picturePath);

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bp.compress(Bitmap.CompressFormat.PNG, 100, baos);
        return baos.toByteArray();
    }
}
