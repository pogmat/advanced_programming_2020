CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic
SOURCE = linked_list.cpp
TARGET = linked_list.x

.PHONY : all
all: $(TARGET)

$(TARGET) : $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY : run
run : all
	@./$(TARGET)
