#####################################################
# You may need to change the parameters under here. #
#####################################################

# Step 1: Choose a compiler. By default, use clang++

# If you use clang++, make sure the following line does not start with a comment (#)
CXX=clang++
# If you use g++, uncomment the following line
#CXX=g++

# Set default compiler parameters
# -Wall 	shows all warnings when compiling, always use this!
# -std=c++11 	enables the C++14 standard mode
CXXFLAGS = -Wall -std=c++14

# Step 2: If you use clang++ under Mac OS X, remove these comments
#CXXFLAGS += -stdlib=libc++
#LFLAGS += -stdlib=libc++

# Step 3: Run 'make' in the same directory as this file


############################
# Settings for the library #
############################


# Compiler flag -Idir specifies, that there are includes in the 'dir' directory
LIB_CXXFLAGS = $(CXXFLAGS) -Iinclude

# List of objects for the library
LIBOBJS = obj/main.o obj/hashcalculator.o obj/singlecrack.o obj/multicrack.o obj/password_score.o obj/permutations.o

# Name of the library
LIBRARY = lib/libhashcracker.a

################################
# Settings for the testing app #
################################

# Compiler flags for the testing app
APP_CXXFLAGS = $(CXXFLAGS) -Iinclude

# Linker flags (order the compiler to link with our library)
LFLAGS += -Llib -lhashcracker

# The object for the testing app
TESTOBJS = obj/hashcrackertest.o

# The name of the testing app
TESTAPP = bin/hashcrackertest

# This is the first target. It will be built when you run 'make' or 'make build'
build: $(LIBRARY)

# Create the library by using 'ar'
$(LIBRARY) : $(LIBOBJS)
	ar cr $(LIBRARY) $(LIBOBJS)

# Compile each source file of the librar
obj/main.o: src/main.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/singlecrack.o: src/singlecrack.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/singlecrack.cpp -o obj/singlecrack.o

obj/multicrack.o: src/multicrack.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/multicrack.cpp -o obj/multicrack.o

obj/password_score.o: src/password_score.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/password_score.cpp -o obj/password_score.o

obj/hashcalculator.o: src/hashcalculator.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/hashcalculator.cpp -o obj/hashcalculator.o

obj/permutations.o: src/permutations.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/permutations.cpp -o obj/permutations.o




# Rule for linking the test app with our library
$(TESTAPP): $(TESTOBJS) $(LIBRARY)
	$(CXX) $(TESTOBJS) -o $(TESTAPP) $(LFLAGS) 

# Compile each source file of the library
obj/hashcrackertest.o: tests/hashcrackertest.cpp
	$(CXX) $(APP_CXXFLAGS) -c tests/hashcrackertest.cpp -o obj/hashcrackertest.o


test: $(TESTAPP)
	./$(TESTAPP)

doc:
	doxygen

clean:
	rm -f $(LIBOBJS)
	rm -f $(TESTOBJS)
	rm -f $(LIBRARY)
	rm -f $(TESTAPP)
	rm -f output


output: $(LIBOBJS)
	g++ $(LIBOBJS) -o output
