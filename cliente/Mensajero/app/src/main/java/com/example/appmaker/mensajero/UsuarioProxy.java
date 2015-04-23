package com.example.appmaker.mensajero;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by diego on 19/04/15.
 */
///TODO: Conectar con el server y traer el datos reales
public class UsuarioProxy {

    /**
       Trae del servidor la lista de usuarios conectados
        @return Un List tipado de Usuario
     */
    public List<Usuario> getUsuariosConectados(){
        List<Usuario> usuarios = new LinkedList<Usuario>();
        usuarios.add(new Usuario("diego", "diego"));
        usuarios.add(new Usuario("cesar", "cesar"));
        usuarios.add(new Usuario("ramiro", "ramiro"));
        usuarios.add(new Usuario("tomas", "tomas"));
        return usuarios;
    }

    /**
     * Autentica a un usuario en el servidor
     * @param usuario que debe tener la información necesaria para autenticar
     * @return Devuelve el Usuario con la información del servidor
     */
    public Usuario login(Usuario usuario){
        usuario.conectar();
        return usuario;
    }

    /**
     * Marca en el servidor que el usuario aparecera como desconectado
     * @param usuario a desconectar
     * @return el usuario desconectado
     */
    public Usuario logout(Usuario usuario){
        usuario.desconectar();
        return usuario;
    }

    /**
     * Registra y Autentifica a un usuario en el servidor
     * @param username nombre del usuario
     * @param password contraseña del usuario
     * @return el Usuario autentificado
     */
    public Usuario registrar(String username, String password){
        Usuario user = new Usuario(username,password);
        user.conectar();
        return user;
    }

    /**
     * Trae la configuración del usuario que esta logueado
     * @param username nombre del usuario
     * @return el usuario con sus datos cargados
     */
    public Usuario getUsuario(String username){
        Usuario user = new Usuario(username);
        user.conectar();
        return user;
    }

    /**
     * Trae el estado completo de un usuario
     * @param username nombre del usuario
     * @return el Usuario con todos sus datos para mostrar
     */
    public Usuario verEstado(String username){
        return  new Usuario(username);
    }

    /**
     * Envia la foto de perfil del usuario al servidor
     * @param usuario con una foto de perfil nueva.
     */
    public void cargarFoto(Usuario usuario){
        ///TODO: Enviar foto al server
    }

}
