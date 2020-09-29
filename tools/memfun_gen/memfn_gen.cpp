//
// Created by uyha on 26.09.2020.
//
#include "mem_fn_sig.hpp"

#include <cxxopts.hpp>

int main(int argc, char **argv) {
  using namespace cxxopts;

  auto format          = std::string{};
  auto config          = Config{};
  auto type_formatter  = TypeFormatter{};
  auto alias_formatter = AliasFormatter{};

  auto options = Options("MemFn", "A member function generator");

  // clang-format off
  options.add_options()
      ("f,format", "the format to be printed out following fmt syntax, 2 named arguments are `alias` and `type`", value(format))
      ("c,const", "const qualifiers of the member function", value(config.consts)->default_value("false,true"))
      ("v,volatile", "volatile qualifiers of the member function", value(config.volatiles)->default_value("false,true"))
      ("r,ref", "reference qualifiers of the member function", value(config.refs)->default_value("empty,lvalue,rvalue"))
      ("n,noexcept", "noexcept qualifiers of the member function", value(config.noexcepts)->default_value("false,true"))
      ("return_type", "the return type of the function type", value(type_formatter.rtn_type)->default_value("R"))
      ("class_type", "the class type of the function type", value(type_formatter.cls_type)->default_value("T"))
      ("arg_type", "the argument type of the function type", value(type_formatter.arg_type)->default_value("Args..."))
      ("name", "name of the alias", value(alias_formatter.name)->default_value("memfn"))
      ("const_prefix", "const prefix of the alias", value(alias_formatter.const_prefix)->default_value("const_"))
      ("volatile_prefix", "volatile prefix of the alias", value(alias_formatter.volatile_prefix)->default_value("volatile_"))
      ("cv_prefix", "cv prefix of the alias", value(alias_formatter.cv_prefix)->default_value("cv_"))
      ("noexcept_prefix", "noexcept prefix of the alias", value(alias_formatter.noexcept_prefix)->default_value("noexcept_"))
      ("empty_prefix", "prefix of the alias for no reference qualifier", value(alias_formatter.empty_prefix)->default_value(""))
      ("lvalue_prefix", "lvalue prefix of the alias", value(alias_formatter.lvalue_prefix)->default_value("lvalue_"))
      ("rvalue_prefix", "rvalue prefix of the alias", value(alias_formatter.rvalue_prefix)->default_value("rvalue_"))
      ("h,help", "Print usage");
  // clang-format on
  options.parse_positional({"format"});

  auto const result = options.parse(argc, argv);
  format += "\n";

  if (result.count("help")) {
    fmt::print("{}\n", options.help());
    return 0;
  }

  for (auto const &memfn : config.generate()) {
    fmt::print(format,
               fmt::arg("alias", memfn.alias(alias_formatter)),
               fmt::arg("type", memfn.type(type_formatter)));
  }

  return 0;
}