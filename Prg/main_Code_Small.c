

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions_code_decode.h"

#define taille_message 4

void Affichage( const unsigned char tab[], int taille, char * nom)
{
int i;
	printf(" %s [%d] : ", nom, taille);
	for( i=0; i<taille; i++)
		printf("%#x ", tab[i]);
	printf("\n");
}


int main(void)
{

char a; // caractere pour la pause

unsigned char information[ taille_message + 1 ];
unsigned char control[ taille_message + 1 ];
unsigned char signal[ (taille_message + 1)*2 ];
unsigned char signal_bruit[ (taille_message + 1)*2 ];
unsigned char information_bruit[ taille_message + 1 ];
unsigned char control_bruit[ taille_message + 1 ];
unsigned char message_debruit[ taille_message ];

int taille_information_control = taille_message + 1;
int taille_signal = taille_information_control * 2;
int taille_message_debruit = taille_message;

unsigned char message[] = "012";

// Emission
CodageConvolutif( message, information, control, taille_message);
MelangeInformationControl( information, control, signal, taille_information_control);

// Bruit
BruitAdditif( signal, signal_bruit, taille_signal, 0.7, 0);

// Reception
SepareInformationControl( signal_bruit, information_bruit, control_bruit, taille_signal);
DecodageConvolutif( information_bruit, control_bruit, message_debruit, taille_information_control);

Affichage( message, taille_message,	"message          ");
printf("\n");

Affichage( information, taille_information_control, "information	  ");
Affichage( control, taille_information_control,	"control          ");
Affichage( signal, taille_signal,		"signal          ");
printf("\n");


Affichage( signal_bruit, taille_signal,		  "signal_bruit	");
Affichage( information_bruit, taille_information_control, "information_bruit");
Affichage( control_bruit, taille_information_control, "control_bruit    ");
printf("\n");

Affichage( message_debruit, taille_message_debruit, "message_debruit  ");
printf("\n");

printf(" -- pause -- \n");

scanf("%c", &a);

return 0;
}
