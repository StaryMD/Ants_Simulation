runme:
	mkdir -p build
	c++ src/Source.cpp -I include -lsfml-system -lsfml-window -lsfml-graphics -Ofast -o build/runme

map_buidler1:
	mkdir -p build
	c++ src/map_builder1.cpp -o build/map_builder1

map_buidler2:
	mkdir -p build
	c++ src/map_builder2.cpp -o build/map_builder2

clean:
	rm -rf build
