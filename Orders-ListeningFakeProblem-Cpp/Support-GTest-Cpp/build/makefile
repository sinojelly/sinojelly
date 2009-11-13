##################################################################################
# SHOULD NOT HAVE TO CHANGE BELOW HERE
##################################################################################
# The following variables are passed in
# PROJ_BASE = what to call everything, e.g. 'Support'
PROJ_NAME = $(dir $(shell pwd))

# ROOT is the root dir of my sub-project, e.g. .../Support-All-Cpp
ROOT = ..

# LIB is the application code library .../Support-All-Cpp/lib/libSupport.a
LIB_DEST = $(ROOT)/lib
LIB_BASE = $(PROJ_BASE)
LIB_NAME = lib$(PROJ_BASE).a
LIB_FULL = $(LIB_DEST)/$(LIB_NAME)
LIB_SRC = $(ROOT)/src
# IMPORTANT:  Most projects have no include dir, but support and untouchable do
LIB_INC = $(ROOT)/include
LIB_HEADERS= $(wildcard $(LIB_INC)/*.h)
LIB_SOURCES = $(wildcard $(LIB_SRC)/*.cpp) $(wildcard $(LIB_SRC)/*.cc)

# EXE is the test executable, e.g. .../Support-All-Cpp/bin/SupportTests
EXE_DEST = $(ROOT)/bin
EXE_NAME = $(PROJ_BASE)Tests
EXE_FULL = $(EXE_DEST)/$(EXE_NAME)
EXE_SRC = $(ROOT)/test
EXE_INC = $(ROOT)/test
EXE_HEADERS = $(wildcard $(EXE_SRC)/*.h)
EXE_SOURCES = $(wildcard $(EXE_SRC)/*.cpp) $(wildcard $(EXE_SRC)/*.cc)

# INVOKE_LIB = how to invoke the library tool
ifeq ($(findstring Darwin, $(shell "uname")) , Darwin)
	INVOKE_LIB = libtool -o 
else
	INVOKE_LIB = ar -cr
endif

as-project: output run-tests

as-subproject: output $(LIB_FULL)

run-tests:	$(EXE_FULL)
	$(EXE_FULL)

$(EXE_FULL): $(LIB_FULL) $(EXE_SOURCES) $(EXE_HEADERS)
	g++ -g -I$(EXE_INC) -I$(LIB_INC) $(EXE_SOURCES) -L$(LIB_DEST) -l $(LIB_BASE) -o $(EXE_FULL)

$(LIB_FULL):	$(LIB_SOURCES) $(LIB_HEADERS)
	g++ -g -Wno-deprecated-declarations -I$(LIB_INC) $(LIB_SOURCES) -c
	$(INVOKE_LIB) $(LIB_FULL) *.o
	
clean:	output
	rm -f $(EXE_DEST)/*.html *.html $(EXE_FULL) $(EXE_FULL).exe $(EXE_FULL).out.exe $(EXE_FULL).out $(LIB_FULL) *.o 2>/dev/null
	
output:
	@echo "----------------------------------------------------------------------------------"
	@echo "Making $(PROJ_NAME) [$(PROJ_BASE)] $(MAKECMDGOALS)"
	@echo "----------------------------------------------------------------------------------"

	