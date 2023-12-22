/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef P1_RECORD_H
#define P1_RECORD_H

#include <string>

namespace dsmr_server {

/**
 * @brief A raw P1 record.
 *
 * This is the string version of a P1 record. It starts with a header and ends
 * with a check sum.
 */
class RawP1Record {

public:
  /**
   * @brief Create a new raw P1 record.
   *
   * The p1RecordString is checked for a correct header and matching check sum.
   * The first complete P1 record found in the string is then used.
   *
   * @param p1RecordString A string that contains a P1 record.
   * @exception std::invalid_argument The provided p1RecordString doesn't
   * contain a valid P1 record.
   */
  RawP1Record(std::string p1RecordString);

  /**
   * @brief Convert to a string.
   *
   * @return The P1 record as a string.
   */
  std::string toString() { return p1RecordString; }

private:
  /**
   * @brief A string that contains a P1 record, including header and valid check
   * sum.
   */
  std::string p1RecordString;
};

} // namespace dsmr_server

#endif
