//
// Created by uyha on 26.09.2020.
//

#pragma once

#include <fmt/compile.h>
#include <istream>
#include <map>

enum class RefQualifier { empty, lvalue, rvalue };
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
};
