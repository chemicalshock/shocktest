# --------------------------------------------------------------------
#
# !\file makefile.project
# !\brief Makefile for project specifics.
# !\author <author>
#
# --------------------------------------------------------------------
#             Copyright (c) 2026. <copyright holder>
#                     All rights reserved
# --------------------------------------------------------------------

#
# project identification
#
PROJECT ?= shocktest

BIN_NAME ?= $(PROJECT)
LIB_BASENAME ?= $(PROJECT)

#
# build configuration
#
BUILD_EXE ?= 1
BUILD_STATIC ?= 1
BUILD_SHARED ?= 0

# c++ version
CXX_STD ?= c++20
MODE ?= debug

#
# extensions
#
USER_CPPFLAGS +=
USER_CXXFLAGS +=
USER_LDFLAGS +=
USER_LDLIBS +=

include dep/makeshift/makeshift.mk
