/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

/* includes */
#include "channel.h"
#include "options.h"
#include "reader.h"
#include <stdlib.h>

/* defines */

/* external declarations */

/* typedefs */

/* global variable declarations */

/* static function */

int
main (int argc, char *argv[])
{
  options_t *options = options_parse (argc, argv);
  channel_t *channel = create_channel ();

  pthread_t reader_tid = start_reader (options, channel);

  return EXIT_SUCCESS;
}
