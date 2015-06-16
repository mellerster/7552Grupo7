#######################
Transmisión de Mensajes
#######################

La transmición de los mensajes se define por una cantidad de variables:

#. **Metodo Http:** Los tipos permitidos son: *POST*, *GET*, *PUT* o *DELETE*, el resto son ignorados.

#. **URL Htpp:** La dirección del recurso al que se desea acceder, esta asociado al tipo de operación a realizar.

#. **Parametros:** La mayoria de las operaciones requiere que los pedidos vengan con un token, entre muchos otros.

Mensajes GET

Los parametros de estos mensajes son transmitidos mediante *query strings* en la misma dirección URL.


*****************
grupo7/api/sesion
*****************

PUT
===

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

DELETE
======

Mediante este pedido se cierra una sesión del cliente en el servidor

Parametro de entrada
--------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0
    }

Donde:

* **Token:** Debe ser el token del cliente y estar activo en el sistema.

Parametro de salida
-------------------

El parametro de salida es en formato JSON::

    {
        Status: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".


*******************
grupo7/api/usuarios
*******************

GET
===

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
  
PUT
===

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

POST
====

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

*******************
/grupo7/api/usuario
*******************

GET
===

Mediante este pedido se obtiene los datos del perfil de un usuario especifico

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        Nombre: ""
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **Nombre:** El nombre del usuario a obtener la información.

Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Status: "",
	Nombre: "",
	Estado: "",
	Foto: "<base64>",
	Ubicacion: "",
	CheckInFechaHora: "",
    }
    
Donde:

* **Status** El estado del resultado de la operación, pudiendo ser esta: "OK" o "ERR".

* **Nombre:** El nombre del usuario.

* **Estado:** El estado del usuario,

* **Foto:** La fotografia que el correspondiente usuario ha cargado en el sistema, en base64.

* **Ubicacion:** La ubicacion del usuario cuando se registró el ultimo checkin.

* **CheckInFechaHora:** La Fecha y Hora cuando se registró el ultimo checkin.


**************************
/grupo7/api/conversaciones
**************************

GET
===

Mediante este pedido se obtiene el listado de conversaciones del usuario.


Parametro de entrada
--------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.


Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Status: "",
        Conversaciones: [
                { 
                    Status: "",
                    IdConversacion: 0,
                    UltimoMensaje: "",
                    UltimoMensajeLeido: true,
                    Participantes: [
                    {
                    	FALTA DEFINIR
                    },
                    ...
                    ]
                },
                {
                    ...
                }
            ]
    }

Donde:

* **Status** El estado del resultado de la operación, pudiendo ser esta: "OK" o "ERR".

* **Conversaciones:** Un arreglo de objetos *conversación*, pueden ser cero o mas.

  * **Status:** Cada dato de conversación tiene este campo por un tema de compatibilidad, siempre deberia ser vacio.

  * **IdConversacion:** El identificador de la conversación en el servidor.

  * **UltimoMensaje:** El último mensaje enviado en la conversación,

  * **UltimoMensajeLeido:** Un flag (true o false) para marcar si este último mensaje fue leído por el usuario que pide el listado.
  
  * **Participantes:** Un arreglo con los participantes.

.. note:: Ver si cambia luego, cambiarlo

************************
/grupo7/api/conversacion
************************

GET
===

Mediante este pedido se obtienen todos los mensajes de una conversación


Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        IdConversacion: 0,
        IdUsuario: ""
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **IdConversacion:** Contiene el identificador unico de la conversación en el servidor.

o

* **IdUsuario:** Contiene el nombre de otro usuario participante en la conversación.

Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Status: "",
        IdConversacion: 0,
        Mensajes: [
                { 
                    Status: "",
                    IdMensaje: 0,
                    IdParticipante: "",
                    Mensaje: ""
                },
                {
                    ...
                }
            ]
    }

Donde:

* **Status** El estado del resultado de la operación, pudiendo ser esta: "OK" o "ERR".

* **IdConversacion** El identificador de la conversación en el servidor.

* **Mensajes:** Un arreglo de objetos *mensaje*, pueden ser cero o mas.

  * **Status:** Cada dato de mensaje tiene este campo por un tema de compatibilidad, siempre deberia ser vacio.

  * **IdMensaje:** El identificador del mensaje en el servidor.

  * **IdParticipante:** El nombre del usuario que envio dicho mensaje,

  * **Mensaje:** El texto del mensaje enviado.

.. note:: Ver si cambia luego, cambiarlo


******************
grupo7/api/checkin
******************

POST
====

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

************************
/grupo7/api/broadcast
************************

POST
====

Mediante este pedido se envia un mensaje a todos los usuarios conectados.

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        Mensaje: "",
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **Mensaje:** El mensaje a enviar.


Parametros de salida
--------------------


El parametro de salida es en formato JSON::

    {
        Status: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".

.. note:: Ver si cambia luego, cambiarlo

********************
/grupo7/api/mensajes
********************

POST
====

Mediante este pedido se envia un mensaje a un usuario en una conversacion.

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        IdConversacion: 0,
        Mensaje: ""
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **IdConversacion:** El identificador de la conversación a la que se envio el mensaje.

* **Mensaje:** El mensaje a enviar.

Parametros de salida
--------------------

El parametro de salida es en formato JSON::

    {
        Status: ""
    }

Donde:

* **Status:** El resultado de la operación; "OK" o "ERR".

.. note:: Ver si cambia luego, cambiarlo

GET
===

Mediante este pedido se obtienen los mensajes sin leer por el usuario de una conversación

Parametros de entrada
---------------------

El parametro de entrada es en formato JSON::

    {
        Token: 0,
        IdConversacion: 0,
    }

Donde:

* **Token:** Contiene el token que identifica al usuario.

* **IdConversacion:** Contiene el identificador unico de la conversación en el servidor.

Parametros de salida
--------------------

Un JSON con la siguiente estructura::

    {
        Status: "",
        Mensajes: [
                { 
                    Status: "",
                    IdMensaje: 0,
                    IdParticipante: "",
                    Mensaje: ""
                },
                {
                    ...
                }
            ]
    }

Donde:

* **Status** El estado del resultado de la operación, pudiendo ser esta: "OK" o "ERR".

* **Mensajes:** Un arreglo de objetos *mensaje*, pueden ser cero o mas.

  * **Status:** Cada dato de mensaje tiene este campo por un tema de compatibilidad, siempre deberia ser vacio.

  * **IdMensaje:** El identificador del mensaje en el servidor.

  * **IdParticipante:** El nombre del usuario que envio dicho mensaje,

  * **Mensaje:** El texto del mensaje enviado.

.. note:: Ver si cambia luego, cambiarlo
