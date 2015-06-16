#######
Cliente
#######

***********************
Descripción del cliente
***********************

El Cliente es una aplicación Android para ser instalada y ejecutada en dispositivos moviles como Celulares y Tablets con dicho sistema operativo. Su funcionalidad es conectarse con el servidor, enviar mensajes y obtener la respuesta del mismo.

Features Incluidos
==================

Dentro de las funcionalidades de la aplicación esta:

* Registrar un nuevo usuario
* Acceder con un usuario ya creado 
* Ver el listado de usuarios conectados
* Configurar Mi Perfil
* Ver el perfil de otro usuario
* Realizar Checkin para que todos sepan mi ubicación

.. note:: Para la proxima entrega van a estar:

* Ver el listado de conversaciones
* Enviar Mensajes con otros usuarios
* Enviar un mensaje a todos los usuarios conectados (Broadcast)

**********
Aplicación
**********

El cliente es una aplicación nativa Android, la misma va a estar generada en un archivo apk.

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

En la pantalla inicial, se puede presionar el boton de AJUSTES, desde allí se podra cambiar la IP del servidor y el Puerto de conexión, por defecto si no se configura ninguno es la ip http://10.0.2.2 y el puerto 8080, dado que la ip es la de la maquina que aloja el emulador del android.

******
Diseño
******

.. figure:: diagrama_clases_cliente.png

   Diagrama del cliente


En la figura se muestra el diseño del cliente y sus partes mas importantes; estas son detalladas a continuación:

Usuario
=======

Es la clase que maneja todos los datos del mismo, como: nombre, password, si esta conectado, la foto, los datos del checkin, etc.

UsuarioParser
=============

Clase encargada de parsear el stream que envia el servidor hacia el cliente

UsuarioProxy
============

Clase encargada de la comunicacion con el servidor en lo que respecta a los usuarios

Conversacion
============

Clase que maneja todo respecto a las conversaciones, por ahora solo se utiliza para las pantallas

Mensaje
=======

Clase que maneja todos los datos de un mensaje, por ahora solo se utiliza para las pantallas


***********************
Known Issues
***********************

* No todas las funcionalidades estan conectadas al 100% con el servidor, dado que el servidor no esta terminado

***********************
Troubleshooting
***********************

No se encuentra resoluciones a problemas frecuentes por el momento.
