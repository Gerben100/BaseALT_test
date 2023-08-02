#define CATCH_CONFIG_MAIN
#include "library.h"
#include "library.cpp"
#include <catch2/catch.hpp>


TEST_CASE("Test singleCompareVersion function") {

    SECTION("Test versions without releases") {
        REQUIRE(singleCompareVersion("1.2", "", "1.1", "") == true);
        REQUIRE(singleCompareVersion("1.10", "", "1.2", "") == true);
        REQUIRE(singleCompareVersion("2.0", "", "2.0", "") == false);
        REQUIRE(singleCompareVersion("2.0", "", "2.1", "") == false);
        REQUIRE(singleCompareVersion("2.2", "", "2.10", "") == false);
        REQUIRE(singleCompareVersion("", "", "", "") == false);
    }

    SECTION("Test versions with releases") {
        REQUIRE(singleCompareVersion("3.0", "rc1", "2.5", "") == true);
        REQUIRE(singleCompareVersion("2.3", "", "2.3", "rc2") == false);
        REQUIRE(singleCompareVersion("2.3", "rc2", "2.3", "rc1") == true);
        REQUIRE(singleCompareVersion("1.0", "beta", "1.0", "alpha") == true);
        REQUIRE(singleCompareVersion("2.0", "rc3", "2.0", "rc3") == false);
        REQUIRE(singleCompareVersion("2.0", "alt3.10", "2.0", "alt3.2") == true);
        REQUIRE(singleCompareVersion("2.0", "alt_test", "2.0", "alt") == true);
}
}
