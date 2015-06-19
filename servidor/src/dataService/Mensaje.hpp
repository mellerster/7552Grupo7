#ifndef MENSAJE_H
#define MENSAJE_H


/** Representa un mensaje enviado o recibido.
 * */
class Mensaje {
    public:
        std::string IDRemitente;    /**< El UserID del emisor del mensaje. */
        std::string Texto;          /**< El texto del mensaje. */
};


#endif

