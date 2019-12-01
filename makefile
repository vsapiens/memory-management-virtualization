CXX = g++
CXXFLAGS = -g -Wall -std=c++17

manager: manager.o ProcessManager.o
	$(CXX) $(CXXFLAGS) -o manager manager.o ProcessManager.o

manager.o: manager.cc
	$(CXX) $(CXXFLAGS) -c manager.cc

ProcessManager.o: process_manager/ProcessManager.cc
	$(CXX) $(CXXFLAGS) -c process_manager/ProcessManager.cc