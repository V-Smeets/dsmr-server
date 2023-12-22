/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#include "p1_record.h"

#include <boost/crc.hpp>
#include <regex>

namespace dsmr_server {

RawP1Record::RawP1Record(std::string p1RecordString) {
  using namespace std;

  regex startOfRecordPattern("^/(...5)");
  regex endOfRecordPattern("!([0-9a-zA-Z]{4})\\r\\n");

  smatch startOfRecordMatch;
  if (!regex_search(p1RecordString, startOfRecordMatch, startOfRecordPattern))
    throw invalid_argument("No start of P1 record found");

  smatch endOfRecordMatch;
  if (!regex_search(p1RecordString.cbegin() + startOfRecordMatch.position(),
                    p1RecordString.cend(), endOfRecordMatch,
                    endOfRecordPattern))
    throw invalid_argument("No end of P1 record found");

  string crcData = p1RecordString.substr(startOfRecordMatch.position(),
                                         endOfRecordMatch.position(1) -
                                             startOfRecordMatch.position());
  string crcExpectedString = endOfRecordMatch.str(1);
  uint_fast16_t crcExpected = stoul(crcExpectedString, NULL, 16);

  boost::crc_optimal<16, 0x8005, 0, 0, true, true> crc_16;
  crc_16.process_bytes(crcData.c_str(), crcData.length());
  uint_fast16_t crcComputed = crc_16.checksum();
  if (crcComputed != crcExpected)
    throw invalid_argument("Incorrect checksum");

  this->p1RecordString = p1RecordString;
}

} // namespace dsmr_server
