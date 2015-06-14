#############
Base de datos
#############

Usaremos una base de datos No-SQL de tipo clave-valor para almacenar los datos necesarios para la operacion del sistema.


**************************
Diseño de la Base de Datos
**************************

Para organizar los datos en la base lo que se definirán dominios para separar los distintos tipos de datos; estos dominios serán:

* Dominio de datos de usuarios: **U/\<UserId\>**

* Dominio de conversaciones: **C/\<IdConversacion\>**

* Dominio de mensajes: **M/\<IdMensaje\>**

* Dominio de mensajes no recibidos: **UR/\<UserId\>\<IdConversacion\>**

Por comodidad todos los datos contenidos en cada dominio estarán en formato de JSON.


U/\<UserName\>
==============

Se accede por el nombre de usuario con el prefijo *U/* para remarcar que es un usuario.
El nombre de usuario debe ser único en todo el sistema y no pueden existir dos usuarios con el mismo nombre; es en efecto un *UserId*.

Dentro de este dominio se guardan los siguientes datos:

* **Password:** Se utiliza para autenticar a un usuario registrado del sistema.

* **Latitud** y **Longitud:** Correnponde a la ultima ubicación geográfica conocida del usuario.

* **Fecha-Hora:** Es un string que contiene la descripción de la fecha y hora del registro de la ultima posición del usuario.

* **Foto:** Una fotografia del usuario codificada en *base64*.

* **IdConversaciones:** Un listado con los ids de todas las conversaciones en las que participa el usuario.


C/\<IdConversacion\>
====================

Se accede por el id de la conversación (número autoincremental) con el prefijo *C/* para separar de los otros dominios.

Dentro de este dominio se guardan los siguientes datos:

* **UserIds:** Un arreglo con los id de usuarios de todos los usuarios que participan en la conversación.

* **IdMensajes:** Un arreglo con los ids de todos los mensajes que pertenecen a la conversación.


M/\<IdMensaje\>
===============

Se accede por el id del mensaje (número autoincremental) con el prefijo *M/* para separar de los otros dominios.

Dentro de este dominio se guardan los siguientes datos:

* **UserId:** El emisor o remitente del mensaje.

* **Texto:** El contenido del mensaje.


UR/\<UserId\>\<idConversacion\>
===============================

Un dominio especial para llevar cuenta de cuales son los ultimos mensajes recibidos de cada conversación para cada usuario.

Solo contiene un dato:

* **IdUltimoMensajeRecibido:** El id del ultimo mensaje recibido por el usuario en la conversación.


