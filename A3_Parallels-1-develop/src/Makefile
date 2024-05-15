# Compiler
CC 				= g++

# Compiler flags
CFLAGS 			= -Wextra -Wall -Werror
CPPFLAGS 		= -std=c++17
TESTFLAGS		= -lgtest -lgtest_main -lpthread
#TSANFLAGS		= -fsanitize=thread 

# Directories
SRCDIR 			= ContextMenu
LIBDIR 			= Libs
BUILDDIR 		= build
TESTDIR 		= Tests

# Source files
SRC_ACO 		= $(LIBDIR)/aco/Sources/s21_aco.cc \
          		  $(LIBDIR)/aco/Sources/s21_ant_algorithm_advanced.cc \
          		  $(LIBDIR)/aco/Sources/s21_ant_algorithm_default.cc \
          		  $(LIBDIR)/aco/Sources/s21_ant_algorithm_optimization.cc \

SRC_SLE 		= $(LIBDIR)/sle/Sources/s21_sle.cc \
				  $(LIBDIR)/sle/Sources/s21_gauss_advanced.cc \
				  $(LIBDIR)/sle/Sources/s21_gauss_default.cc \
				  $(LIBDIR)/sle/Sources/s21_gauss_optimization.cc
				  
SRC_WINOGRAD 	= $(LIBDIR)/winograd/Sources/s21_winograd.cc \
				  $(LIBDIR)/winograd/Sources/s21_winograd_default.cc \
				  $(LIBDIR)/winograd/Sources/s21_winograd_classic.cc \
				  $(LIBDIR)/winograd/Sources/s21_winograd_pipeline.cc \
				  $(LIBDIR)/winograd/Sources/s21_winograd_optimization.cc

SRC_MENU 		= $(SRCDIR)/main.cc \
           		  $(SRCDIR)/Sources/Parallels.cc \
				  $(SRCDIR)/Sources/Timer.cc \
				  $(SRCDIR)/Sources/AcoCommand.cc \
				  $(SRCDIR)/Sources/SleCommand.cc \
				  $(SRCDIR)/Sources/WinogradCommand.cc \
				  $(SRCDIR)/Sources/Command.cc

SRC_TEST 		= $(TESTDIR)/s21_test_aco.cc \
				  $(TESTDIR)/s21_test_sle.cc \
				  $(TESTDIR)/s21_test_winograd.cc \
			 	  $(TESTDIR)/s21_test_main.cc 

# Object files
OBJ_ACO 		= $(patsubst $(LIBDIR)/aco/%.cc,$(BUILDDIR)/%.o,$(SRC_ACO))
OBJ_SLE 		= $(patsubst $(LIBDIR)/sle/%.cc,$(BUILDDIR)/%.o,$(SRC_SLE))
OBJ_WINOGRAD 	= $(patsubst $(LIBDIR)/winograd/%.cc,$(BUILDDIR)/%.o,$(SRC_WINOGRAD))
OBJ_MENU 		= $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.o,$(SRC_MENU))

# Main executable
MAIN 			= $(BUILDDIR)/main

# Test executable
TEST 			= $(BUILDDIR)/test

# Targets
.PHONY: all clean run leaks

all: clean main run

# Main executable
main: $(OBJ_ACO) $(OBJ_SLE) $(OBJ_WINOGRAD) $(OBJ_MENU)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $(BUILDDIR)/$@

# Test executable
test: $(OBJ_ACO) $(OBJ_SLE) $(OBJ_WINOGRAD) $(SRC_TEST)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TSANFLAGS) $^ -o $(BUILDDIR)/$@ $(TESTFLAGS)
	CK_FORKS=no leaks -atExit -- $(BUILDDIR)/$@

# Object files for aco
$(BUILDDIR)/%.o: $(LIBDIR)/aco/%.cc
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Object files for sle
$(BUILDDIR)/%.o: $(LIBDIR)/sle/%.cc
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Object files for winograd
$(BUILDDIR)/%.o: $(LIBDIR)/winograd/%.cc
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Object files for menu
$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Run the main executable
run: main
	./$(BUILDDIR)/$^

clean:
	rm -rf $(BUILDDIR)