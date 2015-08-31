#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "c_line.h"
#include "c_polygon.h"

TEST_CASE("Splitting") {

    c_line line1(0, 0, 0, 1, 1, 1);

    c_polygon polygon(1, 0, 0, 0, 1, 0, 0, 0, 1);

    REQUIRE( line1.sx == 0 );

}
