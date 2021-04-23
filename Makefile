a: main.cpp myStack_i127p615.hpp myQueue_i127p615.hpp
	g++ -std=c++11 myStack_i127p615.hpp
	g++ -std=c++11 myQueue_i127p615.hpp
	g++ -std=c++11 main.cpp
	./a.out inputs/instance10.txt output_stack.txt output_queue.txt

clean:
	rm *.gch output_queue.txt output_stack.txt a.out
