/**
 * @file queue.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @brief Queue.
 *
 * Queue.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* NULL */

#include <pyas/queue.h>

struct link_t {
  void          *content;
  struct link_t *next;
};

queue_t queue_new( void ) {
  return NULL;
}

int     queue_empty( queue_t q ) {
  return queue_new() == q;
}

queue_t enqueue( queue_t q, void* object ) {
  struct link_t *new = queue_new();

  /* TODO! */

  return new;
}

list_t  queue_to_list( queue_t q ) {
  list_t l = list_new();

  /* TODO! */

  return l;
}
