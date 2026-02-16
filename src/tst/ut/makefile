#
# makefile for shocktest unit tests
#

# Keep compatibility with callers that invoke "make all".
all: tests

# ------------------------------
# SUT targets (none yet)
# ------------------------------
# X86CPPTARGETSOL += name_SUT.cpp.so
# name_SUT.cpp.so,SRCS := $(ROOT_DIR)/src/lib/name.cpp
# name_SUT.cpp.so,DEPS :=
# name_SUT.cpp.so,CPPFLAGS := $(GLOBAL_CPPFLAGS)

# ------------------------------
# Test targets
# ------------------------------
X86CPPTARGET += TEST_SHOCKTEST_BEHAVIOR_UT
TEST_SHOCKTEST_BEHAVIOR_UT,SRCS := test_shocktest_behavior.cpp
TEST_SHOCKTEST_BEHAVIOR_UT,USRLIBS :=
TEST_SHOCKTEST_BEHAVIOR_UT,CPPFLAGS = $(GLOBAL_CPPFLAGS)
TEST_SHOCKTEST_BEHAVIOR_UT,LDFLAGS :=

X86CPPTARGET += TEST_SHOCKMOCK_UT
TEST_SHOCKMOCK_UT,SRCS := test_shockmock.cpp
TEST_SHOCKMOCK_UT,USRLIBS :=
TEST_SHOCKMOCK_UT,CPPFLAGS = $(GLOBAL_CPPFLAGS)
TEST_SHOCKMOCK_UT,LDFLAGS :=

X86CPPTARGET += TEST_CUSTOM_MAIN_UT
TEST_CUSTOM_MAIN_UT,SRCS := test_custom_main.cpp
TEST_CUSTOM_MAIN_UT,USRLIBS :=
TEST_CUSTOM_MAIN_UT,CPPFLAGS = $(GLOBAL_CPPFLAGS)
TEST_CUSTOM_MAIN_UT,LDFLAGS :=

# include shocktest makefile
include makefile.shocktest.mk
