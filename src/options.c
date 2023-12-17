/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

/* includes */
#include "local_error.h"
#include "options.h"
#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

/* defines */
#define	DEFAULT_DEVICE		"/dev/ttyUSB0"
#define DEFAULT_BAUD_RATE	B9600
#define DEFAULT_PORT		(IPPORT_USERRESERVED + 1)
#define DEFAULT_VERBOSE		false

/* external declarations */

/* typedefs */
struct options
{
  char *device;
  speed_t baud_rate;
  unsigned int port;
  bool verbose;
};

/* global variable declarations */

/* static function */

/**
 * Convert the baud rate from an integer value to speed_t.
 * On error: UINT_MAX is returned.
 */
static speed_t
get_baud_rate (unsigned long baud_rate)
{
  switch (baud_rate)
    {
    case 0:
      return B0;
    case 50:
      return B50;
    case 75:
      return B75;
    case 110:
      return B110;
    case 134:
      return B134;
    case 150:
      return B150;
    case 200:
      return B200;
    case 300:
      return B300;
    case 600:
      return B600;
    case 1200:
      return B1200;
    case 1800:
      return B1800;
    case 2400:
      return B2400;
    case 4800:
      return B4800;
    case 9600:
      return B9600;
    case 19200:
      return B19200;
    case 38400:
      return B38400;
    default:
      return UINT_MAX;
    }
}

/* external declarations */

struct options *
options_parse (int argc, char *argv[])
{
  assert (argc >= 0);
  assert (argv != NULL);

  static struct option long_options[] = {
    {"device", required_argument, NULL, 'd'},
    {"baud_rate", required_argument, NULL, 'b'},
    {"port", required_argument, NULL, 'p'},
    {"verbose", no_argument, NULL, 'v'},
    {0, 0, 0, 0}
  };
  int longindex = 0;

  struct options *options;

  options = malloc (sizeof (struct options));
  return_on_error (options == NULL, NULL,
		   errno, "malloc(%ld)", sizeof (struct options));
  options->device = strdup (DEFAULT_DEVICE);
  return_on_error (options->device == NULL, NULL,
		   errno, "strdup(\"%s\")", DEFAULT_DEVICE);
  options->baud_rate = DEFAULT_BAUD_RATE;
  options->port = DEFAULT_PORT;
  options->verbose = DEFAULT_VERBOSE;

  while (true)
    {
      int opt_char =
	getopt_long (argc, argv, "d:b:p:v", long_options, &longindex);
      if (opt_char == -1)
	{
	  break;
	}
      switch (opt_char)
	{
	case 'd':
	  if (options->device != NULL)
	    {
	      free (options->device);
	    }
	  options->device = strdup (optarg);
	  return_on_error (options->device == NULL, NULL,
			   errno, "strdup(\"%s\")", optarg);
	  break;

	case 'b':
	  unsigned long baud_rate = strtoul (optarg, NULL, 0);
	  return_on_error (baud_rate == ULONG_MAX, NULL,
			   errno, "strtoul(\"%s\")", optarg);
	  options->baud_rate = get_baud_rate (baud_rate);
	  return_on_error (options->baud_rate == UINT_MAX, NULL,
			   0, "Invalid baud rate: %ld", baud_rate);
	  break;

	case 'p':
	  unsigned long port = strtoul (optarg, NULL, 0);
	  return_on_error (port == ULONG_MAX, NULL,
			   errno, "strtoul(\"%s\")", optarg);
	  return_on_error (port < IPPORT_USERRESERVED
			   || port > USHRT_MAX, NULL,
			   0,
			   "Invalid port number: %ld. Must be between %d and %d",
			   port, IPPORT_USERRESERVED, USHRT_MAX);
	  options->port = htons (port);
	  break;

	case 'v':
	  options->verbose = true;
	  break;

	case '?':
	  exit (EXIT_FAILURE);

	}
    }

  return options;
}

char *
options_get_device (struct options *options)
{
  assert (options != NULL);

  return options->device;
}

speed_t
options_get_baud_rate (struct options *options)
{
  assert (options != NULL);

  return options->baud_rate;
}

in_port_t
options_get_port (struct options *options)
{
  assert (options != NULL);

  return options->port;
}

bool
options_is_verbose (struct options *options)
{
  assert (options != NULL);

  return options->verbose;
}
