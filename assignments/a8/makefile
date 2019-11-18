name ?= libstr.a
target ?= .
build:
	gcc -g -Wall -c -static source/*.c
	if ! [ -d $(target) ]; then mkdir $(target); fi
	$(AR) rv $(name) *.o
	if [ $(target) != . ]; then mv $(name) $(target); fi
	rm *.o
	echo "Successfully compiled without errors"
