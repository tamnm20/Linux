all: cleana buildw runw buildr runr
allw: cleanw buildw runw
allr: buildr runr

runr:
	@./read
runw:
	@./write
	@cat file.txt 
buildw:
	gcc write.c -o write
buildr:
	gcc read.c -o read

cleanw:
	rm -rf write file.txt
cleanr:
	rm -rf read file.txt
cleana:
	rm -rf write read file.txt