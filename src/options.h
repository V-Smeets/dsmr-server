/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <netinet/in.h>
#include <string>
#include <termios.h>

namespace dsmr_server {

/**
 * @brief Parse the options.
 *
 * The class Options will parse the command line arguments.
 * The allowed options are made available to the application.
 */
class Options {

public:
  /**
   * @brief Create an empty options object.
   *
   * Create a new instance of this class. All the options have their default
   * value.
   *
   * @return The created instance.
   */
  Options();

  /**
   * @brief Parse the command line arguments.
   *
   * Create a new instance of this class and parse the command line arguments.
   * In case an unknown option is found, then an error message is displayed and
   * the application exits.
   *
   * @param[in] argc The number of elements in argv.
   * @param[in] argv The command line arguments.
   * @return The created instance.
   * @exception boost::program_options::invalid_option_value An invalid option
   * has been given.
   */
  Options(int argc, char *argv[]);

  /**
   * @brief Is help requested?
   *
   * @return true in case help is requested.
   */
  bool isHelp();

  /**
   * @brief Give an overview of the available options.
   *
   * @param os The output stream where the overview is written to.
   * @param options The options.
   */
  friend std::ostream &operator<<(std::ostream &os, const Options &options);

  /**
   * @brief Get the name of the serial device.
   *
   * @return The name of the device.
   */
  std::string getDevice();

  /**
   * @brief Get the speed for the serial device.
   *
   * @return The speed for the device. (as a baudrate)
   */
  speed_t getSpeed();

  /**
   * @brief Get the TCP port.
   *
   * @return The TCP port.
   */
  in_port_t getPort();

private:
  /**
   * The map that holds the parsed option values.
   */
  boost::program_options::variables_map option_values;
};

} // namespace dsmr_server
#endif
