#######################
Transmisión de Mensajes
#######################

La transmición de los mensajes se define por una cantidad de variables:

#. **Metodo Http:** Los tipos permitidos son: *POST*, *GET*, o *PUT*, el resto son ignorados.

#. **URL Htpp:** La dirección del recurso al que se desea acceder, esta asociado al tipo de operación a realizar.

#. **Parametros:** La mayoria de las operaciones requiere que los pedidos vengan con un token, entre muchos otros.



************
Mensajes GET
************

Los parametros de estos mensajes son transmitidos mediante *query strings* en la misma dirección URL.


grupo7/api/usuarios
===================

Este pedido hace que el servidor le envie al cliente un listado con todos los usuarios que tienen una sesión activa en el servidor.

Parametros de entrada
---------------------

* **Token**: Debe ser el token del cliente y estar activo en el sistema.


Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Token: 0,
        Usuarios: [
                { 
                    Token: 0,
                    Nombre: "",
                    Estado: "",
                    UltimaActividadHora: "",
                    UltimaActividadFecha: ""
                },
                {
                    ...
                }
            ]
    }

Donde:

* **Token:** El token del cliente para que pueda validar su pedido.

* **Usuarios:** Un arreglo de objetos *usuario*, pueden ser cero o mas.

  * **Token:** Cada dato de usuario tiene este campo por un tema de compatibilidad, pero este siempre deberia ser vacio o cero.

  * **Nombre:** El nombre del usuario.

  * **Estado:** El estado del usuario,

  * **UltimaActividadHora:** La hora cuando se registró la ultima actividad de ese usuario.

  * **UltimaActividadFecha:** La fecha cuando se registró la ultima actividad de ese usuario.



************
Mensajes PUT
************


grupo7/api/sesion
=================

Mediante este pedido se inicia una sesión del cliente en el servidor.

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        NombreUsuario: "",
        Password: ""
    }

Donde:

* **Token:** Se mantiene por compatibilidad, debe ser vacio o cero.

* **NombreUsuario:** El nombre con el que el usuario se registró en el sistema.

* **Password:** La clave con la que el usuario se registró en el sistema.


Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Token: 0,
        NombreUsuario: "",
        Password: ""
    }

Donde:

* **Token:** El token generado y registrado por el sistema para el usuario, si el loggeo fue exitoso, cero si no.

* **NombreUsuario:** Por compatibilidad, debe estar vacio.

* **Password:** Por compatibilidad, debe estar vacio.


*************
Mensajes POST
*************



