#include <algorithm>
#include <string>
#include <string_view>

#include "arg_parser.h"

namespace ehanc {

Arg_Parser::Arg_Parser(const int argc,
                       const char* const* const argv) noexcept
{
  // Not storing binary name, hence subtracting 1
  m_args.reserve(static_cast<size_t>(argc - 1));

  for ( int i = 1; i < argc; ++i ) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    m_args.emplace_back(argv[i]);
  }
}

auto Arg_Parser::shortArg(const char arg) const noexcept -> bool
{

  return (
      // Any of the arguments
      std::any_of(
          m_args.cbegin(), m_args.cend(),
          [arg](const std::string& an_arg) -> bool {
            return (
                (
                    // Exactly one '-' (short argument block)
                    std::count(an_arg.cbegin(), an_arg.cend(), '-') == 1)
                && (
                    // Previous single '-' appears as first character
                    an_arg[0] == '-')
                && (
                    // Argument contains the
                    // single-character short argument
                    std::find(an_arg.cbegin(), an_arg.cend(), arg)
                    != an_arg.cend()));
          }));
}

auto Arg_Parser::intArg(const std::string& arg,
                        const int default_value) const noexcept -> int
{

  // Iterator to argument in question, or crend() if not found
  auto it = std::find(m_args.crbegin(), m_args.crend(), ("--" + arg));

  if ( it != m_args.crend() ) {
    try {
      // Reverse iterator, thus the integer
      // will be found by decrementing
      // the reverse iterator
      return (std::stoi(*(--it)));
    } catch ( ... ) {
      // default returned if *(--it) is not a valid integer
      return default_value;
    }
  }

  return default_value;
}

auto Arg_Parser::strArg(const std::string& arg,
                        const std::string_view default_value)
    const noexcept -> std::string_view
{
  auto it = std::find(m_args.crbegin(), m_args.crend(), ("--" + arg));

  if ( it != m_args.crend() ) {
    return *(--it);
  }

  return default_value;
}

auto Arg_Parser::boolArg(const std::string& arg) const noexcept -> bool
{
  return std::find(m_args.cbegin(), m_args.cend(), ("--" + arg))
         != m_args.cend();
}

auto Arg_Parser::arg(size_t index) const noexcept -> std::string_view
{
  return (index < m_args.size() ? m_args[index] : std::string_view {});
}

} // namespace ehanc
