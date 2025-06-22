/**
 * @file lexem.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @brief Lexems.
 *
 * Lexems.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <pyas/lexem.h>

struct lexem {
  char *type;
  char *value;
  int   line;    /* Start at line 1   */
  int   column;  /* Start at column 0 */
};

/*
  Constructor and callbacks for lists/queues of lexems:
 */
lexem_t lexem_new( char *type, char *value, int line, int column ) {
  lexem_t lex = calloc( 1, sizeof( *lex ) );

  assert( lex );

  if ( type  && *type  ) lex->type  = strdup( type );
  if ( value && *value ) lex->value = strdup( value );

  lex->line   = line;
  lex->column = column;

  return lex;
}

int     lexem_print( void *_lex ) {
  lexem_t lex = _lex; /* Start by casting to actual type */

  return printf( "[%d:%d:%s] %s",
         lex->line,
         lex->column,
         lex->type,
         lex->value );
}

int     lexem_delete( void *_lex ) {
  lexem_t lex = _lex;

  if ( lex ) {
    free( lex->type );
    free( lex->value );
  }

  free( lex );

  return 0;
}
