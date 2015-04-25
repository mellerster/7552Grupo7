package com.example.appmaker.mensajero;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by diego on 19/04/15.
 */
///TODO: Conectar con el server y traer el datos reales
public class UsuarioProxy {

    /**
     * Usuario que tiene el token para hablar con el servidor
     */
    private static Usuario usuario;

    /**
     * Obtiene el usuario con el token para hablar con el servidor
     * @return usuario que tiene el token
     */
    public static Usuario getUsuario(){
        return usuario;
    }

    /**
       Trae del servidor la lista de usuarios conectados
        @return Un List tipado de Usuario
     */
    public List<Usuario> getUsuariosConectados(){
        //Mockup de Usuarios
        List<Usuario> usuarios = new LinkedList<Usuario>();
        Usuario usuario;
        usuario = new Usuario("Diego");
        usuario.conectar();
        usuarios.add(usuario);
        usuario = new Usuario("Cesar");
        usuario.conectar();
        usuarios.add(usuario);
        usuario = new Usuario("Ramiro");
        usuario.conectar();
        usuarios.add(usuario);
        usuario = new Usuario("Tomas");
        usuario.conectar();
        usuarios.add(usuario);
        return usuarios;
    }

    /**
     * Autentica a un usuario en el servidor
     * @param usuario que debe tener la información necesaria para autenticar
     * @return Devuelve el Usuario con la información del servidor
     */
    public Usuario login(Usuario usuario){
        usuario.conectar();
        UsuarioProxy.usuario = usuario;
        return usuario;
    }

    /**
     * Marca en el servidor que el usuario aparecera como desconectado
     * @param usuario a desconectar
     * @return el usuario desconectado
     */
    public Usuario logout(Usuario usuario){
        usuario.desconectar();
        UsuarioProxy.usuario.desconectar();
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
        UsuarioProxy.usuario = user;
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
        UsuarioProxy.usuario = usuario;
        ///TODO: Enviar foto al server
    }

}
