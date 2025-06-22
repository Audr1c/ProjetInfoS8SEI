/**
 * @file lexem.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @brief Lexems.
 *
 * Lexems.
 */

#ifndef _LEXEM_H_
#define _LEXEM_H_

#ifdef __cplusplus
extern "C" {
#endif

  /*
    This is called a 'forward declaration': the actual definition of  a
    'struct lexem' is in lexem.c:16, and we only manipulate pointers to
    such lexem structures (observe the star in the typedef). This makes
    the definition of functions using this type legit, because pointers
    have all the same size.
  */
  typedef struct lexem *lexem_t;

  /*
    The end goal is to hide the definition to the user, so as to force
    him/her to use the functions below and s/he cannot tamper with the
    structure contents directly.

    This technique is called setting up an 'opaque type'.

    This is the exactly the same technique that is used in the Standard
    Library with the FILE* type: you do not want to know what's inside,
    you only need using fopen, fclose and friends to manipulate files.
  */

  /* Constructor */
  lexem_t lexem_new( char *type, char *value, int line, int column );

  /* Callbacks */
  int     lexem_print( void *_lex );
  int     lexem_delete( void *_lex );

#ifdef __cplusplus
}
#endif

#endif /* _LEXEM_H_ */
