
#ifndef _LireFichier_H_
#define _LireFichier_H_


#include <stdio.h>
#include <stdlib.h>

//! Fonction de lecture du fichier. le tableau \a message est allou� par cette fonction !!!
/*! \param fichier : nom complet du fichier (chemin + nom du fichier + extension)
    \param message : tableau contenant tous les octets du fichier, ce tableau est allou� par cette fonction
    \param taille : taile du fichier lu (en octet) correspond aussi � la taille du tableau \a message
    \param offset : offset � partir du quel le fichier est lu
*/
int LireFichier( const char fichier[], unsigned char **message, int *taille, int offset);

//! Fonction d'�criture de fichier.
/*! \param fichier : nom complet du fichier � ecrire (chemin + nom du fichier + extension)
    \param message : tableau contenant tous les octets du fichier
    \param taille : taille  du tableau \a message, equivalent au nombre d'octets � ecrire
*/
int EcrireFichier( const char fichier[], const unsigned char message[], int taille);

#endif

