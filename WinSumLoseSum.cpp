#include "WinSumLoseSum.h"
using namespace std;

Optional<Set<int>> makeTarget(const Set<int>& elems, int target) {
    // Base case: target is 0 → success with empty set
    if (target == 0) return {};

    // Base case: no more elements to choose from
    if (elems.isEmpty()) return Nothing;

    // Recursive step: try including or excluding the first element
    int first = elems.first();
    Set<int> rest = elems;
    rest.remove(first);

    // Try including the first element
    Optional<Set<int>> with = makeTarget(rest, target - first);
    if (with != Nothing) {
        with.value().add(first);
        return with;
    }

    // Try excluding the first element
    Optional<Set<int>> without = makeTarget(rest, target);
    if (without != Nothing) {
        return without;
    }

    // No solution found
    return Nothing;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add at least one custom test here, then delete this comment. */




/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Works for an empty set of numbers.") {
    /* Can make 0, but not others. */
    EXPECT_EQUAL(makeTarget({ },  0), {});
    EXPECT_EQUAL(makeTarget({ },  1), Nothing);
    EXPECT_EQUAL(makeTarget({ }, -1), Nothing);
}

PROVIDED_TEST("Works for a one-element (singleton) set.") {
    /* Can make 0 and 137, but not others. */
    EXPECT_EQUAL(makeTarget({ 137 }, 0),   {});
    EXPECT_EQUAL(makeTarget({ 137 }, 137), {137});
    EXPECT_EQUAL(makeTarget({ 137 }, 1),   Nothing);
    EXPECT_EQUAL(makeTarget({ 137 }, -1),  Nothing);
}

PROVIDED_TEST("Works for a two-element (doubleton) set.") {
    EXPECT_EQUAL(makeTarget({ 1, 2 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 0), {});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 2), {2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 3), {1, 2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 4), Nothing);
}

PROVIDED_TEST("Works for a three-element set.") {

    /* Can make 0, 1, 3, 4, 5, 7, and 8, but not others. */
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  0), {});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  2), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  3), {3});
    EXPECT_NOT_EQUAL(makeTarget({ 1, 3, 4 }, 4), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  5), {1, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  6), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  7), {3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  8), {1, 3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  9), Nothing);
}

