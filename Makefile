# @Author: Brandon Wolenetz
# @Date:   15-Oct-2020
# @Project: Elite Dangerous Telemetry System V1
# @Filename: Makefile
# @Last modified by:   Brandon Wolenetz
# @Last modified time: 15-Oct-2020

CXX = g++
PROJSETTINGS = -std=c++11 -I./lib/include -L./lib/lib -lTrmGraphics
MAINFILE = main
OBJFILES = jsoncpp.o EDStatusReader.o

compile: main.o $(OBJFILES)
	$(CXX) $(MAINFILE).o $(OBJFILES) -o output $(PROJSETTINGS)

main.o: $(MAINFILE).cpp
	$(CXX) -c $(MAINFILE).cpp $(PROJSETTINGS)

jsoncpp.o: jsoncpp.cpp
	$(CXX) -c jsoncpp.cpp $(PROJSETTINGS)

EDStatusReader.o: EDStatusReader.cpp
	$(CXX) -c EDStatusReader.cpp $(PROJSETTINGS)

run:
	output $(ARGS)

clean:
	del *.o output
