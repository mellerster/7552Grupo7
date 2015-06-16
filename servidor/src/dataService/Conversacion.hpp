#ifndef CONVERSACION_H
#define CONVERSACION_H

#include <string>
#include <vector>



/** Describe los datos resumidos de una conversacion.
 * */
class Conversacion {
    public:
        unsigned int IDConversacion;    /**< El ID único de la conversación. */

        std::string UltimoMensaje;      /**< El texto del ultimo mensaje que forma parte de la conversación. */
        bool UltimoMensajeLeido;        /**< Indica si el ultimo mensaje de la conversación fue leido. */

        std::vector<std::string> Participantes;  /**< Los UserIDs de los participantes de la conversación. */
};


#endif

