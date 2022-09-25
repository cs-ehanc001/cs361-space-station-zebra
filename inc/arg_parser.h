#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <string_view>
#include <vector>

namespace ehanc {
class Arg_Parser
{
private:

  std::vector<std::string> m_args {};

public:

  /* {{{ doc */
  /**
   * Default Constructor
   *
   * Deleted to enforce construction with arguments
   */
  /* }}} */
  Arg_Parser() = delete;

  /* {{{ doc */
  /**
   * Value Constructor
   *
   * Arg_Parser needs access to arguments
   */
  /* }}} */
  Arg_Parser(const int argc, const char* const* const argv) noexcept;

  Arg_Parser(const Arg_Parser&)                    = delete;
  Arg_Parser(Arg_Parser&&)                         = delete;
  auto operator=(const Arg_Parser&) -> Arg_Parser& = delete;
  auto operator=(Arg_Parser&&) -> Arg_Parser&      = delete;

  /* {{{ doc */
  /**
   * Destructor
   *
   * Safely defaulted
   */
  /* }}} */
  ~Arg_Parser() noexcept = default;

  /* {{{ doc */
  /**
   * Short Argument Parsing
   *
   * Checks for a short argument, supports multiple arguments in
   * one shell "word"
   *
   * ex. ./my_prog -ft
   *
   * short arguments 'f' and 't' are true
   *
   * @param arg Argument to be checked for
   *
   * @return Whether or not argument has been passed to program
   */
  /* }}} */
  [[nodiscard]] auto shortArg(const char arg) const noexcept -> bool;

  /* {{{ doc */
  /**
   * Integer Long Argument Parsing
   *
   * Returns value after long argument, or, if argument not passed,
   * returns default_value.
   * If duplicate arguments are passed, the last one is used.
   *
   * ex. ./my_prog --value 3 --value 6
   *
   * argParser.intArg("value", 8); // returns 6
   * argParser.intArg("different", 8); // returns 8
   *
   * @param arg Name of argument to be checked for
   *
   * @param default_value Value to be returned if argument not found
   *
   * @return Value of argument, or default_value.
   * Returns default value if arg is not present or if
   * the next shell "word" is not a valid integer
   *
   */
  /* }}} */
  [[nodiscard]] auto intArg(const std::string& arg,
                            const int default_value) const noexcept -> int;

  /* {{{ doc */
  /**
   * String Long Argument Parsing
   *
   * Returns value after long argument, or, if argument not passed,
   * returns default_value.
   * If duplicate arguments are passed, the last one is used.
   *
   * ex. ./my_prog --value ignored --value neat
   *
   * argParser.strArg("value", "cool"); // returns "neat"
   * argParser.strArg("different", "cool"); // returns "cool"
   *
   * @param arg Name of argument to be checked for
   *
   * @param default_value Value to be returned if argument not found
   *
   * @return Value of argument, or default_value
   */
  /* }}} */
  [[nodiscard]] auto
  strArg(const std::string& arg,
         const std::string_view default_value) const noexcept
      -> std::string_view;

  /* {{{ doc */
  /**
   * Boolean Long Argument Parsing
   *
   * Checks if a long argument is present
   *
   * A boolean long argument is functionally equivalent to short argument
   *
   * @param arg Name of argument to be checked for
   *
   * @return Whether or not argument is present
   */
  /* }}} */
  [[nodiscard]] auto boolArg(const std::string& arg) const noexcept
      -> bool;

  /* {{{ doc */
  /**
   * Accessor for individual arguments
   *
   * Provides simple, read-only access to arguments
   *
   * @param index Argument number to access, excludes binary name.
   *
   * @return Read-only access to argument at specified index.
   * If out-of-bounds, returns a default-constructed string_view
   */
  /* }}} */
  auto arg(size_t index) const noexcept -> std::string_view;
};

} // namespace ehanc

#endif
