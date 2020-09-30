//
// Created by uyha on 26.09.2020.
//
#include "memfn_sig.hpp"

#include <cxxopts.hpp>

int main(int argc, char **argv) {
  using namespace cxxopts;

  auto format             = std::string{};
  auto configs            = std::vector<Config>{};
  auto variable_formatter = VariableFormatter{};
  auto alias_formatter    = AliasFormatter{};

  auto options = Options("MemFn", "A member function generator");

  // clang-format off
  options.add_options()
      ("f,format", "the format to be printed out following fmt syntax, 2 named arguments are `alias` and `type`", value(format))
      ("c,config", "const volatile ref noexcept config of the member function", value(configs)->default_value("3373"))
      ("return_type", "the return type of the function type", value(variable_formatter.rtn_type)->default_value("R"))
      ("class_type", "the class type of the function type", value(variable_formatter.cls_type)->default_value("T"))
      ("name", "name of the variable", value(variable_formatter.var_name)->default_value("fn"))
      ("arg_type", "the argument type of the function type", value(variable_formatter.arg_type)->default_value("Args..."))
      ("alias", "name of the alias", value(alias_formatter.name)->default_value("memfn"))
      ("const_prefix", "const prefix of the alias", value(alias_formatter.const_prefix)->default_value("const_"))
      ("volatile_prefix", "volatile prefix of the alias", value(alias_formatter.volatile_prefix)->default_value("volatile_"))
      ("cv_prefix", "cv prefix of the alias", value(alias_formatter.cv_prefix)->default_value("cv_"))
      ("noexcept_prefix", "noexcept prefix of the alias", value(alias_formatter.noexcept_prefix)->default_value("noexcept_"))
      ("empty_prefix", "prefix of the alias for no reference qualifier", value(alias_formatter.empty_prefix))
      ("lvalue_prefix", "lvalue prefix of the alias", value(alias_formatter.lvalue_prefix)->default_value("lvalue_"))
      ("rvalue_prefix", "rvalue prefix of the alias", value(alias_formatter.rvalue_prefix)->default_value("rvalue_"))
      ("h,help", "Print usage");
  // clang-format on
  options.parse_positional({"format"});

  auto const result = options.parse(argc, argv);

  if (result.count("help") || format.empty()) {
    fmt::print("{}\n", options.help());
    return 0;
  }

  if (!format.ends_with('\n')) {
    format += "\n";
  }

  for (auto const &config : configs) {
    for (auto const &memfn : config.generate()) {
      fmt::print(format,
                 fmt::arg("alias", memfn.alias(alias_formatter)),
                 fmt::arg("var", memfn.type(variable_formatter)),
                 fmt::arg("type", memfn.var(variable_formatter)));
    }
  }

  return 0;
}