
# AC_LANG_CALL_CXX
# $1	PROLOGUE	The prologue to insert before the start of the main
# 			function.
# $2	STATEMENT	The statement to insert in the main function. The
#			statement will be terminated by a semicolon.
# ------------------------------------------------------------------------------
m4_define([AC_LANG_CALL_CXX],
[AC_LANG_PROGRAM([[$1
]],
[[$2;]])])

# AC_CHECK_CXXLIB
# $1	LIBRARY		The library to check.
# $2	PROLOGUE	The prologue to insert before the start of the main
# 			function.
# $3	STATEMENT	The statement to insert in the main function. The
#			statement will be terminated by a semicolon.
# $4	[ACTION-IF-FOUND]
# 			The action to be executed in case the statement could
# 			be found in the library.
# $5	[ACTION-IF-NOT-FOUND]
# 			The action to be executed in case the statement couldn't
# 			be found in the library.
# $6	[OTHER-LIBRARIES]
# 			Other libraries that are needed during this check.
# ------------------------------------------------------------------------------
AC_DEFUN([AC_CHECK_CXXLIB], [
  m4_ifval([$4], , [AH_CHECK_LIB([$1])])dnl
  AS_LITERAL_WORD_IF([$1],
    [AS_VAR_PUSHDEF([ac_Lib], [ac_cv_lib_$1_$3])],
    [AS_VAR_PUSHDEF([ac_Lib], [ac_cv_lib_$1""_$3])])dnl
  m4_pushdef([AC_LANG_CALL(C++)], m4_defn([AC_LANG_CALL_CXX]))
  AC_CACHE_CHECK([for $3 in -l$1], [ac_Lib],
    [ac_check_lib_save_LIBS=$LIBS
LIBS="-l$1 $6 $LIBS"
AC_LINK_IFELSE([AC_LANG_CALL([$2], [$3])],
  [AS_VAR_SET([ac_Lib], [yes])],
  [AS_VAR_SET([ac_Lib], [no])])
LIBS=$ac_check_lib_save_LIBS])
  m4_popdef([AC_LANG_CALL(C++)])
  AS_VAR_IF([ac_Lib], [yes],
    [m4_default([$4], [AC_DEFINE_UNQUOTED(AS_TR_CPP(HAVE_LIB$1))
LIBS="-l$1 $LIBS"
])],
    [$5])
  AS_VAR_POPDEF([ac_Lib])dnl
])

# vim:ai:sw=2:
