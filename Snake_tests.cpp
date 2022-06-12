/// \file
/// <summary>
/// File with tests
/// </summary>
#include "Snake.cpp"
#include "Class.hpp"
#include <algorithm>
#include <doctest.h>

TEST_CASE("Working Important") {
	REQUIRE(Important(5) == "value > 0");
	REQUIRE(Important(0) == "value = 0");
	REQUIRE(Important(-5) == "value < 0");
}

TEST_CASE("Testing Important") {
	REQUIRE(Important(1000) == "value > 0");
	REQUIRE(Important(323232) == "value > 0");
	REQUIRE(Important(0) == "value = 0");
}

TEST_CASE("Testing Work") {
	REQUIRE(Work(0) == false);
	REQUIRE(Work(1) == true);
	REQUIRE(Work(10) == "Error");
}

TEST_CASE("Testing Work Hard") {
	REQUIRE(Work(-1) == "Error");
	REQUIRE(Work(0) == false);
	REQUIRE(Work(10000) == "Error");
}

TEST_CASE("Testing Errors Module") {
	REQUIRE(Errors(-1) == "Unknown error");
	REQUIRE(Errors(1) == "Fatal error");
	REQUIRE(Errors(3) == "Syntax error");
}

TEST_CASE("Testing Errors Hard") {
	REQUIRE(Errors(100000) == "Unknown error");
	REQUIRE(Errors(0) == "Unknown error");
	REQUIRE(Errors(2) == "Logical error");
}
