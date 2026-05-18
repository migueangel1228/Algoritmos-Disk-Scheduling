# Makefile for Disk Scheduling Simulator

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
LDFLAGS =

# Source, object, and executable files
SRCDIR = src
OBJDIR = obj
BINDIR = .
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/disk_scheduler

# Default target
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to run the program with a default initial head position
run: all
	./$(EXECUTABLE) 2500

# Target to clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE) data/*.csv

# Target to display help
help:
	@echo "Available targets:"
	@echo "  make all     - Compiles the project"
	@echo "  make run     - Compiles and runs the project with initial head position 2500"
	@echo "  make clean   - Removes compiled files and generated data"
	@echo "  make help    - Shows this help message"

# Phony targets
.PHONY: all run clean help
