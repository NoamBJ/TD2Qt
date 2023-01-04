#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void AfficheHexa(char* msg, int tailleTab, char* msgAEnvoye);

int main()
{
  unsigned char message[]={0x0F, 0x44, 0x0B, 0x3D}; // initialisation
  AfficheHexa(message, 4, "Message a envoyer"); // on passe une
   // chaine de caractères correspondant au nom du tableau
   return 0 ;
}

void AfficheHexa(char* msg, int tailleTab, char* msgAEnvoye){

  printf("%s [%d] : ", msgAEnvoye, tailleTab);

  for(int i=0;i<tailleTab;i++){

    printf("%x ",msg[i]);

  }

}
