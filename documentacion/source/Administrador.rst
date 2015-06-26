##########################
Administrador del Servidor
##########################

***********
Get Started
***********

Para poder compilar y/o correr la aplicación servidor necesitarán:

1. `RocksDB <https://github.com/facebook/rocksdb>`_: Repositorio github de rocksDB

2. `CMake <http://www.cmake.org>`_: Sitio oficial de CMake

3. `Doxygen <http://www.stack.nl/~dimitri/doxygen/index.html>`_: Sitio oficial de Doxygen - **Opcional**


RocksDB
=======

Es necesario compilar e instalar esta libreria, para esto hay que:

1. Bajarse el codigo fuente de su repositorio

2. Compilar mediante los comandos:

.. sourcecode:: bash
	
	$ PORTABLE=1 make static_lib	
	$ PORTABLE=1 make shared_lib

3. Instalar la librerias en el sistema ejecutando:

.. sourcecode:: bash
	
	$ make install

CMake
=====

Es necesario para compilar la aplicación, se puede instalar ejecutando en la linea de comando:

.. sourcecode:: bash
	
	$ sudo apt-get install cmake

Doxygen
=======

Es necesario para extraer la documentación del código fuente del servidor, para instalarlo se puede ejecutar el comando:

.. sourcecode:: bash
	
	$ sudo apt-get install doxygen

***************************
Instalación y configuración
***************************

Una vez que las dependencias esten cubiertas hay que seguir los siguientes pasos para compilar la aplicación:

1. Dentro del directorio de la aplicación servidor existe una carpeta vacia llamada **bin**, entrar en la misma.

2. Ejecutar **CMake** mediante el comando 

.. sourcecode:: bash
	
	$ cmake ../src

3. Compilar la aplicación ejecutando el comando `make`

Listo! La aplicación del servidor deberia compilar sin errores.

Para correr la aplicación ejecutar en la terminal:

.. sourcecode:: bash

	$ ./serverMensajerO

************
Forma de uso
************

Para iniciar el servidor dentro de la aplicación debe presionar **Y** y luego enter.

El servidor se iniciara en la ip de la maquina que lo aloja en el puerto 8080 o sea que su url es:

http://localhost:8080

Para finalizar el servidor debe presionar **X** y luego enter.

.. warning:: Ambos comandos (X e Y) son en Mayuscula

*******
Testing
*******

La aplicación servidor posee una cantidad de tests que pueden ser corridos, existen dos formas de llevar esto a cabo:

* Ejecutar desde dentro de la carpeta **bin** el comando 

.. sourcecode:: bash
	
	$ make test

O

* Dentro de la carpeta **bin** existe otra carpeta llamada **tests** esta contiene, entre otras cosas, varios archivos ejecutables; Estos son los tests a correr.

La diferencia entre las dos formas es que en la segunda se obtiene mas información sobre los tests que fallaron, pero ambas formas corren los mismos tests.

*************
Code coverage
*************

Para obtener los datos de **code coverage** se debe compilar la aplicación y luego ejecutar el comando

.. sourcecode:: bash
	
	$ make test coverage

, esto hara un par de cosas:

1. Correrá todos los tests de la aplicación.

2. Capturará toda la información de **code coverage** de los tests sobre la aplicación.

3. Generará un reporte en formato **html** dentro de la carpeta **CoverageReport**.

Se debe abrir el archivo **index.html** para acceder al reporte.

*************
Mantenimiento
*************

Documentación
=============

El código fuente del servidor esta documentado con Doxygen, por lo tanto es necesario correr el comando:

.. sourcecode:: bash

	$ doxygen

Third-party libs
================

El servidor utiliza un número de librerias externas, estas son:

* `Mongoose <https://github.com/cesanta/mongoose>`_: Mongoose web-server.

* `JsonCpp <https://github.com/open-source-parsers/jsoncpp>`_: JsonCpp parser JSON.

* `HumbleLogging <http://humblelogging.insanefactory.com/>`_: Framework de loggeo.

* `Catch <https://github.com/philsquared/Catch>`_: Framework de testeo.

* `Hippomocks <https://github.com/dascandy/hippomocks>`_: Framework de mockeo para los tests.


************
Known Issues
************


***************
Troubleshooting
***************


