CXX      = $(shell fltk-config --cxx)
DEBUG    = -g
CXXFLAGS = $(shell fltk-config --use-gl --cxxflags ) -I.
LDFLAGS  = $(shell fltk-config --use-gl --ldflags )
LDSTATIC = $(shell fltk-config --use-gl --ldstaticflags )
LINK     = $(CXX)
 
TARGET = lab
OBJS = main.o window.o libmessage.o
SRCS = main.cxx window.cpp libmessage.cpp
 
.SUFFIXES: .o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

all: $(TARGET)
	gcc -DLANG_UA -c liblang.c -o liblang_ua.o -Wno-macro-redefined
	gcc -c liblang.c -o liblang_en.o -Wno-macro-redefined
	gcc -shared -o liblang_ua.so liblang_ua.o
	gcc -shared -o liblang_en.so liblang_en.o
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
main.o: main.cxx window.cpp libmessage.cpp

run: $(SRCS)
	./$(TARGET)

clean: $(TARGET) $(OBJS)
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null