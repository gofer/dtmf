SRCS=dtmf.cc sound.cc device.cc main.cc
OBJS=$(addsuffix .o,$(basename $(SRCS)))

CXX=g++
CXXFLAGS+=-std=c++1y -Wall -O3 -I.
LD=g++
LDFLAGS+=-L.
LD_POST_LIB=-lwinmm

.PHONY: all clean distclean
.SUFFIXES: .cc .cpp .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LD_POST_LIB)

.cc.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.o

distclean:
	make clean && rm -f $(TARGET)* && rm -f Makefile
