CXXFLAGS := -std=c++11 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code \
-Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe \
-fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers \
-Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo \
-Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG \
-D_EJUDGE_CLIENT_SIDE 

CPPOBJ := ./main.o  


stack.exe: $(CPPOBJ)
	g++ $(CXXFLAGS) $(CPPOBJ) -o ./stack.exe

./main.o: ./main.cpp
	g++ $(CXXFLAGS) -c  ./main.cpp -o ./main.o
	
stack: $(CPPOBJ)
	g++ $(CXXFLAGS) $(CPPOBJ) -o ./stack

clean:
	rm -rf ./*.o ./*.exe




