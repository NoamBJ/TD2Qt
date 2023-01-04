#include "fonctions_code_decode.h"


//! Fonction de calcul de la valeur majoritaire (1 ou 0) dans la liste de variables
unsigned char Majorite(const unsigned char a, const unsigned char b, const unsigned char c);


void CodageConvolutif( const unsigned char message[], unsigned char information[], unsigned char control[], int taille_message)
{
	int j;

	// variables Flip Flop
	unsigned char mi  = 0;
	unsigned char mi1 = 0;
	unsigned char mi2 = 0;
	unsigned char mi3 = 0;
	unsigned char ci  = 0;

	// penser au dernier 4 bits... qui formeront les MSB du dernier octet
	int taille_information_control = 1 + taille_message;
//	*information = (unsigned char *) malloc ( taille_information_control );
//	*control     = (unsigned char *) malloc ( taille_information_control );

	for( j=0; j<8* (taille_information_control); j++)
		{
		// decalage memoires
		mi3 = mi2;
		mi2 = mi1;
		mi1 = mi;

		// obtention du bit "mi"
		if( j < 8 * taille_message )
			{
			if( message[j/8] & ( 1 << (7-(j%8))) )
				mi = 1;
			else
				mi = 0;
			}
		else  // c'est le dernier octet : on simule une entrée nulle pour "vider" les flip flop
			mi = 0;

		// calcul du bit de control
		ci  = mi ^ mi2 ^ mi3;

		switch ( 7-(j%8) )
			{
			case 0:
				if( mi ) information[j/8] += (unsigned char) 1;
				if( ci ) control[j/8]	 += (unsigned char) 1;

				break;
			case 1:
				if( mi ) information[j/8] += (unsigned char) 2;
				if( ci ) control[j/8]	 += (unsigned char) 2;
				break;
			case 2:
				if( mi ) information[j/8] += (unsigned char) 4;
				if( ci ) control[j/8]	 += (unsigned char) 4;
				break;
			case 3:
				if( mi ) information[j/8] += (unsigned char) 8;
				if( ci ) control[j/8]	 += (unsigned char) 8;
				break;
			case 4:
				if( mi ) information[j/8] += (unsigned char) 16;
				if( ci ) control[j/8]	 += (unsigned char) 16;
				break;
			case 5:
				if( mi ) information[j/8] += (unsigned char) 32;
				if( ci ) control[j/8]	 += (unsigned char) 32;
				break;
			case 6:
				if( mi ) information[j/8] += (unsigned char) 64;
				if( ci ) control[j/8]	 += (unsigned char) 64;
				break;
			case 7:
			       if( mi ) information[j/8] = (unsigned char) 128;
			       else  	 information[j/8] = (unsigned char) 0;

				if( ci ) control[j/8] = (unsigned char) 128;
				else     control[j/8] = (unsigned char) 0;

				break;
			};
		}
}


void DecodageConvolutif( const unsigned char information[], const unsigned char control[], unsigned char message[], int taille_information_control)
{
	int j;

	// variables Flip Flop
	unsigned char mi  = 0;
	unsigned char mi1 = 0;
	unsigned char mi2 = 0;
	unsigned char mi3 = 0;

	unsigned char ci  = 0;

	unsigned char maj = 0;

	unsigned char zi  = 0;
	unsigned char zi1 = 0;
	unsigned char zi2 = 0;
	unsigned char zi3 = 0;

//	unsigned char tmp_message = 0;

	int taille_message = taille_information_control - 1;
//	*message = (unsigned char*) malloc ( taille_message );


	for( j=0; j<8*taille_information_control; j++)
		{
		if( information[j/8] & ( 1 << (7-(j%8))) )
			mi = 1;
		else
			mi = 0;

		if( control[j/8] & ( 1 << (7-(j%8))) )
			ci = 1;
		else
			ci = 0;

		zi = ci ^ mi3 ^ mi2 ^ mi;

		maj = Majorite( zi, zi1, zi3);

		if( (j > 2) && (j < 8*(taille_message) + 3) )
			{
			switch ( 7-((j-3)%8) )
				{
				case 0:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 1;
					break;
				case 1:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 2;
					break;
				case 2:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 4;
					break;
				case 3:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 8;
					break;
				case 4:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 16;
					break;
				case 5:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 32;
					break;
				case 6:
					if( mi3 ^ maj ) message[(j-3)/8] += (unsigned char) 64;
					break;
				case 7:
					if( mi3 ^ maj ) message[(j-3)/8] = (unsigned char) 128;
					else		message[(j-3)/8] = (unsigned char) 0;
					break;
				}
			}

		mi3 = mi2;
		mi2 = mi1;
		mi1 = mi;

		zi3 = zi2;
		zi2 = zi1 ^ maj ;
		zi1 = zi  ^ maj;

		}
}


void MelangeInformationControl( const unsigned char information[], const unsigned char control[], unsigned char signal[], int taille_information_control)
{
	unsigned char lsb;
	unsigned char msb;

	int i,j;

//	int taille_signal = 2*taille_information_control;
//	*signal = (unsigned char*) malloc (*taille_signal);

	// melange avec une boucle (ou avec 8 lignes en dur... c'est moins dur ! cf fonction Separe)
	for( j=0; j<taille_information_control; j++)
		{
		lsb = 0;
		msb = 0;
		for( i=0; i<4; i++)
			{
			msb += (( information[j] & ( 1<<(7-i) )) >> ( i) ) + ((control[j] & (1<<(7-i))) >> ( i + 1) );
			lsb += (( information[j] & ( 1<<i )) << ( i + 1) ) + ((control[j] & ( 1<<i )) << ( i) );
			}
		signal[2*j+1] = lsb;
		signal[2*j] = msb;
		}
}



void SepareInformationControl( const unsigned char signal[], unsigned char information[], unsigned char control[], int taille_signal)
{
	unsigned char lsb;
	unsigned char msb;

	int j;

	// pour la taille faire attention au dernier octet qui est complété
	int taille_information_control = taille_signal / 2;
//	*information = (unsigned char*) malloc ( *taille_information_control );
//	*control     = (unsigned char*) malloc ( *taille_information_control );

	for( j=0; j< taille_information_control; j++)
		{
		lsb = signal[2*j+1];
		msb = signal[2*j];

		information[j] = 0;
		control[j]     = 0;

		information[j] += (unsigned char) ( msb & ( 1 << 1 ) ) << 3;
		information[j] += (unsigned char) ( msb & ( 1 << 3 ) ) << 2;
		information[j] += (unsigned char) ( msb & ( 1 << 5 ) ) << 1;
		information[j] += (unsigned char) ( msb & ( 1 << 7 ) );

		information[j] += (unsigned char) ( lsb & ( 1 << 1 ) ) >> 1;
		information[j] += (unsigned char) ( lsb & ( 1 << 3 ) ) >> 2;
		information[j] += (unsigned char) ( lsb & ( 1 << 5 ) ) >> 3;
		information[j] += (unsigned char) ( lsb & ( 1 << 7 ) ) >> 4;

		control[j]	  += (unsigned char) ( msb & 1 )	  << 4;
		control[j]	  += (unsigned char) ( msb & ( 1 << 2 ) ) << 3;
		control[j]	  += (unsigned char) ( msb & ( 1 << 4 ) ) << 2;
		control[j]	  += (unsigned char) ( msb & ( 1 << 6 ) ) << 1;

		control[j]	  += (unsigned char) ( lsb & 1 );
		control[j]	  += (unsigned char) ( lsb & ( 1 << 2 ) ) >> 1;
		control[j]	  += (unsigned char) ( lsb & ( 1 << 4 ) ) >> 2;
		control[j]	  += (unsigned char) ( lsb & ( 1 << 6 ) ) >> 3;
		}

}



unsigned char Majorite(const unsigned char a, const unsigned char b, const unsigned char c)
{
	if( a+b+c > 1 )
		return 1;
	else
		return 0;
}


void BruitAdditif(const unsigned char signal[], unsigned char signal_bruit[], int taille_signal, double p, int offset)
{
int i, prev_i;
int decalage, prev_decalage;
double random_value;
unsigned char masque;
	// copie du signal, on ajoue le bruit apres
//	*signal_bruit = (unsigned char*) malloc (taille_signal);

	if( offset >= taille_signal)
		offset = 0;

	for( i=0; i<offset; i++)
		signal_bruit[i] = signal[i];

	srand( time(NULL) );

	prev_i = 0;
	prev_decalage = 0;
	for( i=offset; i < taille_signal ; i++) // ne pas bruiter les 2 derniers octets : dangereux...
		{
		random_value = 1.0 * rand() / (RAND_MAX+1.0);
		if( p > random_value)
			{						// on bruite cet octet
			decalage = ( (unsigned char) (8.0*rand() / (RAND_MAX + 1.0) ) );
			if( prev_i + 1 == i)	// attention préserver l'hypothèse de fonctionnement (bruit "gentil" tout les 8 bits)
				decalage = prev_decalage;
			masque =  1 << decalage ;
			signal_bruit[i] = signal[i] ^ masque;
			prev_decalage = decalage;
			prev_i = i;
			}
		else
			signal_bruit[i] = signal[i];
		}
}


//! Fonction permettant de déterminer la taille des tableaux "information" et "controle" à partir d'un message de taille \a taille_message
int GetTailleInformationControlFromMessage(int taille_message)
{ return 1 + taille_message; }

//! Fonction permettant de déterminer la taille du message obtenu à partir deux tableaux "information" et "controle" de même taille \a taille_information_control
int GetTailleMessageFromInformationControl(int taille_information_control)
{ return taille_information_control - 1; }

//! Fonction permettant de déterminer la taille des tableaux "information" et "controle" à partir d'un signal recu de taille \a taille_signal
int GetTailleInformationControlFromSignal(int taille_signal)
{ return taille_signal / 2; }

//! Fonction permettant de déterminer la taille du signal à transmettre à partir deux tableaux "information" et "controle" de même taille \a taille_information_control
int GetTailleSignalFromInformationControl(int taille_information_control)
{ return 2*taille_information_control; }
