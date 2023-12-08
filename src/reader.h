/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef READER_H
#define READER_H

/* includes */
#include "channel.h"
#include "options.h"

/* defines */

/* typedefs */

/* global variable declarations */

/* external declarations */

/**
 * @brief Start the reader thread.
 *
 * Start a new thread that will read P1 records from the serial port
 * and publish them on the channel.
 *
 * @param options The options that define the serial port.
 * @param channel The channel where the P1 record will be published.
 * @return The thread of the reader.
 */
extern pthread_t start_reader (options_t * options, channel_t * channel);

#endif
