
#include "fonctions_fichier.h"

int LireFichier( const char fichier[], unsigned char **message, int *taille, int offset)
{
 int nb_lu;
 
 FILE* fich = fopen(fichier,"rb");
 if(!fich)  return 1;

// * Lecture de la taille du fichier
   fseek( fich, 0, SEEK_END);	    // Positionnement du pointeur à la fin du fichier
   *taille = ftell(fich) - offset;   // Lecture de la position du pointeur (=taille)
   fseek( fich, offset, SEEK_SET);  // rePositionnement du pointeur au début du fichier (offset)

   *message = (unsigned char*) malloc (*taille);
   if( *message == NULL ) return 3; // PB allocation

   
   nb_lu = fread( *message, sizeof(char), *taille, fich); // Lecture
   if ( nb_lu != *taille ) return 1;

 fclose(fich);
 return 0; // pas de problème
}


int EcrireFichier( const char fichier[], const unsigned char message[], int taille)
{
 FILE *f_dest;
 f_dest = fopen(fichier,"wb");
 if(!f_dest) return 1;    //problème d'accès en ecriture
 fwrite( message, sizeof(char), taille, f_dest);

 fclose(f_dest);
 return 0;  //pas de probleme
}

