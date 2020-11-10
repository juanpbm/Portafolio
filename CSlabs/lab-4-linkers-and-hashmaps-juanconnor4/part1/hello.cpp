// filename: hello.cpp
// // compile with: g++ -g -c hello.cpp
// // Investigate with:  objdump -t hello.o

int foo(int a, int b){
	return a+b;
}

int main(){

	foo(1,2);	

	return 0;
}
