/*
Ce programme prend un unique argument en paramètre dans le Termi-
nal : une chaîne de caractères représentant l’expression régulière.

- En cas d’erreur, c’est-à-dire si la chaîne de caractères n’est pas une
expression régulière valide, votre exécutable affichera autant que pos-
sible un message indiquant la nature de l’erreur dans le Terminal, puis
quittera en appelant exit(EXIT_FAILURE).

- Sinon, il construira en mémoire la structure de données représentant
l’expression régulière (i.e. une liste chaînée de groupes de caractères),
affichera dans le Terminal la structure de l’expression régulière (c’est-à-
dire le contenu de la liste chaînée), puis quittera en appelant exit(EXIT_SUCCESS).

Pour le formatage de la sortie, des exemples d’exécution de ce pro-
gramme sont fournis au paragraphe 3.6.5.

*/
#include <stdlib.h>
#include <stdio.h>

#include <pyas/regexp.h>

int main ( int argc, char *argv[] ) { 

    char     *end = NULL; 
    int  is_match; 

    if ( argc < 2 ) {
        fprintf( stderr, "Usage :\n\t%s regexp\n", argv[ 0 ] );
        exit( EXIT_FAILURE );
    }
    /*
        TODO
    */
    is_match = re_match( argv[ 1 ], argv[ 2 ], &end );

    if ( is_match ) {
        printf( "The start of '%s' is in %s, %s: '%s'.\n", argv[2], argv[ 1 ], *end ? "next" : "END", end );
    }
    else {
        printf( "The start of '%s' is *NOT* in %s.\n", argv[2], argv[ 1 ] );
    }

    exit( EXIT_SUCCESS );
}