package com.example.appmaker.mensajero;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;

import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;

/**
 * Muestra una pantalla que permite loguearse mediante usuario y contrasenia.
 */
public class AutentificacionActivity extends Activity {
    private AutentificacionTask autentificacionTask = null;
    private AutoCompleteTextView usuarioView;
    private EditText contraseniaView;
    private View mProgressView;
    private View mLoginFormView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_autentificacion);
        usuarioView = (AutoCompleteTextView) findViewById(R.id.usuario);

        contraseniaView = (EditText) findViewById(R.id.contrasenia);
        contraseniaView.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int id, KeyEvent keyEvent) {
                if (id == R.id.autentificacion || id == EditorInfo.IME_NULL) {
                    intentarAutentificacion();
                    return true;
                }
                return false;
            }
        });

        Button iniciarSesionButton = (Button) findViewById(R.id.iniciar_sesion_button);
        iniciarSesionButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                intentarAutentificacion();
            }
        });

        Button crearNuevaCuentaButton = (Button) findViewById(R.id.crear_nueva_cuenta_button);
        crearNuevaCuentaButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                abrirRegistracion();
            }
        });

        mLoginFormView = findViewById(R.id.login_form);
        mProgressView = findViewById(R.id.login_progress);
    }

    /**
     * Intenga autentificar al usuario. Si hay errores en el contenido de los campos los informa y
     * no se intenta realizar la autentificacion.
     */
    public void intentarAutentificacion() {
        if (autentificacionTask != null) {
            return;
        }

        usuarioView.setError(null);
        contraseniaView.setError(null);

        String usuario = usuarioView.getText().toString();
        String contrasenia = contraseniaView.getText().toString();

        boolean cancel = false;
        View focusView = null;

        if (TextUtils.isEmpty(contrasenia)) {
            contraseniaView.setError(getString(R.string.error_contrasenia_vacia));
            focusView = contraseniaView;
            cancel = true;
        }

        if (TextUtils.isEmpty(usuario)) {
            usuarioView.setError(getString(R.string.error_usuario_vacio));
            focusView = usuarioView;
            cancel = true;
        }

        if (cancel) {
            focusView.requestFocus();
        } else {
            showProgress(true);
            autentificacionTask = new AutentificacionTask(usuario, contrasenia);
            autentificacionTask.execute((Void) null);
        }
    }


    private void abrirRegistracion() {
        Intent registracionIntent =new Intent("com.example.appmaker.mensajero.RegistracionActivity");
        startActivity(registracionIntent);
        finish();
    }

    /**
     * Muestra el progreso.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    public void showProgress(final boolean show) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            int shortAnimTime = getResources().getInteger(android.R.integer.config_shortAnimTime);

            mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
            mLoginFormView.animate().setDuration(shortAnimTime).alpha(
                    show ? 0 : 1).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
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
            mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
        }
    }

    /**
     * Representa un task asincronico para la autentificacion del usuario.
     */
    public class AutentificacionTask extends AsyncTask<Void, Void, Boolean> {

        private final String usuario;
        private final String contrasenia;

        AutentificacionTask(String usuario, String contrasenia) {
            this.usuario = usuario;
            this.contrasenia = contrasenia;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            Usuario usuario = null;
            usuario = new UsuarioProxy(PreferenceManager.getDefaultSharedPreferences(getBaseContext())).login(new Usuario(this.usuario, this.contrasenia));
            if(usuario != null) {
                CheckBox recordarDatosCheck = (CheckBox) findViewById(R.id.recordar_datos_check);
                if (recordarDatosCheck.isChecked()) {
                    guardarLogin();
                }
            }
            return (usuario != null );
        }

        private void guardarLogin() {
            SharedPreferences preferenciasCompartidas = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
            SharedPreferences.Editor editorPreferenciasCompartidas = preferenciasCompartidas.edit();
            editorPreferenciasCompartidas.putString("usuario", this.usuario);
            editorPreferenciasCompartidas.putString("contrasenia", this.contrasenia);
            editorPreferenciasCompartidas.apply();
        }

        @Override
        protected void onPostExecute(final Boolean success) {
            autentificacionTask = null;
            showProgress(false);

            if (success) {
                Intent listaUsuariosConectadosIntent = new Intent("com.example.appmaker.mensajero.ListaUsuariosConectadosActivity");
                startActivity(listaUsuariosConectadosIntent);
                finish();
            } else {
                contraseniaView.setError(getString(R.string.error_credenciales_invalidas));
                contraseniaView.requestFocus();
            }
        }

        @Override
        protected void onCancelled() {
            autentificacionTask = null;
            showProgress(false);
        }
    }
}