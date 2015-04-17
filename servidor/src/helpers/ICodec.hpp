#ifndef ICODIFIER_DECODIFIER_H
#define ICODIFIER_DECODIFIER_H



/** Define la interfaz de los codificadores-decodificadores utilizados para la transmisiones.
 * */
class ICodec {
    public:
        virtual void codificar() = 0;
};


#endif

