/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#include "options.h"

#include <boost/program_options.hpp>
#include <sstream>

#define OPTION_HELP_LONG "help"
#define OPTION_HELP_SHORT "h"
#define OPTION_HELP OPTION_HELP_LONG "," OPTION_HELP_SHORT
#define OPTION_DEVICE_LONG "device"
#define OPTION_DEVICE_SHORT "d"
#define OPTION_DEVICE OPTION_DEVICE_LONG "," OPTION_DEVICE_SHORT
#define DEFAULT_DEVICE "/dev/ttyUSB0"
#define OPTION_SPEED_LONG "speed"
#define OPTION_SPEED_SHORT "s"
#define OPTION_SPEED OPTION_SPEED_LONG "," OPTION_SPEED_SHORT
#define DEFAULT_SPEED B9600
#define OPTION_PORT_LONG "port"
#define OPTION_PORT_SHORT "p"
#define OPTION_PORT OPTION_PORT_LONG "," OPTION_PORT_SHORT
#define DEFAULT_PORT 8120

namespace dsmr_server {

/**
 * Class to hold the port number. Needed for overloading the validate function.
 */
struct port_container {
  in_port_t port;
  port_container(in_port_t port) : port(port) {}
  port_container &operator=(const port_container &other) {
    if (this == &other)
      return *this;
    port = other.port;
    return *this;
  }
};

/**
 * @brief Validate the option value for a port.
 *
 * Validate that the option value for a port is within the allowed range.
 *
 * The values in xs are validated and converted to the desired type. The result
 * is then retuned by the parameter v. The last two parameters are only there to
 * specify the template types.
 *
 * @param v The validated value.
 * @param xs The values that the user has given for this option.
 * @exception boost::program_options::invalid_option_value An invalid option
 * has been given.
 */
void validate(boost::any &v, const std::vector<std::string> &xs,
              port_container *, long) {
  using namespace boost;
  using namespace boost::program_options;

  validators::check_first_occurrence(v);
  const std::string &s = validators::get_single_string(xs);
  try {
    const unsigned long port = lexical_cast<unsigned long>(s);
    if (port < IPPORT_USERRESERVED || port > in_port_t(-1))
      throw invalid_option_value("Port " + std::to_string(port) +
                                 " not in the range " +
                                 std::to_string(IPPORT_USERRESERVED) + ".." +
                                 std::to_string(in_port_t(-1)));
    v = any(port_container(port));
  } catch (const bad_lexical_cast &) {
    throw invalid_option_value(s);
  }
}

/**
 * Class to hold the speed value. Needed for overloading the validate function.
 */
struct speed_container {
  speed_container(speed_t speed) : speed(speed) {}
  speed_t speed;
  speed_container &operator=(const speed_container &other) {
    if (this == &other)
      return *this;
    speed = other.speed;
    return *this;
  }
};

/**
 * @brief Validate the option value for a speed.
 *
 * Validate that the option value is an allowed speed/baudrate value.
 *
 * The values in xs are validated and converted to the desired type. The result
 * is then retuned by the parameter v. The last two parameters are only there to
 * specify the template types.
 *
 * @param v The validated value.
 * @param xs The values that the user has given for this option.
 * @exception boost::program_options::invalid_option_value An invalid option
 * has been given.
 */
void validate(boost::any &v, const std::vector<std::string> &xs,
              speed_container *, long) {
  using namespace boost;
  using namespace boost::program_options;

  validators::check_first_occurrence(v);
  const std::string &s = validators::get_single_string(xs);
  try {
    const unsigned long ulSpeed = lexical_cast<unsigned long>(s);
    speed_t speed = DEFAULT_SPEED;
    switch (ulSpeed) {
    case 0:
      speed = B0;
      break;
    case 50:
      speed = B50;
      break;
    case 75:
      speed = B75;
      break;
    case 110:
      speed = B110;
      break;
    case 134:
      speed = B134;
      break;
    case 150:
      speed = B150;
      break;
    case 200:
      speed = B200;
      break;
    case 300:
      speed = B300;
      break;
    case 600:
      speed = B600;
      break;
    case 1200:
      speed = B1200;
      break;
    case 1800:
      speed = B1800;
      break;
    case 2400:
      speed = B2400;
      break;
    case 4800:
      speed = B4800;
      break;
    case 9600:
      speed = B9600;
      break;
    case 19200:
      speed = B19200;
      break;
    case 38400:
      speed = B38400;
      break;
    default:
      throw invalid_option_value("Invalid speed: " + std::to_string(ulSpeed));
    }
    v = any(speed_container(speed));
  } catch (const bad_lexical_cast &) {
    throw invalid_option_value(s);
  }
}

static boost::program_options::options_description get_descriptions() {
  using namespace boost::program_options;

  options_description description("Allowed options");
  description.add_options()              //
      (OPTION_HELP, "This help message") //
      (OPTION_DEVICE, value<std::string>()->default_value(DEFAULT_DEVICE),
       "The serial device from which the server will read the P1 records.") //
      (OPTION_SPEED,
       value<speed_container>()->default_value(speed_container(DEFAULT_SPEED),
                                               std::to_string(DEFAULT_SPEED)),
       "The speed that will be used to read from the serial device.") //
      (OPTION_PORT,
       value<port_container>()->default_value(port_container(DEFAULT_PORT),
                                              std::to_string(DEFAULT_PORT)),
       "The network port on which the server will listen for incoming "
       "connections.") //
      ;

  return description;
}

Options::Options() {}

Options::Options(int argc, char *argv[]) {
  using namespace boost::program_options;

  store(parse_command_line(argc, argv, get_descriptions()), option_values);
  notify(option_values);
}

bool Options::isHelp() { return option_values.count(OPTION_HELP_LONG); }

std::ostream &operator<<(std::ostream &os, const Options &options) {
  return os << (get_descriptions());
}

std::string Options::getDevice() {
  return option_values[OPTION_DEVICE_LONG].as<std::string>();
}

speed_t Options::getSpeed() {
  return option_values[OPTION_SPEED_LONG].as<speed_container>().speed;
}

in_port_t Options::getPort() {
  return option_values[OPTION_PORT_LONG].as<port_container>().port;
}

} // namespace dsmr_server
