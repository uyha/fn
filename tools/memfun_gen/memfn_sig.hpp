//
// Created by uyha on 26.09.2020.
//

#pragma once

#include <ctll/fixed_string.hpp>
#include <ctre/functions.hpp>
#include <fmt/compile.h>
#include <istream>
#include <map>
#include <range/v3/view/cartesian_product.hpp>

enum class RefQualifier : std::uint8_t { empty, lvalue, rvalue };
std::istream &operator>>(std::istream &is, RefQualifier &ref) {
  std::string raw(std::istreambuf_iterator<char>{is}, {});
  if (raw == "empty")
    ref = RefQualifier::empty;
  else if (raw == "lvalue")
    ref = RefQualifier::lvalue;
  else if (raw == "rvalue")
    ref = RefQualifier::rvalue;
  else
    throw std::invalid_argument{fmt::format(
        FMT_COMPILE(
            "{} is not a value ref qualifier (only `empty`, `lvalue`, `rvalue` are allowed)"),
        raw)};
  return is;
}
auto operator|(RefQualifier lhs, RefQualifier rhs) noexcept -> RefQualifier {
  return static_cast<RefQualifier>(
      static_cast<std::uint8_t>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs)));
}
auto operator&(RefQualifier lhs, RefQualifier rhs) noexcept -> RefQualifier {
  return static_cast<RefQualifier>(
      static_cast<std::uint8_t>(static_cast<std::uint8_t>(lhs) & static_cast<std::uint8_t>(rhs)));
}
auto operator^(RefQualifier lhs, RefQualifier rhs) noexcept -> RefQualifier {
  return static_cast<RefQualifier>(
      static_cast<std::uint8_t>(static_cast<std::uint8_t>(lhs) ^ static_cast<std::uint8_t>(rhs)));
}

struct TypeFormatter {
  std::string rtn_type{"R"};
  std::string cls_type{"T"};
  std::string arg_type{"Args..."};
};

struct AliasFormatter {
  std::string name{"memfn"};
  std::string const_prefix{"const_"};
  std::string volatile_prefix{"volatile_"};
  std::string cv_prefix{"cv_"};
  std::string noexcept_prefix{"noexcept_"};
  std::string empty_prefix{};
  std::string lvalue_prefix{"lvalue_"};
  std::string rvalue_prefix{"rvalue_"};
};

struct VariableFormatter : TypeFormatter {
  std::string var_name{"fn"};
};

struct MemFn {
  bool is_const{false};
  bool is_volatile{false};
  RefQualifier ref_qualifier{RefQualifier::empty};
  bool is_noexcept{false};

  friend bool operator==(MemFn const &lhs, MemFn const &rhs) noexcept {
    return lhs.is_const == rhs.is_const && lhs.is_volatile == rhs.is_volatile
        && lhs.ref_qualifier == rhs.ref_qualifier && lhs.is_noexcept == rhs.is_noexcept;
  }
  friend bool operator!=(MemFn const &lhs, MemFn const &rhs) noexcept {
    return !(lhs == rhs);
  }

  [[nodiscard]] auto alias(AliasFormatter const &formatter = {}) const -> std::string {
    static const std::map<std::pair<bool, bool>, std::string_view> cv_map{
        {{false, false}, ""},
        {{false, true}, formatter.volatile_prefix},
        {{true, false}, formatter.const_prefix},
        {{true, true}, formatter.cv_prefix},
    };
    const std::map<RefQualifier, std::string_view> ref_map = {
        {RefQualifier::empty, formatter.empty_prefix},
        {RefQualifier::lvalue, formatter.lvalue_prefix},
        {RefQualifier::rvalue, formatter.rvalue_prefix}};
    const std::map<bool, std::string_view> noexcept_map = {{false, ""},
                                                           {true, formatter.noexcept_prefix}};

    std::string_view const cv_prefix       = cv_map.at({is_const, is_volatile});
    std::string_view const ref_prefix      = ref_map.at(ref_qualifier);
    std::string_view const noexcept_prefix = noexcept_map.at(is_noexcept);

    return fmt::format(
        FMT_COMPILE("{}{}{}{}"), ref_prefix, noexcept_prefix, cv_prefix, formatter.name);
  }
  [[nodiscard]] auto type(TypeFormatter const &formatter = {}) const -> std::string {
    static const std::map<std::pair<bool, bool>, std::string_view> cv_map{
        {{false, false}, ""},
        {{false, true}, " volatile"},
        {{true, false}, " const"},
        {{true, true}, " const volatile"},
    };
    static const std::map<RefQualifier, std::string_view> ref_map{
        {RefQualifier::empty, ""}, {RefQualifier::lvalue, " &"}, {RefQualifier::rvalue, " &&"}};

    std::string_view const cv_spec       = cv_map.at({is_const, is_volatile});
    std::string_view const ref_spec      = ref_map.at(ref_qualifier);
    std::string_view const noexcept_spec = is_noexcept ? " noexcept" : "";

    return fmt::format(FMT_COMPILE("{} ({}::*) ({}){}{}{}"),
                       formatter.rtn_type,
                       formatter.cls_type,
                       formatter.arg_type,
                       cv_spec,
                       ref_spec,
                       noexcept_spec);
  }
  [[nodiscard]] auto var(VariableFormatter const &formatter = {}) const -> std::string {
    static const std::map<std::pair<bool, bool>, std::string_view> cv_map{
        {{false, false}, ""},
        {{false, true}, " volatile"},
        {{true, false}, " const"},
        {{true, true}, " const volatile"},
    };
    static const std::map<RefQualifier, std::string_view> ref_map{
        {RefQualifier::empty, ""}, {RefQualifier::lvalue, " &"}, {RefQualifier::rvalue, " &&"}};

    std::string_view const cv_spec       = cv_map.at({is_const, is_volatile});
    std::string_view const ref_spec      = ref_map.at(ref_qualifier);
    std::string_view const noexcept_spec = is_noexcept ? " noexcept" : "";

    return fmt::format(FMT_COMPILE("{} ({}::*{}) ({}){}{}{}"),
                       formatter.rtn_type,
                       formatter.cls_type,
                       formatter.var_name,
                       formatter.arg_type,
                       cv_spec,
                       ref_spec,
                       noexcept_spec);
  }
};
struct MemFnMask {
  enum Operator { or_op, and_op, xor_op };

  Operator op;
  bool const_mask{true};
  bool volatile_mask{true};
  RefQualifier ref_mask{RefQualifier::empty};
  bool noexcept_mask{true};

  static constexpr auto pattern = ctll::fixed_string{"([\\|&^])([01])([01])([0-2])([01])"};
  static auto parse(std::string_view source) -> MemFnMask {
    auto mask = MemFnMask{};
    auto const &[whole, op, const_mask, volatile_mask, ref_mask, noexcept_mask] =
        ctre::match<pattern>(source);

    if (!whole)
      throw std::invalid_argument(fmt::format(FMT_COMPILE("{} is not a valid mask"), source));

    mask.op            = op.to_view() == "|" ? Operator::or_op
                       : op.to_view() == "&" ? Operator::and_op
                                             : Operator::xor_op;
    mask.const_mask    = const_mask.to_view() == "1";
    mask.volatile_mask = volatile_mask.to_view() == "1";
    mask.ref_mask      = const_mask.to_view() == "0" ? RefQualifier::empty
                       : const_mask.to_view() == "1" ? RefQualifier::lvalue
                                                     : RefQualifier::rvalue;
    mask.noexcept_mask = noexcept_mask.to_view() == "1";

    return mask;
  }
  friend std::istream &operator>>(std::istream &is, MemFnMask &mask) {
    auto raw = std::string{std::istreambuf_iterator<char>{is}, {}};
    mask     = parse(raw);
    return is;
  }
  friend MemFn operator|(MemFn const &lhs, MemFnMask const &rhs) {
    return {lhs.is_const || rhs.const_mask,
            lhs.is_volatile || rhs.volatile_mask,
            lhs.ref_qualifier | rhs.ref_mask,
            lhs.is_noexcept || rhs.noexcept_mask};
  }
  friend MemFn operator&(MemFn const &lhs, MemFnMask const &rhs) {
    return {lhs.is_const && rhs.const_mask,
            lhs.is_volatile && rhs.volatile_mask,
            lhs.ref_qualifier & rhs.ref_mask,
            lhs.is_noexcept && rhs.noexcept_mask};
  }
  friend MemFn operator^(MemFn const &lhs, MemFnMask const &rhs) {
    return {lhs.is_const != rhs.const_mask,
            lhs.is_volatile != rhs.volatile_mask,
            lhs.ref_qualifier ^ rhs.ref_mask,
            lhs.is_noexcept != rhs.noexcept_mask};
  }
  [[nodiscard]] auto mask(MemFn memfn) const noexcept -> MemFn {
    switch (op) {
    case Operator::or_op:
      return memfn | *this;
    case Operator::and_op:
      return memfn & *this;
    case Operator::xor_op:
      return memfn ^ *this;
    }
  }
};

auto parse_1_3(char selection_char) -> std::vector<bool> {
  auto result = std::vector<bool>{};
  result.reserve(2);

  std::uint8_t selection = selection_char - '0';

  if (selection < 1u || selection > 3u)
    throw std::invalid_argument(
        fmt::format("{} is not a valid argument, only 1, 2, or 3 are allowed", selection));

  if (selection & 1u)
    result.emplace_back(false);
  if (selection & 2u)
    result.emplace_back(true);

  return result;
}
auto parse_ref(char selection_char) -> std::vector<RefQualifier> {
  auto result = std::vector<RefQualifier>{};
  result.reserve(2);

  std::uint8_t selection = selection_char - '0';

  if (selection < 1u || selection > 7u)
    throw std::invalid_argument(
        fmt::format("{} is not a valid argument, only 1 to 7 are allowed", selection));

  if (selection & 1u)
    result.emplace_back(RefQualifier::empty);
  if (selection & 2u)
    result.emplace_back(RefQualifier::lvalue);
  if (selection & 4u)
    result.emplace_back(RefQualifier::rvalue);

  return result;
}

struct Config {
  std::vector<bool> consts{false, true};
  std::vector<bool> volatiles{false, true};
  std::vector<RefQualifier> refs{RefQualifier::empty, RefQualifier::lvalue, RefQualifier::rvalue};
  std::vector<bool> noexcepts{false, true};

  [[nodiscard]] auto generate() const -> std::vector<MemFn> {
    using namespace ranges;
    auto member_functions = std::vector<MemFn>{};
    for (auto const &[ref, is_noexcept, is_volatile, is_const] :
         views::cartesian_product(refs, noexcepts, volatiles, consts)) {
      member_functions.push_back(MemFn{.is_const      = is_const,
                                       .is_volatile   = is_volatile,
                                       .ref_qualifier = ref,
                                       .is_noexcept   = is_noexcept});
    }
    return member_functions;
  }

  static constexpr auto pattern = ctll::fixed_string{"([1-3])([1-3])([1-7])([1-3])"};
  static auto parse(std::string_view source) -> Config {
    auto config                                             = Config{};
    auto const &[whole, consts, volatiles, refs, noexcepts] = ctre::match<pattern>(source);

    if (!whole)
      throw std::invalid_argument(fmt::format("{} is not a config", source));

    config.consts    = parse_1_3(consts.to_view()[0]);
    config.volatiles = parse_1_3(volatiles.to_view()[0]);
    config.refs      = parse_ref(refs.to_view()[0]);
    config.noexcepts = parse_1_3(noexcepts.to_view()[0]);

    return config;
  }
  friend std::istream &operator>>(std::istream &is, Config &config) {
    auto raw = std::string{std::istreambuf_iterator<char>{is}, {}};
    config   = parse(raw);

    return is;
  }
};
