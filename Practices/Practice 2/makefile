all: estandar

run: estandar
	./difuminador media.bmp	

no_optimizado: source.cpp
	g++ -Wall -O0 source.cpp -o difuminador

estandar: source.cpp
	g++ -Wall -O1 source.cpp -o difuminador

optimizado: source.cpp
	g++ -Wall -O3 source.cpp -o difuminador

clean :
	rm difuminador *shadow_*

