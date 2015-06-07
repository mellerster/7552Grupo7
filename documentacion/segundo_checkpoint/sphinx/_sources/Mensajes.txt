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

Este pedido hace que el servidor envie al cliente un listado con todos los usuarios que tienen una sesión activa.


Parametros de entrada
---------------------

* **Token**: Debe ser el token del cliente y estar activo en el sistema.


Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Status: "",
        Usuarios: [
                { 
                    Status: "",
                    Nombre: "",
                    Estado: "",
                    Foto: "<base64>",
                    UltimaActividadHora: "",
                    UltimaActividadFecha: ""
                },
                {
                    ...
                }
            ]
    }

Donde:

* **Status** El estado del resultado de la operación, pudiendo ser esta: "OK" o "ERR".

* **Usuarios:** Un arreglo de objetos *usuario*, pueden ser cero o mas.

  * **Status:** Cada dato de usuario tiene este campo por un tema de compatibilidad, siempre deberia ser vacio.

  * **Nombre:** El nombre del usuario.

  * **Estado:** El estado del usuario,

  * **Foto:** La fotografia que el correspondiente usuario ha cargado en el sistema, en base64.

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
        NombreUsuario: "",
        Password: ""
    }

Donde:

* **NombreUsuario:** El nombre con el que el usuario se registró en el sistema.

* **Password:** La clave con la que el usuario se registró en el sistema.


Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Token: 0,
        Status: ""
    }

Donde:

* **Token:** Contiene el token que identifica la sesión del usuario, si este logro loggearse al sistema.

* **Status:** El resultado de la operación; "OK" o "ERR".



grupo7/api/usuarios
===================

Mediante este pedido se realiza la edición de los datos del perfil del usuario.

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        Foto: "<base64>",
        Estado: ""
    }

Donde:

* **Token:** Contiene el token que identifica la sesión del usuario.

* **Foto:** Una imagen codificada en base64.

* **Estado:** Un texto que indique el estado del usuario.


Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Status: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".



*************
Mensajes POST
*************


grupo7/api/usuarios
===================

Mediante este pedido un usuario puede registrarse en el sistema.


Parametro de entrada
--------------------

El parametro de entrada es en formato JSON::

    {
        NombreUsuario: "",
        Password: ""
    }

Donde:

* **NombreUsuario:** El nombre con el que el usuario se registró en el sistema.

* **Password:** La clave con la que el usuario se registró en el sistema.


Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Status: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".


grupo7/api/checkin
==================

Mediante este pedido un usuario puede actualizar su ubicación en el sistema, al mismo tiempo recibe una descripción del punto conocido mas cercano.


Parametro de entrada
--------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        Latitud: "",
        Longitud: ""
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **Latitud:** Coordenada geografica.

* **Longitud:** Coordenada geografica.


Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Status: "",
        Descripcion: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".

* **Descripcion:** Una pequeña descripción del lugar conocido mas cercano a la ubicación del usuario.



