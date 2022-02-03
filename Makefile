INCS = cmdline.h catch.h expr.h

OBJS = main.o cmdline.o num.o add.o mult.o var.o #tests.o

CXXFLAGS = --std=c++14 -O2

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)
	
main.o: main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

cmdline.o: cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

num.o: num.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

add.o: add.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

mult.o: mult.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

var.o: var.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

# tests.o: tests.cpp $(INCS)
#	$(CXX) $(CXXFLAGS) -c $<
