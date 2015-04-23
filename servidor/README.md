# Aplicaci�n Servidor del Mensajero

## Introducci�n

Es un webserver de linea de comando que utiliza una API REST para comunicarse con la aplicaci�n cliente.


## Dependencias

Para poder compilar y/o correr la aplicaci�n servidor necesitar�n:

1. [RocksDB] (https://github.com/facebook/rocksdb "Repositorio github de rocksDB")

2. [CMake] (http://www.cmake.org "Sitio oficial de CMake")


### RocksDB

Es necesario compilar e instalar esta libreria, para esto hay que:

1. Bajarse el codigo fuente de su repositorio

2. Compilar mediante los comandos:

    * `PORTABLE=1 make static_lib`

    * `PORTABLE=1 make shared_lib`

3. Instalar la librerias en el sistema ejecutando:

    * `make install`


### CMake

Es necesario para compilar la aplicaci�n, se puede instalar ejecutando en la linea de comando:

* `sudo apt-get install cmake`


## Compilaci�n

Una vez que las dependencias esten cubiertas hay que seguir los siguientes pasos para compilar la aplicaci�n:

1. Dentro del directorio de la aplicaci�n servidor existe una carpeta vacia llamada **bin**, entrar en la misma.

2. Ejecutar **CMake** mediante el comando `cmake ../src`

3. Compilar la aplicaci�n ejecutando el comando `make`

Listo! La aplicaci�n del servidor deberia compilar sin errores.


### Testing

La aplicaci�n servidor posee una cantidad de tests que pueden ser corridos, existen dos formas de llevar esto a cabo:

* Ejecutar desde dentro de la carpeta **bin** el comando `make test`

O

* Dentro de la carpeta **bin** existe otra carpeta llamada **tests** esta contiene, entre otras cosas, varios archivos ejecutables; Estos son los tests a correr.

La diferencia entre las dos formas es que en la segunda se obtiene mas informaci�n sobre los tests que fallaron, pero ambas formas corren los mismos tests.


### Code coverage

Para obtener los datos de **code coverage** se debe compilar la aplicaci�n y luego ejecutar el comando `make test coverage`, esto hara un par de cosas:

1. Correr� todos los tests de la aplicaci�n.

2. Capturar� toda la informaci�n de **code coverage** de los tests sobre la aplicaci�n.

3. Generar� un reporte en formato **html** dentro de la carpeta **CoverageReport**.

Se debe abrir el archivo **index.html** para acceder al reporte.


