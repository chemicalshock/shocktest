# -------------------------------------------------------------
# Unit Test Build System (for src/tst/ut)
# -------------------------------------------------------------
# Builds all SUTs and test binaries into ./bld/
# Usage: make, make tests, make run, make clean
# -------------------------------------------------------------

.DEFAULT_GOAL := tests
ROOT_DIR := $(abspath ../../..)
BUILD_DIR := $(CURDIR)/bld

# Compiler config
CXX ?= g++
GLOBAL_CPPFLAGS := -I$(ROOT_DIR)/src/inc -I$(ROOT_DIR)/dep
CXXFLAGS := -std=c++20 -Wall -Wextra -Wno-unknown-pragmas
LDFLAGS :=

# ==============================
#  SUT Definitions
# ==============================
X86CPPTARGETSOL ?=
#
# Example SUT definition
#
# X86CPPTARGETSOL += name_SUT.cpp.so
# name_SUT.cpp.so,SRCS := $(ROOT_DIR)/src/lib/name.cpp
# name_SUT.cpp.so,DEPS := 
# name_SUT.cpp.so,CPPFLAGS := $(GLOBAL_CPPFLAGS)

# ==============================
#  Test Definitions
# ==============================
X86CPPTARGET ?=
#
# Example test definition
#
# X86CPPTARGET += TEST_NAME
# TEST_NAME,SRCS := test_name.cpp
# TEST_NAME,USRLIBS := name_SUT.cpp.so
# TEST_NAME,CPPFLAGS := $(GLOBAL_CPPFLAGS)
# TEST_NAME,LDFLAGS :=

# ==============================

#           #
# MAKESHIFT #
#           #

# ==============================
#  Helpers
# ==============================

# Resolve transitive DEPS recursively
define resolve_deps
$(if $($1,DEPS),\
  $(strip $(foreach d,$($1,DEPS),$(call resolve_deps,$(d)) $(d))),\
)
endef


# ==============================
#  Rules
# ==============================

# Macro to generate SUT target definitions from a pair "module,flags".
#define MAKE_TARGET_SOL
#  $(info Something: $(1))
#  $(eval module := $(strip $(word 1,$(subst ,, ,$(1)))))
#  $(eval flags := $(strip $(word 2,$(subst ,, ,$(1)))))
#  $(info Module: $(module), Flags: $(flags))
#  X86CPPTARGETSOL += $(module)_SUT.cpp.so
#  $(module)_SUT.cpp.so,SRCS := $(ROOT_DIR)/src/lib/$(module).cpp
#  $(module)_SUT.cpp.so,CPPFLAGS := $(flags)
#endef

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# --- SUT Rule Generator ---
define MAKE_SUT_TARGET
$(BUILD_DIR)/$(1): $$($(1),SRCS) $$(addprefix $(BUILD_DIR)/,$$($(1),USRLIBS)) | $(BUILD_DIR)
	@echo "[SUT] Compiling: $(BUILD_DIR)/$(1)"
	$$(CXX) $(CXXFLAGS) $$($(1),CPPFLAGS) -c -o $$@ $$^
endef

# --- Test Rule Generator ---
#define MAKE_TEST_TARGET
#$(BUILD_DIR)/$(1): $$($(1),SRCS) $$(addprefix $(BUILD_DIR)/,$$($(1),USRLIBS)) | $(BUILD_DIR)
#	@echo "[TEST] Compiling: $(BUILD_DIR)/$(1)"
#	$$(CXX) $(CXXFLAGS) $$($(1),CPPFLAGS) -o $$@ $$^ $$($(1),LDFLAGS) $(LDFLAGS)
#endef

define MAKE_TEST_TARGET
$(BUILD_DIR)/$(1): $$($(1),SRCS) \
$$(foreach d,$$(sort $$(strip \
  $$(foreach l,$$($(1),USRLIBS),$$(call resolve_deps,$$l) $$l)\
)),$$(BUILD_DIR)/$$d) | $(BUILD_DIR)
	@echo "[TEST] Compiling: $(BUILD_DIR)/$(1)"
	$$(CXX) $(CXXFLAGS) $$($(1),CPPFLAGS) -o $$@ $$^ $$($(1),LDFLAGS) $(LDFLAGS)
endef




# --- Apply Rules ---
#$(foreach tgt,$(SUT_GEN),$(eval $(call MAKE_TARGET_SOL,$(tgt))))
$(foreach tgt,$(X86CPPTARGETSOL),$(eval $(call MAKE_SUT_TARGET,$(tgt))))
$(foreach tgt,$(X86CPPTARGET),$(eval $(call MAKE_TEST_TARGET,$(tgt))))

# ==============================
#  Targets
# ==============================

debugdeps:
	@echo "Resolved dependencies per test target:"
	@$(foreach t,$(X86CPPTARGET), \
		echo ""; \
		printf "\033[1mTest: $(t)\033[0m\n"; \
		$(foreach lib,$($(t),USRLIBS), \
			printf "→ %s\n" "$(lib)"; \
			$(foreach d,$(call resolve_deps,$(lib)),printf "   \033[90m└── %s\033[0m\n" "$(d)";) \
		) \
	)

explain:
	@t="$(filter-out explain,$(MAKECMDGOALS))"; \
	if [ -z "$$t" ]; then \
		echo "Usage: make explain TEST_NAME"; exit 1; \
	fi; \
	echo "Resolved USRLIBS + transitive DEPS for $$t:"; \
	$(foreach lib,$($(filter-out explain,$(MAKECMDGOALS)),USRLIBS), \
		printf "→ %s\n" "$(lib)"; \
		$(foreach d,$(call resolve_deps,$(lib)),printf "   \033[90m└── %s\033[0m\n" "$(d)";) \
	)

testlist:
	@echo "Available test targets:"
	@$(foreach t,$(X86CPPTARGET), echo "• $(t)";)	

tests: $(BUILD_DIR) \
  $(foreach t,$(X86CPPTARGETSOL),$(BUILD_DIR)/$t) \
  $(foreach t,$(X86CPPTARGET),$(BUILD_DIR)/$t)

run:
	@if [ "$(filter-out run,$(MAKECMDGOALS))" != "" ]; then \
		testname="$(filter-out run,$(MAKECMDGOALS))"; \
		bin="$(BUILD_DIR)/$$testname"; \
		if [ -x "$$bin" ]; then \
			echo "→ Running $$bin"; \
			"$$bin" || exit 1; \
		else \
			echo "No such test or not executable: $$bin"; \
			exit 1; \
		fi; \
	else \
		echo "Running all unit tests..."; \
		for f in $(X86CPPTARGET); do \
			bin="$(BUILD_DIR)/$$f"; \
			if [ -x "$$bin" ]; then \
				echo "→ Running $$bin"; \
				"$$bin" || exit 1; \
			else \
				echo "Skipping missing or non-executable $$bin"; \
			fi; \
		done \
	fi

graphdeps:
	@t="$(filter-out graphdeps,$(MAKECMDGOALS))"; \
	if [ -z "$$t" ]; then \
		echo "Usage: make graphdeps TEST_NAME"; exit 1; \
	fi; \
	echo "digraph G {" > deps.dot; \
	echo "  node [shape=box];" >> deps.dot; \
	$(foreach lib,$($(filter-out graphdeps,$(MAKECMDGOALS)),USRLIBS), \
		echo "  \"$$t\" -> \"$(lib)\";" >> deps.dot; \
		$(foreach d,$(call resolve_deps,$(lib)), \
			echo "  \"$(lib)\" -> \"$(d)\";" >> deps.dot;) \
	) \
	echo "}" >> deps.dot; \
	echo "deps.dot written. Convert with: dot -Tpng deps.dot -o deps.png"

viewdeps:
	@t="$(filter-out viewdeps,$(MAKECMDGOALS))"; \
	if [ -z "$$t" ]; then \
		echo "Usage: make viewdeps TEST_NAME"; exit 1; \
	fi; \
	echo "digraph G {" > deps.dot; \
	echo "  node [shape=box];" >> deps.dot; \
	$(foreach lib,$($(filter-out viewdeps,$(MAKECMDGOALS)),USRLIBS), \
		echo "  \"$$t\" -> \"$(lib)\";" >> deps.dot; \
		$(foreach d,$(call resolve_deps,$(lib)), \
			echo "  \"$(lib)\" -> \"$(d)\";" >> deps.dot;) \
	) \
	echo "}" >> deps.dot; \
	dot -Tpng deps.dot -o deps.png && echo "deps.png written"; \
	( command -v xdg-open >/dev/null && xdg-open deps.png ) || echo "Use 'dot -Tpng deps.dot -o deps.png'"


clean:
	@echo Cleaning unit test build output...
	@mkdir -p "$(BUILD_DIR)"
	@find "$(BUILD_DIR)" -mindepth 1 -maxdepth 1 ! -name '.gitignore' -exec rm -rf {} +
	@touch "$(BUILD_DIR)/.gitignore"

.PHONY: tests run clean

%::
	@:
