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

public class ConfigurarPerfil extends ActionBarActivity {


    private static int RESULT_LOAD_IMAGE = 1;

    Usuario usuario;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configurar_perfil);
        Bundle extras = getIntent().getExtras();
        if (extras!=null)
        {
            usuario = new UsuarioProxy().getUsuario(extras.getString("usuarioLogueado"));
        }

        Button btn = (Button) findViewById(R.id.btnCambiarFoto);
        btn.setOnClickListener(cargarImagenListener);

        Switch swt = (Switch) findViewById(R.id.swtEstado);
        swt.setOnClickListener(cambiarEstadoListener);
        //Cargo los datos del usuario

        ///TODO: Extraer metodo
        swt.setChecked(usuario.estaConectado());

        byte[] foto = usuario.getFoto();
        if(foto != null){
            ImageView imageView = (ImageView) findViewById(R.id.imgFoto);

            Bitmap bmp = BitmapFactory.decodeByteArray(foto, 0, foto.length);
            imageView.setImageBitmap(bmp);
        }

        TextView lblUsuarioLogueado = (TextView) findViewById(R.id.lblUsuarioLogueado);
        lblUsuarioLogueado.setText(usuario.getNombre());

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
            ///TODO:Ver si el cambio debe ser por proxy o solamente por estado del objeto
            UsuarioProxy proxy = new UsuarioProxy();
            Switch swt =((Switch) v);
            if (usuario.estaConectado()) {
                proxy.logout(usuario);
                swt.setChecked(false);
                swt.setText("Desconectado");
            } else {
                proxy.login(usuario);
                swt.setChecked(true);
                swt.setText("Conectado");
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
        if (id == R.id.action_settings) {
            return true;
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

        ImageView imageView = (ImageView) findViewById(R.id.imgFoto);
        Bitmap bp = BitmapFactory.decodeFile(picturePath);
        imageView.setImageBitmap(bp);

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bp.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        return baos.toByteArray();
    }
}
