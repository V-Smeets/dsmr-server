/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef CHANNEL_H
#define CHANNEL_H

/* includes */

/* defines */

/* typedefs */

/**
 * The object that holds the channel.
 */
typedef struct channel channel_t;

/* global variable declarations */

/* external declarations */

/**
 * @brief Create a channel.
 *
 * Create an initialize a channel so that it can be used to publish P1 record.
 *
 * @return The channel.
 */
extern channel_t *create_channel ();

/**
 * @brief Publish a new P1 record.
 *
 * A new P1 record is made availabe for publication.
 *
 * @param channel The channel where the P1 record is published.
 * @param p1_record The new P1 record.
 */
extern void set_p1_record (channel_t * channel, const char *p1_record);

/**
 * @brief Get a new P1 record.
 *
 * A new P1 record will be requested.
 * Every call to this function will get a different P1 record.
 *
 * @param channel The channel where the P1 record has been published.
 * @return The P1 record.
 *         The memory should be freed by the caller.
 */
extern const char *get_p1_record (channel_t * channel);

#endif
