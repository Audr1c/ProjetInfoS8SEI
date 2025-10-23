/**
 * @file char_set.h
 * @author Audric Siguret 
 * @brief Char_set type
 *
 * General include for char set, group interval.., as in the project's pdf document
 */

#ifndef _CHAR_SET_H_
#define _CHAR_SET_H_

#ifdef __cplusplus
extern "C" {
#endif

# include <pyas/list.h>
#define ZERO 0
#define ONE 1
#define ZERO_OR_ONE 2
#define ZERO_OR_MORE 3
#define ONE_OR_MORE 4

typdef struct
{
    char start;
    char end;
} group_interval, gi;

void * group_interval_new( char start, char end );

int group_interval_delete( void *group_intervals );

int group_interval_print( void *group_interval );

int char_in_group_interval( char c, gi group_interval );

int char_in_group_intervals( char c,  list_t group_intervals );

typdef struct
{
    list_t group_intervals; 
    int type; // ZERO or ONE or ZERO_OR_ONE or ZERO_OR_MORE or ONE_OR_MORE
} char_set;


/*
Now we need to convert every possible regexp in a char_set


*/

int char_set_print( void *char_set );

int convert( char *regexp, char_set *char_set_regexp );

#define c_in(c, group_interval) char_in_group_interval( (c),  (group_interval))
#define c_ins(c, group_intervals) char_in_group_intervals((c), (group_intervals))

#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
