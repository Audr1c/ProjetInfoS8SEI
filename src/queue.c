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
  struct link_t *new = malloc(sizeof(*new));
  assert(new);
  struct link_t *maillon = malloc(sizeof(*maillon));
  assert(maillon);
  new->next = maillon;
  new->contents = object;
  if (queue_empty(q))
  {
    // in this case create a new link linking back to itself
    maillon->next = maillon;
    
    return new;
  }
  else{
    maillon->next = (q->next)->next;
    (q->next)->next = maillon;
    q->next = maillon;
    return new;
  }
  /* ! */

  return new;
}

list_t  queue_to_list( queue_t q ) {
  list_t l = list_new();

  /* TODO! */

  return l;
}

queue_t queue_dequeue(queue_t q, void **object)
{
  struct link_t *queue = (q->next);
  struct link_t *head = queue->next;
  struct link_t *new_head = head->next;
  // get head value 
  assert(object);
  *object = head->contents;
  if (head == queue)
  {
    free(head);
    free(q);
    return queue_new();
  }
  // free head
  free(head);
  // update queue
  queue->next = new_head;

  /* ! */

  return q;
}

queue_t queue_free(queue_t q, action_t delete)
{

  
  struct link_t *queue = (q->next);
  struct link_t *head = queue->next;
  struct link_t *new_head = head->next;

  /* ! */
  while (queue != head)
  {
    new_head = head->next;
    delete(head->contents);
    free(head);
    head = new_head;
  }
  free(queue);
  free(q);

  return queue_new();
}

int queue_print(queue_t q, action_t print)
{
  

  int ret = printf("(%s", queue_empty(q) ? "" : " ");
  if (!queue_empty(q)){

    link_t *queue = (q->next);
    link_t *head = (queue->next);

    while (head != queue)
    {
      ret += print ? print(head->contents) : printf("#OBJECT#");
      ret += printf(" ");
      head = head->next;
    }
    ret += print ? print(queue->contents) : printf("#OBJECT#");
    ret += printf(" ");
  }
  return ret + printf(")");
  /* ! */
  
  
}
