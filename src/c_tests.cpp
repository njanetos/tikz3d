#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "common.h"

#include "c_line.h"
#include "c_polygon.h"

TEST_CASE("Splitting") {

    c_line line1(0, 0, 0, 1, 1, 1);

    c_polygon polygon(1, 0, 0, 0, 1, 0, 0, 0, 1);

    std::vector< std::vector<c_tikz_obj*> > splitted = line1.split(&polygon);

    REQUIRE( splitted.size() == 3 );
    REQUIRE( splitted[0].size() == 1 );
    REQUIRE( splitted[1].size() == 0 );
    REQUIRE( splitted[2].size() == 1 );

}
