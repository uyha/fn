//
// Created by uyha on 24.09.2020.

// sml dependency injection doesn't support overload, hence overload is disabled
// to integrate with sml
#define FN_ENABLE_OVERLOAD 0
#if defined(_MSC_VER)
#define FN_NO_PROPAGATE_NOEXCEPT 1
#endif

#include <catch2/catch.hpp>
#include <fn/fn.hpp>
#include <sml/sml.hpp>

struct next {};
struct s1 {};
struct s2 {};
struct s3 {};
struct s4 {};
struct s5 {};
struct s6 {};

void action1_impl() {}
void action2_impl() noexcept {}

struct SM {
  void action3_impl() {}
  void action4_impl() const {}
  void action5_impl() noexcept {}
  void action6_impl() const noexcept {}

  auto operator()() {
    using namespace boost::sml;
    using namespace river;

    auto const action1 = fn<&action1_impl>{};
    auto const action2 = fn<&action2_impl>{};
    auto const action3 = fn<&SM::action3_impl>{};
    auto const action4 = fn<&SM::action4_impl>{};
    auto const action5 = fn<&SM::action5_impl>{};
    auto const action6 = fn<&SM::action6_impl>{};

    return make_transition_table(*state<s1> + event<next> / action1 = state<s2>,
                                 state<s2> + event<next> / action2  = state<s3>,
                                 state<s3> + event<next> / action3  = state<s4>,
                                 state<s4> + event<next> / action4  = state<s5>,
                                 state<s5> + event<next> / action5  = state<s6>,
                                 state<s6> + event<next> / action6  = X);
  }
};

TEST_CASE("Integration with sml") {
  SM state{};
  auto state_machine = boost::sml::sm<SM>{state};
  REQUIRE(state_machine.is(boost::sml::state<s1>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::state<s2>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::state<s3>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::state<s4>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::state<s5>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::state<s6>));
  state_machine.process_event(next{});
  REQUIRE(state_machine.is(boost::sml::X));
}