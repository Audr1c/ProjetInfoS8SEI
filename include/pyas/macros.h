/**
 * @file macros.h
 * @author François Cayre <cayre@uvolante.org>
 * @brief A few useful macros and other handy stuff.
 *
 * A few useful macros.
 */

#ifndef _MACROS_H_
#define _MACROS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define UNUSED(thing) ((void)(thing))

#define STRLEN 255
  typedef char string[ 1+STRLEN ];

#define string_init( string ) memset( (string), '\0', 1+STRLEN )

#ifdef __cplusplus
}
#endif

#endif /* _MACROS_H_ */
