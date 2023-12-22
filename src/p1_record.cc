/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#include "p1_record.h"

#include <boost/crc.hpp>
#include <regex>
#ifdef DEBUG
#include <iostream>
#endif

namespace dsmr_server {

RawP1Record::RawP1Record(std::string p1RecordString) {
  using namespace std;

  static regex startOfRecordPattern("^/(...5)");
  static regex endOfRecordPattern("!([0-9a-zA-Z]{4})\\r\\n");

  smatch startOfRecordMatch;
  if (!regex_search(p1RecordString, startOfRecordMatch, startOfRecordPattern))
    throw invalid_argument("No start of P1 record found");

  smatch endOfRecordMatch;
  if (!regex_search(p1RecordString.cbegin() + startOfRecordMatch.position(),
                    p1RecordString.cend(), endOfRecordMatch,
                    endOfRecordPattern))
    throw invalid_argument("No end of P1 record found");

  string crcData = p1RecordString.substr(startOfRecordMatch.position(),
                                         endOfRecordMatch.position() -
                                             startOfRecordMatch.position() + 1);
  string crcExpectedString = endOfRecordMatch.str(1);
  size_t crcExpectedEndIndex = 0;
  boost::crc_16_type::value_type crcExpected =
      stoul(crcExpectedString, &crcExpectedEndIndex, 16);
  if (crcExpectedEndIndex != 4) {
    throw invalid_argument("No valid checksum length found");
  }
#ifdef DEBUG
  cout << "crcExpected: " << crcExpected << endl;
#endif

  boost::crc_16_type crc_16;
  crc_16.process_bytes(crcData.c_str(), crcData.length());
  boost::crc_16_type::value_type crcComputed = crc_16.checksum();
#ifdef DEBUG
  cout << "crcComputed: " << crcComputed << endl;
#endif
  if (crcComputed != crcExpected) {
    throw invalid_argument("No valid checksum found");
  }

  this->p1RecordString = p1RecordString;
}

} // namespace dsmr_server
