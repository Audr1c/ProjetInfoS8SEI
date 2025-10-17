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
   
 
   test_abort( queue_dequeue( list_new(), NULL, NULL),
               "An empty queue has no first element" );
   
  
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
 
 static void list_construct( void ) {
   int array[ 4 ] = { 1, 2, 3, 4 };
   int i;
 
   list_t l = list_new();
 
 
   for ( i = 0 ; i < 4 ; i++ ) {
     l = list_add_first( int_new( array[ i ] ), l );
     test_assert( (size_t)(i+1) == list_length( l ),
                  "Can construct a list of %d element%s", i+1, (i+1)>1 ? "s" : "" );
     test_assert( array[ i ] == *(int*)list_first( l ),
                  "Insertion order is OK" );
   }
 
   test_assert( !list_is_empty( l ),
                "A constructed list is not empty" );
 
   test_oracle_start( stdout );
   list_print( l, int_print );
   test_oracle_check( "Can print a non-empty list", "( 4 3 2 1 )" );
 
   for ( i = 0 ; i < 4 ; i++ ) {
     l = list_del_first( l, int_delete );
     test_assert( (size_t)(4-i-1) == list_length( l ),
                  "Can remove from a list of %d element%s", 4-i, (4-i)>1 ? "s" : "" );
   }
 
   test_assert( list_is_empty( l ),
                "List is empty after removal of all elements" );
 
   return;
 }
 
 int main ( int argc, char *argv[] ) {
 
   unit_test( argc, argv );
 
   test_suite( "Empty list core properties" );
 
   list_core( );
 
   test_suite( "Constructing and deleting lists" );
 
   list_construct( );
 
   exit( EXIT_SUCCESS );
 }
 