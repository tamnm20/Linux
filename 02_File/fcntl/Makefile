allw: buildw runw
allr: buildr runr

runw:
	@./write
runr:
	@./read

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