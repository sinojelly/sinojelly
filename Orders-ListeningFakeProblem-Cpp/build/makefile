##################################################################################
# SHOULD NOT HAVE TO CHANGE BELOW HERE
##################################################################################
# The following variables are passed in
# PROJ_BASE = what to call everything, e.g. 'Untouchable'
# SUP_DIR = path to root of support library, e.g '../../Support-All-Cpp
# SUP_BASE = base name for support, e.g. 'Support'

# ROOT is the root dir of my sub-project, e.g. .../Support-All-Cpp
ROOT = ..
PROJ_NAME = $(dir $(shell pwd))

# LIB is the application code library .../Support-All-Cpp/lib/libSupport.a
LIB_DEST = $(ROOT)/lib
LIB_BASE = $(PROJ_BASE)
LIB_NAME = lib$(PROJ_BASE).a
LIB_FULL = $(LIB_DEST)/$(LIB_NAME)
LIB_SRC = $(ROOT)/src
# IMPORTANT:  Most projects have no include dir, but support and untouchable do
LIB_INC = $(ROOT)/src
LIB_HEADERS= $(wildcard $(LIB_INC)/*.h)
LIB_SOURCES = $(wildcard $(LIB_SRC)/*.cpp)

# EXE is the test executable, e.g. .../Support-All-Cpp/bin/SupportTests
EXE_DEST = $(ROOT)/bin
EXE_NAME = $(PROJ_BASE)Tests
EXE_FULL = $(EXE_DEST)/$(EXE_NAME)
EXE_SRC = $(ROOT)/test
EXE_INC = $(ROOT)/test
EXE_HEADERS = $(wildcard $(EXE_SRC)/*.h)
EXE_SOURCES = $(wildcard $(EXE_SRC)/*.cpp)

# SUP is the support library.  LIB depends on its headers, and EXE depends on its .lib
SUP_NAME = lib$(SUP_BASE).a
SUP_PATH = $(SUP_DIR)/lib
SUP_FULL = $(SUP_PATH)/$(SUP_NAME)
SUP_INC = $(SUP_DIR)/include
SUP_HEADERS = $(wildcard $(SUP_INC)/*.h)

# UNT is the support library.  LIB depends on its headers, and EXE depends on its .lib
UNT_NAME = lib$(UNT_BASE).a
UNT_PATH = $(UNT_DIR)/lib
UNT_FULL = $(UNT_PATH)/$(UNT_NAME)
UNT_INC = $(UNT_DIR)/include
UNT_HEADERS = $(wildcard $(UNT_INC)/*.h)

# INVOKE_LIB = how to invoke the library tool
ifeq ($(findstring Darwin, $(shell "uname")) , Darwin)
	INVOKE_LIB = libtool -o 
else
	INVOKE_LIB = ar -cr
endif

as-project: output $(EXE_FULL)

as-subproject: output $(LIB_FULL)

run-tests:	$(EXE_FULL)
	$(EXE_FULL)

$(EXE_FULL): $(LIB_FULL) $(EXE_SOURCES) $(EXE_HEADERS)
	g++ -g -I$(EXE_INC) -I$(LIB_INC) -I$(SUP_INC) $(if $(UNT_BASE),-I$(UNT_INC)) $(EXE_SOURCES) -L$(LIB_DEST) -l $(LIB_BASE) -L$(SUP_PATH) -l $(SUP_BASE) $(if $(UNT_BASE),-L$(UNT_PATH) -l $(UNT_BASE)) -o $(EXE_FULL)

$(LIB_FULL):	$(LIB_SOURCES) $(LIB_HEADERS) $(SUP_HEADERS) $(if $(UNT_BASE),$(UNT_HEADERS))
	g++ -g -Wno-deprecated-declarations -I$(SUP_INC) -I$(LIB_INC) $(if $(UNT_BASE),-I$(UNT_INC)) $(LIB_SOURCES) -c
	$(INVOKE_LIB) $(LIB_FULL) *.o
	
clean:	output
	rm -f $(EXE_DEST)/*.html *.html $(EXE_FULL) $(EXE_FULL).exe $(EXE_FULL).out.exe $(EXE_FULL).out $(LIB_FULL) *.o 2>/dev/null

output:
	@echo "----------------------------------------------------------------------------------"
	@echo "Making $(PROJ_NAME) [$(PROJ_BASE)] $(MAKECMDGOALS)"
	@echo "----------------------------------------------------------------------------------"

