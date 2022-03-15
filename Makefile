INCS = cmdline.h catch.h expr.h parse.h

OBJS = cmdline.o expr.o parse.o

CXXFLAGS = --std=c++14 -O2

msdscript: $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS) main.o

test_msdscript: $(OBJS) test_msdscript.o exec.o
	$(CXX) $(CXXFLAGS) -o test_msdscript $(OBJS) test_msdscript.o exec.o
	
main.o: main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

cmdline.o: cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

expr.o: expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

parse.o: parse.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<

#test_msdscript.o: test_msdscript.cpp $(INCS)
#	$(CXX) $(CXXFLAGS) -c $<

exec.o: exec.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<
