CPP = g++
CPPFLAGS = -std=c++11
CPPSRC = Main.cpp Graph.cpp FileParsing.cpp DijiktraFun.cpp
CPPTARGET = iscas

$(CPPTARGET): $(CPPSRC)
	$(CPP) $(CPPFLAGS) $^ -o $@


clean:
	rm -f $(CPPTARGET)
