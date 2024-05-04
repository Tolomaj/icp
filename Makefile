.PHONY: all doxygen clean pack run

EXECUTABLE=icp24-robot-sim
PACKAGE_NAME=xgross13-xfolty21.zip

all:
	cd src/ && qmake && make
	cp src/main $(EXECUTABLE)
	cp -a src/img img

doxygen:
	doxygen Doxyfile

clean:
	$(MAKE) clean -C src/
	rm -f $(EXECUTABLE)
	rm -rf doc/html
	rm -rf img
	rm -f $(PACKAGE_NAME)

pack:
	zip -r $(PACKAGE_NAME) \
		Makefile \
		Doxyfile \
		README.txt \
		diagrams.pdf \
		assets/ \
		src/data/ \
		src/gui/ \
		src/img/ \
		src/link/ \
		src/sim/ \
		src/main.cpp \
		src/main.pro \
		src/README.md \
		examples/ \
		doc/doxygen-awesome-css/120 \
		doc/doxygen-awesome-css/LICENSE \
		doc/doxygen-awesome-css/README.md \
		doc/doxygen-awesome-css/doxygen-awesome-darkmode-toggle.js \
		doc/doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js \
		doc/doxygen-awesome-css/doxygen-awesome-interactive-toc.js \
		doc/doxygen-awesome-css/doxygen-awesome-paragraph-link.js \
		doc/doxygen-awesome-css/doxygen-awesome-sidebar-only-darkmode-toggle.css \
		doc/doxygen-awesome-css/doxygen-awesome-sidebar-only.css \
		doc/doxygen-awesome-css/doxygen-awesome-tabs.js \
		doc/doxygen-awesome-css/doxygen-awesome.css \
		doc/doxygen-awesome-css/logo.drawio.svg


run: all doxygen