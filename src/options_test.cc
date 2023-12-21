/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#include "options.h"

#include <boost/program_options.hpp>
#include <climits>
#include <gtest/gtest.h>
#include <string.h>

namespace dsmr_server {
namespace {

class OptionsTest : public testing::Test {
protected:
  OptionsTest() {
    execName = strdup("execName");
    optionH = strdup("-h");
    optionHelp = strdup("--help");
    optionD = strdup("-d");
    optionDevice = strdup("--device");
    optionDeviceValue = strdup("/dev/ttyTest");
    optionS = strdup("-s");
    optionSpeed = strdup("--speed");
    optionP = strdup("-p");
    optionPort = strdup("--port");
  }

  ~OptionsTest() {
    free(execName);
    free(optionH);
    free(optionHelp);
    free(optionD);
    free(optionDevice);
    free(optionDeviceValue);
    free(optionS);
    free(optionSpeed);
    free(optionP);
    free(optionPort);
  }

  char *getExecName() { return execName; }
  char *getOptionH() { return optionH; }
  char *getOptionHelp() { return optionHelp; }
  char *getOptionD() { return optionD; }
  char *getOptionDevice() { return optionDevice; }
  char *getOptionDeviceValue() { return optionDeviceValue; }
  char *getOptionS() { return optionS; }
  char *getOptionSpeed() { return optionSpeed; }
  char *getOptionP() { return optionP; }
  char *getOptionPort() { return optionPort; }

private:
  char *execName;
  char *optionH;
  char *optionHelp;
  char *optionD;
  char *optionDevice;
  char *optionDeviceValue;
  char *optionS;
  char *optionSpeed;
  char *optionP;
  char *optionPort;
};

TEST_F(OptionsTest, getHelpShort) {
  char *argv[] = {getExecName(), getOptionH()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_TRUE(options.isHelp());
}

TEST_F(OptionsTest, getHelpLong) {
  char *argv[] = {getExecName(), getOptionHelp()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_TRUE(options.isHelp());
}

TEST_F(OptionsTest, getDeviceDefault) {
  std::string expected("/dev/ttyUSB0");

  char *argv[] = {getExecName()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getDevice());
}

TEST_F(OptionsTest, getDeviceShort) {
  std::string expected(getOptionDeviceValue());

  char *argv[] = {getExecName(), getOptionD(), getOptionDeviceValue()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getDevice());
}

TEST_F(OptionsTest, getDeviceLong) {
  std::string expected(getOptionDeviceValue());

  char *argv[] = {getExecName(), getOptionDevice(), getOptionDeviceValue()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getDevice());
}

TEST_F(OptionsTest, getSpeedDefault) {
  speed_t expected = B9600;

  char *argv[] = {getExecName()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getSpeed());
}

TEST_F(OptionsTest, getSpeedShort) {
  char buffer[32];
  speed_t expected = B50;
  sprintf(buffer, "%d", 50);

  char *argv[] = {getExecName(), getOptionS(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getSpeed());
}

TEST_F(OptionsTest, getSpeedLong) {
  char buffer[32];
  speed_t expected = B110;
  sprintf(buffer, "%d", 110);

  char *argv[] = {getExecName(), getOptionSpeed(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getSpeed());
}

TEST_F(OptionsTest, getSpeedLongInvalid) {
  char buffer[32];
  sprintf(buffer, "%d", 123);

  char *argv[] = {getExecName(), getOptionSpeed(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  EXPECT_THROW(Options options(argc, argv),
               boost::program_options::invalid_option_value);
}

TEST_F(OptionsTest, getPortDefault) {
  in_port_t expected = 8120;

  char *argv[] = {getExecName()};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getPort());
}

TEST_F(OptionsTest, getPortShort) {
  char buffer[32];
  in_port_t expected = 8111;
  sprintf(buffer, "%d", expected);

  char *argv[] = {getExecName(), getOptionP(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getPort());
}

TEST_F(OptionsTest, getPortLong) {
  char buffer[32];
  in_port_t expected = 8999;
  sprintf(buffer, "%d", expected);

  char *argv[] = {getExecName(), getOptionPort(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  Options options(argc, argv);

  EXPECT_EQ(expected, options.getPort());
}

TEST_F(OptionsTest, getPortLongTooLow) {
  char buffer[32];
  in_port_t expected = IPPORT_USERRESERVED - 1;
  sprintf(buffer, "%d", expected);

  char *argv[] = {getExecName(), getOptionPort(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  EXPECT_THROW(Options options(argc, argv),
               boost::program_options::invalid_option_value);
}

TEST_F(OptionsTest, getPortLongTooHigh) {
  char buffer[32];
  int expected = USHRT_MAX + 1;
  sprintf(buffer, "%d", expected);

  char *argv[] = {getExecName(), getOptionPort(), buffer};
  int argc = sizeof(argv) / sizeof(argv[0]);

  EXPECT_THROW(Options options(argc, argv),
               boost::program_options::invalid_option_value);
}

} // namespace
} // namespace dsmr_server
