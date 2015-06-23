#######
Cliente
#######

***********************
Descripción del cliente
***********************

El Cliente es una aplicación Android para ser instalada y ejecutada en dispositivos moviles como Celulares y Tablets con dicho sistema operativo. Su funcionalidad es conectarse con el servidor, enviar mensajes y obtener la respuesta del mismo.

Features Incluidos
==================

Dentro de las funcionalidades de la aplicación estan:

* Registrar un nuevo usuario
* Acceder con un usuario ya creado 
* Ver el listado de usuarios conectados
* Configurar Mi Perfil
* Ver el perfil de otro usuario
* Realizar Checkin para que todos sepan mi ubicación
* Ver el listado de conversaciones
* Enviar Mensajes con otros usuarios
* Enviar un mensaje a todos los usuarios conectados (Broadcast)

**********
Aplicación
**********

El cliente es una aplicación nativa Android, la misma va a estar generada en un archivo apk. `Descargar de aquí <https://github.com/mellerster/7552Grupo7/blob/Entrega_Final/documentacion/DocumentacionGenerada/MensajerO.apk>`_

Versión minima del sistema operativo
====================================

La aplicación esta compilada para correr en Android a partir de `Lollipop 5.0 (API 21) <http://www.android.com/versions/lollipop-5-0/>`_

Instalación
===========

En un dispositivo movil real
----------------------------

Copiar el archivo apk al dispositivo movil y abrirlo, al hacerlo seguir los pasos del instalador para instalar la aplicación. 


Configuración
=============

En la pantalla inicial, se puede presionar el boton de AJUSTES, desde allí se podra cambiar la IP del servidor, el Puerto de conexión y las demoras, por defecto si no se configura ninguno es la ip http://10.0.2.2 y el puerto 8080, dado que la ip es la de la maquina que aloja el emulador del android. Las demoras son en milisegundos.

Logging
=======

La aplicación usa un sistema de logging que es el nativo de android llamado `Logcat <http://developer.android.com/tools/help/logcat.html>`_

******
Diseño
******

.. figure:: diagrama_clases_cliente.png

   Diagrama del cliente


En la figura se muestra el diseño del cliente y sus partes mas importantes; estas son detalladas a continuación:

ProxyBase
=========

Es la clase de la que heredan los proxys de Usuario y Conversación, tiene en ella la url del servidor con el puerto.

Usuario
=======

Es la clase que maneja todos los datos del mismo, como: nombre, password, si esta conectado, la foto, los datos del checkin, etc.

UsuarioParser
=============

Clase encargada de parsear el stream que envía el servidor hacia el cliente sobre usuarios.

UsuarioProxy
============

Clase encargada de la comunicacion con el servidor en lo que respecta a los usuarios.

Conversacion
============

Clase que maneja todo respecto a las conversaciones, su Id, que usuarios participan y los mensajes.

Mensaje
=======

Clase que maneja todos los datos de un mensaje: usuario remitente y texto del mensaje.

ConversacionProxy
=================

Clase encargada de la comunicación con el servidor en lo que respecta a las conversaciones y mensajes.

ConversacionParser
==================

Clase encargada de parsear el stream que envía el servidor hacia el cliente sobre conversaciones.

*************
Código Fuente
*************

El código fuente se encuentra documentado con doxygen `aquí <https://github.com/mellerster/7552Grupo7/tree/Entrega_Final/documentacion/DocumentacionGenerada/Documentacion_Codigo_Cliente>`_

************
Known Issues
************

* Si el servidor deja de funcionar inesperadamente la aplicación cliente se caera y aparecera una alerta de "Mensajero ha dejado de funcionar".

* El checkin muestra el mapa con el zoom muy alejado, esto se solucionara para proximas versiones.

* La flecha del teclado no pasa entre campos en algunas pantallas, esto se solucionara para proximas versiones.

***************
Troubleshooting
***************

No se encuentra resoluciones a problemas frecuentes por el momento.
