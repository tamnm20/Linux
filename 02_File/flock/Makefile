all: cleana buildA runA buildB runB
allA: cleanA buildA runA
allB: cleanB buildB runB

runA:
	@./process_A
runB:
	@./process_B 
buildA:
	gcc process_A.c -o process_A
buildB:
	gcc process_B.c -o process_B

cleanA:
	rm -rf process_A text.txt
cleanB:
	rm -rf process_B file.txt
cleana: cleanA cleanB