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

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  group_interval_list();

  exit(EXIT_SUCCESS);
}
