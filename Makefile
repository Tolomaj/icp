.PHONY: all doxygen clean pack run

all:
	cd src/ && qmake
	$(MAKE) -C src/
	cp src/main ipc24-robot-sim
	cp -a src/img img

doxygen:
	doxygen Doxyfile

clean:
	$(MAKE) clean -C src/
	rm -f ipc24-robot-sim
	rm -rf doc/html
	rm -rf img
	rm -f solution.zip

pack:
	zip -r solution.zip . -x "*.git*" "*doc/html*" "*src/main*"

run: all doxygen