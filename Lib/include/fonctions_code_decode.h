#ifndef _Code_Decode_H_
#define _Code_Decode_H_

#include <stdlib.h>
#include <time.h>


//! Fonction permettant de d�terminer la taille des tableaux "information" et "controle" � partir d'un message de taille \a taille_message
//! \return : 1 + taille_message
int GetTailleInformationControlFromMessage(int taille_message);

//! Fonction permettant de d�terminer la taille du message obtenu � partir deux tableaux "information" et "controle" de m�me taille \a taille_information_control
//! \return : taille_information_control - 1
int GetTailleMessageFromInformationControl(int taille_information_control);

//! Fonction permettant de d�terminer la taille des tableaux "information" et "controle" � partir d'un signal recu de taille \a taille_signal
//! \return : taille_signal / 2
int GetTailleInformationControlFromSignal(int taille_signal);

//! Fonction permettant de d�terminer la taille du signal � transmettre � partir deux tableaux "information" et "controle" de m�me taille \a taille_information_control
//! \return : taille_information_control * 2
int GetTailleSignalFromInformationControl(int taille_information_control);


//! Fonction de codage convolutif syst�matique
/*!       \param message : message a coder de taille \a taille_message; parametre d'entr�e
          \param taille_message : taille du message (en octects); parametre d'entr�e
          \param information : partie "information" du message cod� de taille \a taille_message + 1; parametre de sortie, ce tableau doit �tre allou� avant l'appel � cette fonction
          \param control : partie "controle" du message cod� de taille \a taille_message + 1; parametre de sortie, ce tableau doit �tre allou� avant l'appel � cette fonction
*/
void CodageConvolutif( const unsigned char message[], unsigned char information[], unsigned char control[], int taille_message);

//! Fonction de decodage convolutif syst�matique
/*!       \param message : message d�cod� de taille \a taille_information_control - 1; parametre de sortie, espace � allouer avant l'appel � cette fonction
          \param information : partie "information" du message cod� de taille \a taille_information_control; parametre d'entr�e
          \param control : partie "controle" du message cod� de taille \a taille_information_control; parametre d'entr�e
          \param taille_information_control : taille en octects des parties "information" et "controle"; parametre d'entr�e
*/
void DecodageConvolutif( const unsigned char information[], const unsigned char control[], unsigned char message[], int taille_information_control);

//! Melange binaire de l'information et du control pour faire le signal
/*!       \param signal : signal � transmettre, compos� alternativement d'un bit d'information et d'un bit de controle, la taille du signal est \a taille_information_control*2; parametre de sortie, espace � allouer avant l'appel � cette fonction
          \param information : partie "information" du message cod� de taille \a taille_information_control; parametre d'entr�e
          \param control : partie "controle" du message cod� de taille \a taille_information_control; parametre d'entr�e
          \param taille_information_control : taille en octects des parties "information" et "controle"; parametre d'entr�e
*/
void MelangeInformationControl( const unsigned char information[], const unsigned char control[], unsigned char signal[], int taille_information_control);

//! S�paration binaire de l'information et du control � partir du signal
/*!       \param signal_recu : signal (bruit�) recu , compos� alternativement d'un bit d'information et d'un bit de controle, la taille du signal est \a taille_signal; parametre d'entr�e
          \param information : partie "information" du message cod� de taille \a taille_signal / 2; parametre de sortie, espace � allouer avant l'appel � cette fonction
          \param control : partie "controle" du message cod� de taille \a taille_signal / 2; parametre de sortie, espace � allouer avant l'appel � cette fonction
          \param taille_signal : taille en octects du \a signal recu; parametre d'entr�e
*/
void SepareInformationControl( const unsigned char signal_recu[], unsigned char information[], unsigned char control[], int taille_signal);


//! Fonction de bruitage du signal (bruit uniforme). "p" est le pourcentage d'octets bruit�s. "offset" permet de commencer le bruitage qu'� partir de l'octet "offset"
/*!       \param signal : signal � bruiter, de taille \a taille_signal; parametre d'entr�e
          \param signal_bruit :d signal bruit� de taille \a taille_signal; parametre de sortie, espace � allouer avant l'appel � cette fonction
          \param taille_signal : taille en octects de \a signal; parametre d'entr�e
          \param p : pourcentage de bruit � appliquer
          \param offset : offset de bruitage. avant l'octet "offset", le signal n'est pas bruit�( pour les tests, permet de ne pas bruiter les ent�tes: offset = 2*54 pour BMP)
*/
void BruitAdditif(const unsigned char signal[], unsigned char signal_bruit[], int taille_signal, double p, int offset);


#endif
