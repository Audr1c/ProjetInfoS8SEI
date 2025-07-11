/**
 * @file regexp.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @brief General include for regexp
 *
 * General include for regexp, as in the project's pdf document
 */

#ifndef _REGEXP_H_
#define _REGEXP_H_

#ifdef __cplusplus
extern "C" {
#endif


  int re_match( char *regexp , char *source , char **end );


#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
