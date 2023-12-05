/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

/* includes */
#include "channel.h"
#include "local_error.h"
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/* defines */

/* external declarations */

/* typedefs */
struct channel
{
  char *p1_buffer;
  size_t p1_buffer_size;
  pthread_cond_t new_data_available;
  pthread_mutex_t protect_p1_buffer;
};

/* global variable declarations */

/* static function */

/* external declarations */

struct channel *
create_channel ()
{
  struct channel *channel;

  channel = malloc (sizeof (struct channel));
  error_if (channel == NULL,
	    EXIT_FAILURE, errno, "malloc(%ld)", sizeof (struct channel));
  channel->p1_buffer = NULL;
  channel->p1_buffer_size = 0;
  channel->new_data_available = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
  channel->protect_p1_buffer = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

  return channel;
}

void
set_p1_record (struct channel *channel, const char *p1_record)
{
  int rc;

  if (p1_record == NULL)
    {
      return;
    }

  rc = pthread_mutex_lock (&channel->protect_p1_buffer);
  error_if (rc != 0, EXIT_FAILURE, rc, "pthread_mutex_lock()");

  size_t p1_record_size = strlen (p1_record) + 1;
  if (p1_record_size > channel->p1_buffer_size)
    {
      channel->p1_buffer = realloc (channel->p1_buffer, p1_record_size);
      error_if (channel->p1_buffer == NULL,
		EXIT_FAILURE, errno, "realloc(%ld)", p1_record_size);
      channel->p1_buffer_size = p1_record_size;
    }
  memcpy (channel->p1_buffer, p1_record, p1_record_size);

  rc = pthread_cond_broadcast (&channel->new_data_available);
  rc = pthread_mutex_unlock (&channel->protect_p1_buffer);
  error_if (rc != 0, EXIT_FAILURE, rc, "pthread_mutex_unlock()");
}

const char *
get_p1_record (struct channel *channel)
{
  int rc;

  if (channel->p1_buffer == NULL)
    {
      return NULL;
    }

  rc = pthread_mutex_lock (&channel->protect_p1_buffer);
  error_if (rc != 0, EXIT_FAILURE, rc, "pthread_mutex_lock()");
  rc =
    pthread_cond_wait (&channel->new_data_available,
		       &channel->protect_p1_buffer);

  const char *p1_record = strdup (channel->p1_buffer);
  error_if (p1_record == NULL, EXIT_FAILURE, errno, "strdup");

  rc = pthread_mutex_unlock (&channel->protect_p1_buffer);
  error_if (rc != 0, EXIT_FAILURE, rc, "pthread_mutex_unlock()");

  return p1_record;
}
