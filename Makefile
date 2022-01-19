INCS = cmdline.h catch.h expr.h

OBJS = main.o cmdline.o expr.o

CXXFLAGS = --std=c++14 -O2

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)
	
main.o: main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

cmdline.o: cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

expr.o: expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<
