#include <catch2/catch_test_macros.hpp>
#include <river/fn.hpp>
#include <utility>

struct UserClass {
  auto operator()(int){};

  int a = 1;
};

template <typename>
struct print_type;

TEST_CASE("fn_trait_of invocables will look at its operator() if possible, then it will look at the given value") {
  using namespace river;

  constexpr auto lambda = [] {};
  STATIC_CHECK(std::is_same_v<fn_trait_of<lambda>, fn_trait<void (decltype(lambda)::*)() const>>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<UserClass{}>, fn_trait<void (UserClass::*)(int)>>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<&UserClass::a>, fn_trait<int UserClass::*>>);
}
