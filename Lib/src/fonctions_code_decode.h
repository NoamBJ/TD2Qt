#ifndef _Code_Decode_H_
#define _Code_Decode_H_

#include <stdlib.h>
#include <time.h>


//! Fonction permettant de déterminer la taille des tableaux "information" et "controle" à partir d'un message de taille \a taille_message
//! \return : 1 + taille_message
int GetTailleInformationControlFromMessage(int taille_message);

//! Fonction permettant de déterminer la taille du message obtenu à partir deux tableaux "information" et "controle" de même taille \a taille_information_control
//! \return : taille_information_control - 1
int GetTailleMessageFromInformationControl(int taille_information_control);

//! Fonction permettant de déterminer la taille des tableaux "information" et "controle" à partir d'un signal recu de taille \a taille_signal
//! \return : taille_signal / 2
int GetTailleInformationControlFromSignal(int taille_signal);

//! Fonction permettant de déterminer la taille du signal à transmettre à partir deux tableaux "information" et "controle" de même taille \a taille_information_control
//! \return : taille_information_control * 2
int GetTailleSignalFromInformationControl(int taille_information_control);


//! Fonction de codage convolutif systématique
/*!       \param message : message a coder de taille \a taille_message; parametre d'entrée
          \param taille_message : taille du message (en octects); parametre d'entrée
          \param information : partie "information" du message codé de taille \a taille_message + 1; parametre de sortie, ce tableau doit être alloué avant l'appel à cette fonction
          \param control : partie "controle" du message codé de taille \a taille_message + 1; parametre de sortie, ce tableau doit être alloué avant l'appel à cette fonction
*/
void CodageConvolutif( const unsigned char message[], unsigned char information[], unsigned char control[], int taille_message);

//! Fonction de decodage convolutif systèmatique
/*!       \param message : message décodé de taille \a taille_information_control - 1; parametre de sortie, espace à allouer avant l'appel à cette fonction
          \param information : partie "information" du message codé de taille \a taille_information_control; parametre d'entrée
          \param control : partie "controle" du message codé de taille \a taille_information_control; parametre d'entrée
          \param taille_information_control : taille en octects des parties "information" et "controle"; parametre d'entrée
*/
void DecodageConvolutif( const unsigned char information[], const unsigned char control[], unsigned char message[], int taille_information_control);

//! Melange binaire de l'information et du control pour faire le signal
/*!       \param signal : signal à transmettre, composé alternativement d'un bit d'information et d'un bit de controle, la taille du signal est \a taille_information_control*2; parametre de sortie, espace à allouer avant l'appel à cette fonction
          \param information : partie "information" du message codé de taille \a taille_information_control; parametre d'entrée
          \param control : partie "controle" du message codé de taille \a taille_information_control; parametre d'entrée
          \param taille_information_control : taille en octects des parties "information" et "controle"; parametre d'entrée
*/
void MelangeInformationControl( const unsigned char information[], const unsigned char control[], unsigned char signal[], int taille_information_control);

//! Séparation binaire de l'information et du control à partir du signal
/*!       \param signal_recu : signal (bruité) recu , composé alternativement d'un bit d'information et d'un bit de controle, la taille du signal est \a taille_signal; parametre d'entrée
          \param information : partie "information" du message codé de taille \a taille_signal / 2; parametre de sortie, espace à allouer avant l'appel à cette fonction
          \param control : partie "controle" du message codé de taille \a taille_signal / 2; parametre de sortie, espace à allouer avant l'appel à cette fonction
          \param taille_signal : taille en octects du \a signal recu; parametre d'entrée
*/
void SepareInformationControl( const unsigned char signal_recu[], unsigned char information[], unsigned char control[], int taille_signal);


//! Fonction de bruitage du signal (bruit uniforme). "p" est le pourcentage d'octets bruités. "offset" permet de commencer le bruitage qu'à partir de l'octet "offset"
/*!       \param signal : signal à bruiter, de taille \a taille_signal; parametre d'entrée
          \param signal_bruit :d signal bruité de taille \a taille_signal; parametre de sortie, espace à allouer avant l'appel à cette fonction
          \param taille_signal : taille en octects de \a signal; parametre d'entrée
          \param p : pourcentage de bruit à appliquer
          \param offset : offset de bruitage. avant l'octet "offset", le signal n'est pas bruité( pour les tests, permet de ne pas bruiter les entêtes: offset = 2*54 pour BMP)
*/
void BruitAdditif(const unsigned char signal[], unsigned char signal_bruit[], int taille_signal, double p, int offset);


#endif
