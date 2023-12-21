/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#include "channel.h"
#include "options.h"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  using namespace boost::program_options;
  using namespace dsmr_server;
  using namespace std;

  Options options;
  try {
    options = dsmr_server::Options(argc, argv);

    if (options.isHelp()) {
      cerr << options << endl;
      return EXIT_FAILURE;
    }
  } catch (invalid_option_value &e) {
    cerr << options << endl;
    return EXIT_FAILURE;
  }

  [[maybe_unused]] dsmr_server::Channel channel = dsmr_server::Channel();

  return EXIT_SUCCESS;
}
