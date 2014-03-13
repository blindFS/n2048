all:
	g++ -O2 *.cpp -lncurses -o n2048
clean:
	rm -f *.o n2048 gmon.out
