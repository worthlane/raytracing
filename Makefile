CXX = g++

EXECUTABLE = vector

CXXFLAGS  = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts       \
			-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
			-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
			-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
			-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
			-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
			-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
			-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192         \
			-Wstack-usage=8192 -fPIE -Werror=vla -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

HOME = $(shell pwd)

SOURCE_DIR = src
CXXFLAGS  += -I $(HOME)/$(SOURCE_DIR)

BUILD_DIR   = build

DOXYFILE = Doxyfile
DOXYBUILD = doxygen $(DOXYFILE)

# ==============================================================
# 						 FILE GROUPS
# ==============================================================

SOURCES = main.cpp vectors.cpp visual.cpp coord_system.cpp objects.cpp pixels_array.cpp

OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# ==============================================================

.PHONY: all
all: $(EXECUTABLE)

# -------------------------------------------------------------------------------

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

# -------------------------------------------------------------------------------

.PHONY: clean makedirs

clean:
	rm -rf  $(EXECUTABLE) $(BUILD_DIR)/*.o

makedirs:
	mkdir -p $(BUILD_DIR)




