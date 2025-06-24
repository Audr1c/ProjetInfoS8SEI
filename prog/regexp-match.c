/**
 * @file regexp.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  28 09:56:03 2022
 * @brief Regexp parsing and matching. 
 *
 * Program for regexp parsing, and regexp matching. 
 
 */

 /*
Ce programme prend deux arguments en paramètres dans le Terminal :
la chaîne de caractères qui représente l’expression régulière à recon-
naître, et la chaîne de caractères dans laquelle on cherche à reconnaître
cette expression régulière.

- En cas d’erreur, c’est-à-dire si la chaîne de caractères n’est pas une
expression régulière valide, votre programme affichera autant que pos-
sible un indiquant la nature de l’erreur dans le Terminal, puis quittera en
appelant exit(EXIT_FAILURE).

- Sinon, il indiquera dans le Terminal si l’expression régulière et le début
de la chaîne correspondent ou pas. Si elles correspondent, il indiquera
également la partie de la fin de la chaîne qui n’est pas reconnue par l’ex-
pression régulière (i.e. le reste de la chaîne). Enfin, le programme quit-
tera en appelant exit(EXIT_SUCCESS). 

Pour le formatage de la sortie, des exemples d’exécution de ce programme sont 
fournis au paragraphe 3.6.5.
*/
#include <stdlib.h>
#include <stdio.h>

#include <pyas/regexp.h>

int main ( int argc, char *argv[] ) { 
  char     *end = NULL; 
  int  is_match; 

  if ( argc < 3 ) {
    fprintf( stderr, "Usage :\n\t%s regexp text\n", argv[ 0 ] );
    exit( EXIT_FAILURE );
  }

  is_match = re_match( argv[ 1 ], argv[ 2 ], &end );

  if ( is_match ) {
    printf( "The start of '%s' is in %s, %s: '%s'.\n", argv[2], argv[ 1 ], *end ? "next" : "END", end );
  }
  else {
    printf( "The start of '%s' is *NOT* in %s.\n", argv[2], argv[ 1 ] );
  }

  exit( EXIT_SUCCESS );
}
