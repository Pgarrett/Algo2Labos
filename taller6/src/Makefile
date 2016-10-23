CXXFLAGS = -g -Wall

SOURCES = test_dhc.cpp
HEADERS = DiccHashCerrado.hpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = test

$(TARGET): $(OBJS) $(HEADERS)  
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
