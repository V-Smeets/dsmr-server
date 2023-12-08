/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

/* includes */
#include "reader.h"
#include "local_error.h"
#include <pthread.h>
#include <stdlib.h>

/* defines */

/* external declarations */

/* typedefs */

/* global variable declarations */

/* static function */

static void *
reader (void *arg)
{
  return NULL;
}

/* external declarations */

pthread_t
start_reader (options_t *options, channel_t *channel)
{
  pthread_t reader_thread;

  int rc = pthread_create (&reader_thread, NULL, &reader, NULL);
  error_if (rc != 0, EXIT_FAILURE, rc, "pthread_create()");

  return reader_thread;
}
