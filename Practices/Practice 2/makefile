all: estandar

run: estandar
	./gsh media.bmp	

no_optimizado: source.cpp
	g++ -Wall -O0 source.cpp -o gsh

estandar: source.cpp
	g++ -Wall -O1 source.cpp -o gsh

optimizado: source.cpp
	g++ -Wall -O3 source.cpp -o gsh

clean :
	rm gsh *shadow_*

