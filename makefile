CXX=g++
CXXFLAGS = -std=c++11 -g

all: raycaster_app

raycaster_app: main.o camera.o scene.o raycaster.o shape.o point.o vector.o color.o material.o lightsource.o triangle.o
	$(CXX) $(CXXFLAGS) main.o camera.o scene.o raycaster.o shape.o point.o vector.o color.o material.o lightsource.o triangle.o -o raytracer_app

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

raycaster.o: raycaster.cpp
	$(CXX) $(CXXFLAGS) -c raycaster.cpp -o raycaster.o

shape.o: shape.cpp
	$(CXX) $(CXXFLAGS) -c shape.cpp -o shape.o

point.o: point.cpp
	$(CXX) $(CXXFLAGS) -c point.cpp -o point.o

vector.o: vector.cpp
	$(CXX) $(CXXFLAGS) -c vector.cpp -o vector.o

color.o: color.cpp
	$(CXX) $(CXXFLAGS) -c color.cpp -o color.o

material.o: material.cpp
	$(CXX) $(CXXFLAGS) -c material.cpp -o material.o

lightsource.o: lightsource.cpp
	$(CXX) $(CXXFLAGS) -c lightsource.cpp -o lightsource.o

scene.o: scene.cpp
	$(CXX) $(CXXFLAGS) -c scene.cpp -o scene.o

camera.o: camera.cpp
	$(CXX) $(CXXFLAGS) -c camera.cpp -o camera.o

triangle.o: triangle.cpp
	$(CXX) $(CXXFLAGS) -c triangle.cpp -o triangle.o

clean:
	rm -f *.o *.ppm raytracer_app ./TestImages/*.ppm
