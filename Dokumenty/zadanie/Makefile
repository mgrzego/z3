__start__: obj interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj

__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++11 -Iinc
LDFLAGS=-Wall

interp: obj/main.o obj/PluginManager.o obj/GnuplotVisualizer.o obj/lacze_do_gnuplota.o obj/Wektor3D.o obj/scene.o obj/Cuboid.o obj/xmlparser4scene.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/PluginManager.o obj/GnuplotVisualizer.o obj/lacze_do_gnuplota.o obj/Wektor3D.o obj/scene.o obj/xmlparser4scene.o obj/Cuboid.o -ldl  -lxerces-c -lreadline

obj/main.o: src/main.cpp inc/PluginManager.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/PluginManager.o: src/PluginManager.cpp inc/PluginManager.hh inc/Interp4Command.hh inc/GnuplotVisualizer.hh inc/Plugin.hh
	g++ -c ${CPPFLAGS} -o obj/PluginManager.o src/PluginManager.cpp

obj/GnuplotVisualizer.o: src/GnuplotVisualizer.cpp inc/GnuplotVisualizer.hh\
                         inc/GnuplotVisualizer.hh inc/Wektor3D.hh inc/scene.hh inc/xmlparser4scene.hh
	g++  -c ${CPPFLAGS} -o obj/GnuplotVisualizer.o src/GnuplotVisualizer.cpp

obj/scene.o: src/scene.cpp inc/scene.hh inc/Cuboid.hh 
	g++ -c ${CPPFLAGS} -o obj/scene.o src/scene.cpp

obj/xmlparser4scene.o: src/xmlparser4scene.cpp inc/xmlparser4scene.hh inc/scene.hh
	g++ -c ${CPPFLAGS} -o obj/xmlparser4scene.o src/xmlparser4scene.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CPPFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Cuboid.o: src/Cuboid.cpp inc/Cuboid.hh inc/Wektor3D.hh
	g++ -c ${CPPFLAGS} -o obj/Cuboid.o src/Cuboid.cpp

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh
	g++ -c ${CPPFLAGS} -o obj/Wektor3D.o src/Wektor3D.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
