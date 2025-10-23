/**
 * @file test-char_set.c
 * @author Audric Siguret
 * @brief Unit tests for char_set.
 *
 * Unit tests for char_set.
 */

#include <pyas/char_set.h>
#include <unitest/unitest.h>

/*

  The purpose of this file is to get you started for testing your regexp engine.

  From a purely combinatorial perspective, designing an exhaustive set of tests
  for regexp matching is impossible because (1) a regexp implements a
  deterministic finite automaton and (2) the size of the set of C-strings is:
  $$\sum_{i=1}^{2^48} 256^i$$
  (on an amd64 machine, just like the one you are probably using right now).

  That's the main reason why we shall focus on positive tests below.

  Yet, your little regexp engine will be constructed by *incrementally* adding
  support for various operators: we tell you how to match a constant regexp (one
  that does not contain any regexp operator) and a regexp containing `.` and/or
  `*` operators -- and you will add support for regexp operators `+` and `?`,
  etc.

  Also, remember that we are only supposed to match a regexp against the *start*
  of `source`!

  Now we need some systematic way of writing our tests for the operators. We
  propose the following strategy:
  - First we ensure core positive/negative properties of an operator (e.g., `*`
    operator must have a preceding char, etc.),
  - Then we ensure its behaviour is correct whether it appears (1) at the
    beginning, (2) in the middle, and (3) at the end of a regexp.

  Then it remains to test the behaviour of the legal combinations that were not
  covered by the above. In the present situation with the sole `.` and `*`
  operators available, the only remaining, uncovered legal combination is `.*`.

  That's because `*.` should have been covered in the tests above by "continuity
  by concatenation" (between a regexp that ends in `*` and another that starts
  in `.`), but `.*` was not tested already as the operators were tested
  separately and `*` refers to its preceding character.

  This gives us a blueprint for our testing strategy:
  1. pre/post-conditions;
  2. constant regexps;
  3. regexps containing `.`;
  4. regexps containing `*`;
  5. regexps containing `.*`.


  Obviously, any extension of these tests should be *justified* along the same
  lines. Similarly, the logic of any new group of tests for any new module
  should be *justified* in some way.

*/

static void group_interval_list( void ) {
  /* No relevant post-condition was identified, except return values. */

  char      *end;

  test_suite( "List of group interval" );

  list_t groupI = list_new();

  groupI = cons( group_interval_new('a', 'd'), groupI );
  groupI = cons(group_interval_new('e', 'e'), groupI);
  groupI = cons(group_interval_new('\n', '\n'), groupI);

  test_assert(list_length(groupI) == 3, "The list has the correct length");


  
  test_oracle_start(stdout);
  list_print(groupI, group_interval_print);
  test_oracle_check("  List is printed as ( a-d e \\n )", "( a-d e \\n )");


  groupI = cons(group_interval_new('\t', '\t'), groupI);

  // appartenace test 
  // Single groupe
  test_assert(char_in_group_interval('a', *group_interval_new('a', 'a')), 
            "a is in the groupe a-a");

  test_assert(!char_in_group_interval('b', *group_interval_new('a', 'a')),
              "b is not in the groupe a-a");

  test_assert(char_in_group_interval('h', *group_interval_new('a', 'z')),
              "h is in the groupe a-z");

  test_assert(!char_in_group_interval('4', *group_interval_new('a', 'z')),
              "4 is not in the groupe a-z");
}

static void re_constant( void ) {
  char      *end;

  test_suite( "Constant regexps" );

  test_assert( !re_match( "abc", "ab", NULL ),
               "The whole regexp must match" );


  test_assert(  re_match( "a", "abc", &end ),
                "Can match a single char" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "bc" );

  test_assert(  re_match( "ab", "abc", &end ),
                "Can match prefix string" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "c" );

  test_assert(  re_match( "abc", "abc", &end ),
                "Can match last string" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is empty", "" );

}

static void re_dot( void ) {
  char      *end;

  test_suite( "`.` core properties" );

  test_assert( !re_match( ".", "", NULL ),
               "The empty source does *not* match `.`" );

  test_assert(  re_match( ".", "z", NULL ) && re_match( ".", "abc", &end ),
                "Any character matches `.`" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "bc" );


  test_suite( "`.` continuity" );

  test_assert(  re_match( ".ip", "zipend", &end ),
                "Can match `.` at start of regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "end" );

  test_assert(  re_match( "z.p", "zipend", &end ),
                "Can match `.` inside regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "end" );

  test_assert(  re_match( "zi.", "zipend", &end ),
                "Can match `.` at end of regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "end" );

  return;
}

static void re_star( void ) {
  char      *end;

  test_suite( "`*` core properties" );

  test_assert( !re_match( "*", "aaaa", &end ),
               "Cannot match `*` at start of regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And end == source", "aaaa" );

  test_assert( !re_match( "a**", "aaaabb", &end ),
               "Cannot match `*` without preceding char" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And end == source", "aaaabb" );

  test_assert(  re_match( "a*", "", NULL ),
                "Can match the empty source" );

  test_assert(  re_match( "a*", "baaaaa", &end ),
                "Can match zero character" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And end == source", "baaaaa" );

  test_assert(  re_match( "a*", "abb", &end ),
                "Can match one character" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "bb" );

  test_assert(  re_match( "a*", "aaaaaaabb", &end ),
                "Can match several characters" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "bb" );


  test_suite( "`*` continuity" );

  test_assert(  re_match( "z*ip", "zipend", &end ),
                "Can match `*` at start of regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( " And suffix is OK", "end" );

  test_assert(  re_match( "zi*p", "zipend", &end ),
                "Can match `*` inside regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "end" );

  test_assert(  re_match( "zip*", "zipend", &end ),
                "Can match `*` at end of regexp" );

  test_oracle_start( stdout );
  printf( "%s", end );
  test_oracle_check( "  And suffix is OK", "end" );

  return;
}

static void re_dot_star( void ) {
  char      *end;

  test_suite( "`.*` properties" );

  test_assert(  re_match( ".*", "", &end ) && !*end,
                "`.*` matches the empty string" );

  test_assert(  re_match( ".*", "any string ;-)", &end ) && !*end,
                "[Theorem] `.*` is the set of finite strings" );

  test_assert(  re_match( "abc.*", "abcdef", &end ) && !*end,
                "`prefix.*` can match any prefix" );

  test_assert(  re_match( ".*def", "abcdef", &end ) && !*end,
                "`.*suffix` can match any suffix" );

  test_assert(  re_match( "abc.*def", "abcABSORBMEdefend", &end ),
                "[Corollary] `.*` is absorbant" );

  test_oracle_start( stdout );
  printf( "%s" , end );
  test_oracle_check( "  And suffix is OK", "end" );

}

static void re_plus(void)
{
  char *end;

  test_suite("`+` core properties");

  test_assert(!re_match("+", "aaaa", &end),
              "Cannot match `+` at start of regexp");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And end == source", "aaaa");

  test_assert(!re_match("a++", "aaaabb", &end),
              "Cannot match `+` without preceding char");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And end == source", "aaaabb");

  test_assert(!re_match("a+", "", NULL),
              "Can't match an empty source");

  test_assert(!re_match("a+", "baaaaa", &end),
              "Can't match zero character");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And end == source", "baaaaa");

  test_assert(re_match("a+", "abb", &end),
              "Can match one character");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "bb");

  test_assert(re_match("a+", "aaaaaaabb", &end),
              "Can match several characters");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "bb");

  test_suite("`+` continuity");

  test_assert(re_match("z+ip", "zipend", &end),
              "Can match `*` at start of regexp");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check(" And suffix is OK", "end");

  test_assert(re_match("zi+p", "zipend", &end),
              "Can match `*` inside regexp");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "end");

  test_assert(re_match("zip+", "zipend", &end),
              "Can match `*` at end of regexp");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "end");

  return;
}

static void re_plus_star(void)
{
  char *end;

  test_suite("`.+` properties");

  test_assert(!re_match(".+", "", &end) && !*end,
              "can't match empty strings");

  test_assert(re_match(".+", "any string ;-)", &end) && !*end,
              "[Theorem] `.+` is the set of finite strings");
    

  test_assert(re_match("abc.+", "abcdef", &end) && !*end,
              "`prefix.*` can match any prefix");

  test_assert(!re_match("abc.+", "abc", &end) && !*end,
              "`prefix.*` can't match any prefix if there is none");

  test_assert(re_match(".*def", "abcdef", &end) && !*end,
              "`.*suffix` can match any suffix");

  test_assert(!re_match(".def", "def", &end) ,
              "`.suffix` can't match any suffix suffix if there is none");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "ef");
  

  test_assert(!re_match(".+def", "def", &end) ,
              "`.+suffix` can't match any suffix suffix if there is none");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "def");


  test_assert(re_match("abc.+def", "abcABSORBMEdefend", &end),
              "[Corollary] `.+` is absorbant");

  test_oracle_start(stdout);
  printf("%s", end);
  test_oracle_check("  And suffix is OK", "end");
}

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  re_pre_post();
  re_constant();
  re_dot();
  re_star();
  re_dot_star();
  re_plus();
  re_plus_star();

  exit( EXIT_SUCCESS );
}
