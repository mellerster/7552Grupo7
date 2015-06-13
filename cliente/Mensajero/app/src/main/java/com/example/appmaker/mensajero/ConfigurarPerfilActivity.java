package com.example.appmaker.mensajero;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Build;
import android.preference.PreferenceManager;
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
import android.widget.GridLayout;
import android.widget.ImageView;
import android.view.View.OnClickListener;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.util.List;

public class ConfigurarPerfilActivity extends ActionBarActivity {


    private static int RESULT_LOAD_IMAGE = 1;

    Usuario usuario;
    Switch swt;
    ImageView imageView;
    TextView lblUltimoCheckin;
    private View mProgressView;
    private View mConfigurarPerfilView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configurar_perfil);
        mConfigurarPerfilView = findViewById(R.id.configurar_perfil_panel);
        mProgressView = findViewById(R.id.configurar_perfil_progress);

        // Toma el usuario logueado del proxy
        copiarUsuarioDelProxy();
        Button btn = (Button) findViewById(R.id.btnCambiarFoto);
        btn.setOnClickListener(cargarImagenListener);

        swt = (Switch) findViewById(R.id.swtEstado);
        swt.setOnClickListener(cambiarEstadoListener);

        imageView= (ImageView) findViewById(R.id.imgFoto);
        lblUltimoCheckin = (TextView) findViewById(R.id.lblUltimoCheckin);
        //cargarDatosUsuario();
        new VerEstadoAPI().execute();
    }

    private void copiarUsuarioDelProxy() {
        usuario = new Usuario(UsuarioProxy.getUsuario());
    }

    private void cargarDatosUsuario(){
        if(usuario != null) {
            setEstadoSwitch(usuario.estaConectado());

            byte[] foto = usuario.getFoto();
            if (foto != null) {
                imageView.setImageBitmap(usuario.getFotoBitmap());
            }

            lblUltimoCheckin.setText(usuario.getCheckin());

            TextView lblUsuarioLogueado = (TextView) findViewById(R.id.lblUsuarioLogueado);
            lblUsuarioLogueado.setText(usuario.getNombre());
        }
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
            if (usuario.estaConectado()) {
                usuario.desconectar();
            } else {
                usuario.conectar();
            }
            new ConfigurarPerfilAPI().execute();
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
            new ConfigurarPerfilAPI().execute();
        } else {
            Toast.makeText(getApplicationContext(), "No se pudo cargar la foto, intente de nuevo mas tarde", Toast.LENGTH_LONG).show();
            Log.e("MensajerO","Error al cargar la foto, el result fue: "+ resultCode);
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

    /**
     * Muestra el progreso.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    public void showProgress(final boolean show) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            int shortAnimTime = getResources().getInteger(android.R.integer.config_shortAnimTime);

            mConfigurarPerfilView.setVisibility(show ? View.GONE : View.VISIBLE);
            mConfigurarPerfilView.animate().setDuration(shortAnimTime).alpha(
                    show ? 0 : 1).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mConfigurarPerfilView.setVisibility(show ? View.GONE : View.VISIBLE);
                }
            });

            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
            mProgressView.animate().setDuration(shortAnimTime).alpha(
                    show ? 1 : 0).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
                }
            });
        } else {
            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
            mConfigurarPerfilView.setVisibility(show ? View.GONE : View.VISIBLE);
        }
    }

    private class ConfigurarPerfilAPI extends AsyncTask<String, Boolean, Boolean> {
        @Override
        protected Boolean doInBackground(String... params) {
            boolean result = false;
            try {
                result = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).actualizarPerfil(usuario);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return result;
        }

        protected void onPostExecute(Boolean result) {
            if (!result) {
                copiarUsuarioDelProxy();
                Log.e("MensajerO", "Error al intentar guardar el perfil en el servidor");
                Toast.makeText(getApplicationContext(), "No se pudo guardar los cambios en el servidor", Toast.LENGTH_LONG).show();
            }else {
                Toast.makeText(getApplicationContext(), "Todos los cambios guardados", Toast.LENGTH_LONG).show();
            }
            cargarDatosUsuario();
        }

    } // end ConfigurarPerfilAPI

    private class VerEstadoAPI extends AsyncTask<String, Usuario, Usuario> {
        @Override
        protected Usuario doInBackground(String... params) {
            try {
                usuario = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).verEstado(usuario.getNombre());
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

    } // end VerEstadoAPI
}
