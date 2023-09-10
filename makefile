all:		*.h *.cpp
			g++ -g -Wall -std=c++11 -o main *.cpp

main:		*.h *.cpp
			g++ -g -Wall -std=c++11 -o main *.cpp

clean:		main
			rm main

run:		*.h *.cpp
			clear
			g++ -g -Wall -std=c++11 -o main *.cpp
			valgrind -s --leak-check=full ./main
ru:			*.h *.cpp
			clear
			g++ -g -Wall -std=c++11 -o main *.cpp
			valgrind -s --leak-check=full ./main
urn:		*.h *.cpp
			clear
			g++ -g -Wall -std=c++11 -o main *.cpp
			valgrind -s --leak-check=full ./main
rn:			*.h *.cpp
			clear
			g++ -g -Wall -std=c++11 -o main *.cpp
			valgrind -s --leak-check=full ./main
