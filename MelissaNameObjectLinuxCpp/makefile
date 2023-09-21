# Melissa Name Object Linux C++

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
LDLIBS = -lmdName
LDFLAGS = -L/home/emaiiii/MdLinuxExamples/NameObject-Cpp-Linux/MelissaNameObjectLinuxCpp/Build
RM = rm -f

OUT_DIR = Build

MelissaNameObjectLinuxCpp: Main.cpp NameObject.cpp mdName.h mdNameEnums.h | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) Main.cpp NameObject.cpp $(LDFLAGS) $(LDLIBS) -o $(OUT_DIR)/$@

clean:
	$(RM) *.o $(OUT_DIR)/MelissaNameObjectLinuxCpp

