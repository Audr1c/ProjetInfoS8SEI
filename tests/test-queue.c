/**
 * @file test-queue.c
 * @author Audric Siguret 
 *
 * Tests unitaires pour les "files"
 */

 #include <pyas/all.h>
 #include <unitest/unitest.h>
 
 #include <assert.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <unistd.h>
 /* 
 
 
 TODODODO
 
 

 */
 static void queue_core( void ) {
 
   test_assert( queue_empty( queue_new() ),
                "A new queue is empty" );

   test_abort(queue_dequeue(queue_new(), NULL),
              "An empty queue has no first element");

   test_oracle_start( stdout );
   queue_print( queue_new(), NULL );
   test_oracle_check( "An empty queue is printed as ()", "()" );
 }
 
 /*
   Let's make a list of `int`.
 
   First, we need a constructor to allocate an `int` from a given value:
 */
 static void *int_new( int v ) {
   int *p = calloc( 1, sizeof( *p ) );
   assert( p );
   *p = v;
   return p;
 }
 
 /*
   Two action_t callbacks for deleting and printing an `int`.
 
   Deleting is easy, as free(3) only needs a generic address too:
  */
 static int int_delete( void *p ) {
   free( p );
   return 0;
 }
 
 /*
   Idiomatic callback start: first cast generic pointer to
   type of object we know we store in the links:
  */
 static int int_print( void *p ) {
   int *v = p;
   return printf( "%d", *v );
 }
 
 /*
   That's all there is to make a list of any kind of objetcs!
  */
 
 static void queue_construct( void ) {
   int array[ 4 ] = { 1, 2, 3, 4 };
   int i;
 
   queue_t q = queue_new();
 
 
   for ( i = 0 ; i < 4 ; i++ ) {
     q = enqueue( int_new( array[ i ] ), q );
     // can only test if not empty
     test_assert( !queue_empty( q ), 
                  "Can construct a queue of %d element%s", i+1, (i+1)>1 ? "s" : "" );
     
     
   }
   

 
   test_oracle_start( stdout );
   list_print( q, int_print );
   test_oracle_check( "Can print a non-empty queue", "( 1 2 3 4 )" );
 
   for ( i = 0 ; i < 4 ; i++ ) {
     int * p = int_new(-1);
     q = queue_dequeue( q, &p);
     test_assert(array[i] == *(int *)p,
                 "Insertion order was OK");
      int_delete( p );
     
   }

   test_assert(list_is_empty(q),
               "queue is empty after removal of all elements");
               
  test_oracle_start( stdout );
  queue_print( q, int_print );
  test_oracle_check( "Can print an empty queue", "()" );
  for (i = 0; i < 4; i++)
  {
    q = enqueue(int_new(array[i]), q);
  }
   queue_free( q, int_delete );

   test_assert(q==NULL, "queue is freed");
   return;
 }
 
 int main ( int argc, char *argv[] ) {
 
   unit_test( argc, argv );
 
   test_suite( "Empty queue core properties" );
 
   queue_core( );
 
   test_suite( "Constructing and deleting queue" );
 
   queue_construct( );
 
   exit( EXIT_SUCCESS );
 }
 