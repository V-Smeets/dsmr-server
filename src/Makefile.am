# MIT License
#
# Copyright (c) 2023 Vincent Smeets

bin_PROGRAMS	=
check_PROGRAMS	= $(TESTS)
dist_man_MANS	=
TESTS		=

bin_PROGRAMS		+= dsmr_server
dist_man_MANS		+= dsmr_server.1
dsmr_server_SOURCES	= dsmr_server.cc
dsmr_server_CPPFLAGS	= $(BOOST_CPPFLAGS)
dsmr_server_LDFLAGS	= $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
dsmr_server_LDADD	= $(BOOST_PROGRAM_OPTIONS_LIBS)

dsmr_server_SOURCES	+= options.h options.cc
TESTS			+= options_test
options_test_SOURCES	= options_test.cc
options_test_CPPFLAGS	= $(BOOST_CPPFLAGS)
options_test_LDFLAGS	= $(BOOST_PROGRAM_OPTIONS_LIBS)
options_test_LDADD	= options.$(OBJEXT)

dsmr_server_SOURCES	+= p1_record.h p1_record.cc
TESTS			+= p1_record_test
p1_record_test_SOURCES	= p1_record_test.cc
p1_record_test_CPPFLAGS	= $(BOOST_CPPFLAGS)
p1_record_test_LDADD	= p1_record.$(OBJEXT)
