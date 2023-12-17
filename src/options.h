/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef OPTIONS_H
#define OPTIONS_H

/* includes */
#include <netinet/in.h>
#include <stdbool.h>
#include <termios.h>

/* defines */

/* typedefs */

/**
 * The object that hold the parsed options.
 */
typedef struct options options_t;

/* global variable declarations */

/* external declarations */

/**
 * @brief Parse the command line options.
 *
 * @param argc, argv The command line arguments.
 * @return The parsed options.
 * @return On error: NULL
 */
extern options_t *options_parse (int argc, char *argv[]);

/**
 * @brief Get the name of the serial device.
 *
 * @param options The parsed options.
 * @return The name of the serial device.
 */
extern char *options_get_device (options_t * options);

/**
 * @brief Get the baud rate for the serial device.
 *
 * @param options The parsed options.
 * @return The baud rate for the serial device.
 */
extern speed_t options_get_baud_rate (options_t * options);

/**
 * @brief Get the port to listen on for connections.
 *
 * @param options The parsed options.
 * @return The port to listen on for connections.
 */
extern in_port_t options_get_port (options_t * options);

/**
 * @brief Is the verbose flag set?
 *
 * @param options The parsed options.
 * @return true in case the verbose flag is set.
 */
extern bool options_is_verbose (options_t * options);

#endif
