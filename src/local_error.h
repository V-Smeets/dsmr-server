/**
 * MIT License
 *
 * Copyright (c) 2023 Vincent Smeets
 */

#ifndef LOCAL_ERROR_H
#define LOCAL_ERROR_H

/* includes */
#include <errno.h>
#include <error.h>

/* defines */
#define return_on_error(condition, return_value, errnum, format, ...) \
  { \
    if (condition) \
      { \
	error(0, errnum, format, ##__VA_ARGS__); \
	return return_value; \
      } \
  }
#define	exit_on_error(condition, errnum, format, ...) \
  { \
    if (condition) \
      error(EXIT_FAILURE, errnum, format, ##__VA_ARGS__); \
  }

/* typedefs */

/* global variable declarations */

/* external declarations */

#endif
