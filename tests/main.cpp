#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <fmt/format.h>

TEST_CASE("Basic test") {
  CHECK(fmt::format("Hello, {}", "World") == "Hello, World");
}