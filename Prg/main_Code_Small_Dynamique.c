

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions_code_decode.h"


void Affichage( const unsigned char tab[], int taille, char * nom)
{
int i;

	printf(" %s [%d] : ", nom, taille);
	for( i=0; i<taille; i++)
		printf("%#x ", tab[i]);
	printf("\n");

}


double Comparaison( const unsigned char signal_ref[], const unsigned char signal[], int taille)
{
double p_erreur=0.0;
int i;

	for( i=0; i<taille; i++)
		if( signal[i] != signal_ref[i] )
			p_erreur++;

	return (p_erreur/(1.0*taille));

}


int main(void)
{

char a; // caractere pour la pause

unsigned char *information;
unsigned char *control;
unsigned char *signal;
unsigned char *signal_bruit;
unsigned char *information_bruit;
unsigned char *control_bruit;
unsigned char *message_debruit;

int taille_message;
int taille_information_control;
int taille_signal;
int taille_message_debruit;


// Emission
unsigned char message[20];
printf(" Chaine du message : ");
scanf("%s", message);
taille_message = strlen(message) + 1;

  taille_information_control = GetTailleInformationControlFromMessage( taille_message );
  information = (unsigned char *) malloc ( taille_information_control );
  control     = (unsigned char *) malloc ( taille_information_control );
CodageConvolutif( message, information, control, taille_message);

  taille_signal = GetTailleSignalFromInformationControl( taille_information_control );
  signal        = (unsigned char *) malloc ( taille_signal );
MelangeInformationControl( information, control, signal, taille_information_control);


// Bruit
  signal_bruit      = (unsigned char *) malloc ( taille_signal );
BruitAdditif( signal, signal_bruit, taille_signal, 0.7, 0);


// Reception
  information_bruit = (unsigned char *) malloc ( taille_information_control );
  control_bruit     = (unsigned char *) malloc ( taille_information_control );
SepareInformationControl( signal_bruit, information_bruit, control_bruit, taille_signal);

  taille_message_debruit = GetTailleMessageFromInformationControl( taille_information_control );
  message_debruit = (unsigned char *) malloc ( taille_message_debruit );
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


printf(" > Erreur avant correction sur signal      : %f %% \n",100*Comparaison( signal, signal_bruit, taille_signal));
printf(" > Erreur avant correction sur information : %f %% \n",100*Comparaison( information, information_bruit, taille_message));
printf(" > Erreur apres correction sur information : %f %% \n",100*Comparaison( message, message_debruit, taille_message));
printf(" > Taux de correction sur information      : %f %% \n",100*Comparaison( information_bruit, message_debruit, taille_message));

free( information );
free( control );
free( signal );
free( signal_bruit );
free( information_bruit );
free( control_bruit );
free( message_debruit );

printf(" -- pause -- \n");

scanf("%c", &a);
scanf("%c", &a);

return 0;
}
