/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include "p1_record.h"

namespace dsmr_server {

/**
 * @brief A channel to distribute P1 reords.
 *
 * A channel to distribute P1 records between different threads. Multiple
 * threads can wait for a new P1 record. When then one threads sends a new P1
 * record, the all the waiting threads will receive this new P1 record.
 */
class Channel {

public:
  /**
   * @brief Send a P1 record.
   *
   * Send a P1 record in the channel. All the threads that are waiting for a new
   * P1 record, will get now this record.
   *
   * @param p1Record The P1 record.
   */
  void sendP1Record(RawP1Record p1Record);

  /**
   * @brief Wait for a P1 record.
   *
   * Wait for a P1 record. The method returns with the P1 record that an other
   * threads has send. This method will always wait for a new P1 reord. It will
   * never return an old (existing) record.
   *
   * @return The P1 record.
   */
  RawP1Record waitForP1Record();
};

} // namespace dsmr_server

#endif
