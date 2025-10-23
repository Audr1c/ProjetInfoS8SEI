/**
 * @file char_set.c
 * @author Audric Siguret
 * @brief char_set
 *
 * char_set code, as in the project's pdf document
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <pyas/char_set.h>

void *group_interval_new(char start, char end){
  group_interval *group_interval = malloc(sizeof(group_interval));
  group_interval->start = start;
  group_interval->end = end;
  return group_interval;
}

int group_interval_delete(void *group_intervals){
  free(group_intervals);
  return 0;
}

int group_interval_print(void *v){
  //assert(g);
  gi *g = v;
  // special caracters (\n  \t)
  if (g->start == '\n' || g->start == '\t')
    return printf("\\%c", g->start == '\n' ? 'n' : 't');
  if (g->start == g->end)
    return printf("%c", g->start);
  return printf("%c-%c", g->start, g->end);
}
int char_in_group_interval(char c, group_interval group_interval){
  return group_interval.start <= c && c <= group_interval.end;
}


int char_in_group_intervals(char c, list_t group_intervals){
  list_t p ;
  for (
      p = group_intervals;
      !c_in(c, *(gi*)(car(p))) && !list_is_empty(p);
      p = cdr(p));

  return !list_is_empty(p);
}

int char_set_print(void *char_set){
  // TODO
  return 0;
}
int convert(char *regexp, char_set *char_set_regexp){

  // TODO



  return 0;

}