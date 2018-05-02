
all:
	cd src/ && make
	cd src/ && make

doxygen:
	doxygen Doxyfile

pack:
	zip -r xknazi00-xlovis03-70-30 src Makefile Doxyfile README.txt examples

clean:
	rm ./src/*.o
	rm ./src/moc_mainwindow.cpp
	rm ./src/moc_predefs.h
	rm blockeditor
	rm ./src/BlockEditorQt.pro.user
	rm -r doc

run:
	./blockeditor
