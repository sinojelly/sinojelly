# This is the base name of the project, used to produce the full name of the 
# application library "libBASENAME.a" and the test executable, "BASENAME" or 
# "BASENAME.exe"
PROJ_NAME = $(notdir $(shell pwd))
PROJ_BASE = Support

# --------------------------------------------------------------
# In a perfect world, nothing below this line should change.
# --------------------------------------------------------------

# --------------------------------------------------------------
# Determine constants passed to all files
# The support project needs only PROJ_BASE

PASS_ON = PROJ_BASE=$(PROJ_BASE)

all:
	@make --no-print-directory -C build as-project $(PASS_ON)

clean:
	@make --no-print-directory -C build clean $(PASS_ON)

