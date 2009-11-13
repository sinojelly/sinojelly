# This is the base name of the project, used to produce the full name of the 
# application library "libBASENAME.a" and the test executable, "BASENAME" or 
# "BASENAME.exe"
PROJ_NAME = $(notdir $(shell pwd))
PROJ_BASE = Untouchable

SUP_NAME = Support-GTest-Cpp
SUP_BASE = Support

# --------------------------------------------------------------
# In a perfect world, nothing below this line should change.
# --------------------------------------------------------------

# --------------------------------------------------------------
# Determine constants passed to all files
# The untouchable project needs PROJ_BASE, SUP_BASE, and SUP_DIR

# Determine whether SUP_NAME is a sibling or a child dir.
ifeq ($(shell ls -1d $(SUP_NAME) 2>/dev/null),$(SUP_NAME))
	# Support is in child dir
	SUP_DIR=$(SUP_NAME)
else
	# Support (assumed) in sibling dir
	SUP_DIR=../$(SUP_NAME)
endif

# Determine whether UNT_NAME is a sibling or a child dir.
ifneq ($(UNT_BASE),)
ifeq ($(shell ls -1d $(UNT_NAME) 2>/dev/null),$(UNT_NAME))
	# Support is in child dir
	UNT_DIR=$(UNT_NAME)
else
	# Support (assumed) in sibling dir
	UNT_DIR=../$(UNT_NAME)
endif
endif
# Note extra level of directory for SUP_DIR and UNT_DIR
PASS_ON = PROJ_BASE=$(PROJ_BASE) SUP_DIR=../$(SUP_DIR) SUP_BASE=$(SUP_BASE) UNT_DIR=../$(UNT_DIR) UNT_BASE=$(UNT_BASE)


all:	support untouchable
	@$(MAKE) --no-print-directory -C build as-project $(PASS_ON)

support:
	@$(MAKE) --no-print-directory -C $(SUP_DIR)/build as-subproject PROJ_BASE=$(SUP_BASE)	

untouchable:
ifneq ($(UNT_BASE),)
	@$(MAKE) --no-print-directory -C $(UNT_DIR)/build as-subproject PROJ_BASE=$(UNT_BASE) SUP_DIR=../$(SUP_DIR) SUP_BASE=$(SUP_BASE)
endif
		
clean: 
	@$(MAKE) --no-print-directory -C build clean $(PASS_ON)
	@$(MAKE) --no-print-directory -C $(SUP_DIR)/build clean PROJ_BASE=$(SUP_BASE)
ifneq ($(UNT_BASE),)
	@$(MAKE) --no-print-directory -C $(UNT_DIR)/build clean PROJ_BASE=$(UNT_BASE)
endif
