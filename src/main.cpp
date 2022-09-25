#include <fstream>
#include <iostream>
#include <string>

#include "utils/etc.hpp"

#include "arg_parser.h"
#include "constants.h"
#include "space_station.h"

// It's not that bad
// NOLINTNEXTLINE(readability-function-cognitive-complexity)
auto main(const int argc, const char* const* const argv) -> int
{
  ehanc::Arg_Parser arg_parser(argc, argv);

  if ( arg_parser.boolArg("help") || arg_parser.shortArg('h') ) {
    std::cout
        << "Space Station Zebra options:" << '\n'
        << "--help or -h : Print this help message" << '\n'
        << "--steps [value] : Choose number of time steps to perform "
        << "(default: " + std::to_string(conf::default_time_steps) + ")"
        << '\n'
        << "--logfile [path] : Choose path to log file" << '\n';

    if constexpr ( conf::print_to_console_by_default ) {
      std::cout << "--quiet or -q : Do not print to stdout" << '\n';
    } else {
      std::cout << "--print or -p : Print to stdout" << '\n';
    }

    if constexpr ( conf::write_to_logfile_by_default ) {
      std::cout << "--no-log or -n : Do not write to logfile" << '\n';
    } else {
      std::cout << "--log or -l : Write to logfile" << '\n';
    }

    return 0;
  }

  const int steps_to_perform {
      arg_parser.intArg("steps", conf::default_time_steps)};

  const std::string logfile {
      arg_parser.strArg("logfile", conf::default_log_file)};

  const bool print_to_console {[&]() {
    if constexpr ( conf::print_to_console_by_default ) {
      return not(arg_parser.boolArg("quiet") || arg_parser.shortArg('q'));
    } else {
      return arg_parser.boolArg("print") || arg_parser.shortArg('p');
    }
  }()}; // IILE

  const bool print_to_logfile {[&]() {
    if constexpr ( conf::write_to_logfile_by_default ) {
      return not(arg_parser.boolArg("no-log") || arg_parser.shortArg('n'));
    } else {
      return arg_parser.boolArg("log") || arg_parser.shortArg('l');
    }
  }()}; // IILE

  // Done parsing arguments

  space_station zebra("Zebra");
  std::ofstream fout;

  if ( print_to_logfile ) {
    fout.open(logfile.c_str());

    if ( !fout.is_open() ) {
      std::cout << "Error opening logfile" << '\n';

      if ( !print_to_console ) {
        std::cout << "Not printing to console either, aborting" << '\n';
        return 1;
      }
    }
  }

  for ( int i {0}; i != steps_to_perform; ++i ) {
    zebra.step();
    if ( print_to_console ) {
      zebra.display(std::cout);
    }
    if ( print_to_logfile ) {
      zebra.display(fout);
    }
    if ( zebra.queue_size() > conf::cutoff_queue_size ) {
      std::cout << "Queue size has exceeded cutoff of "
                << conf::cutoff_queue_size << " ships" << '\n';
      return 1;
    }
  }

  if ( fout.is_open() ) {
    fout << std::flush;
    fout.close();
  }

  return 0;
}
