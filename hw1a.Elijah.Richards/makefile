CXX=g++
CXXFLAGS = -std=c++11 -g

all: raycaster_app

raycaster_app: main.o raycaster.o shape.o point.o vector.o color.o
	$(CXX) $(CXXFLAGS) main.o raycaster.o shape.o point.o vector.o color.o -o raycaster_app.out

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

raycaster.o: raycaster.cpp
	$(CXX) $(CXXFLAGS) -c raycaster.cpp -o raycaster.o

shape.o: main.cpp
	$(CXX) $(CXXFLAGS) -c shape.cpp -o shape.o

point.o: main.cpp
	$(CXX) $(CXXFLAGS) -c point.cpp -o point.o

vector.o: main.cpp
	$(CXX) $(CXXFLAGS) -c vector.cpp -o vector.o

color.o: main.cpp
	$(CXX) $(CXXFLAGS) -c color.cpp -o color.o

clean:
	rm -f *.o *.ppm raycaster_app.out
