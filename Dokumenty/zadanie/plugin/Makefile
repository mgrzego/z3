__start__: obj ../libs/Interp4Fly.so ../libs/Interp4Turn.so ../libs/Interp4Rotate.so ../libs/Interp4ReadScene.so ../libs/Interp4Pause.so
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++11 -Iinc -I../inc
LDFLAGS=-Wall -shared

../libs/Interp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/Interp4Rotate.so obj/Interp4Rotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo

../libs/Interp4Turn.so: obj/Interp4Turn.o
	g++ ${LDFLAGS} -o ../libs/Interp4Turn.so obj/Interp4Turn.o
	@echo
	@echo "  Wtyczka dla polecenia 'Turn' zostala utworzona."
	@echo

../libs/Interp4ReadScene.so: obj/Interp4ReadScene.o
	g++ ${LDFLAGS} -o ../libs/Interp4ReadScene.so obj/Interp4ReadScene.o
	@echo
	@echo "  Wtyczka dla polecenia 'ReadScene' zostala utworzona."
	@echo

../libs/Interp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/Interp4Pause.so obj/Interp4Pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo

../libs/Interp4Fly.so: obj/Interp4Fly.o
	g++ ${LDFLAGS} -o ../libs/Interp4Fly.so obj/Interp4Fly.o
	@echo
	@echo "  Wtyczka dla polecenia 'Fly' zostala utworzona."
	@echo

obj/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh ../inc/Visualization.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp


obj/Interp4Turn.o: src/Interp4Turn.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Turn.hh ../inc/Visualization.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Turn.o src/Interp4Turn.cpp

obj/Interp4ReadScene.o: src/Interp4ReadScene.cpp ../inc/Interp4Command.hh\
                        inc/Interp4ReadScene.hh ../inc/Visualization.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4ReadScene.o src/Interp4ReadScene.cpp

obj/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh ../inc/Visualization.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp

obj/Interp4Fly.o: src/Interp4Fly.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Fly.hh ../inc/Visualization.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Fly.o src/Interp4Fly.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
