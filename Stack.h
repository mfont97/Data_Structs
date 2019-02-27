#include <iostream>
#include <string>

using namespace std;

template <class T>
class Stack{
	

public: 
	Stack(){
		Stack(1);
	}
	Stack(int size){
       stkptr = new T[size];
       size= this.size;

	}	
	void push(T obj);
	T pop();
    T top();

private:
	T* stkptr;
	int size;
};

template <class T>
void Stack<T>:: push(T in){
	for (int i=size-1; i>-1;i--){
		if(stkptr+i){ //if position not null go back one
			continue;
		}
		else {	//if it is null add to top of stack
			*(stkptr+i)= in;
			return;
		}
		cout<<"stack is full"<<endl;

	}

}

template <class T>
T Stack<T>:: pop(){

	for(int i =0; i< size+1;i++){
		T objFree=*(stkptr+i);
		if (stkptr+i){
			delete *(stkptr+i);
			return objFree;
		}
		else
			continue;
	}

	cout<<"stack is empty"<<endl;
	return NULL;


}

template <class T>
T Stack<T>:: top(){

	for(int i =0; i< size+1;i++){
		if (stkptr+i){
			
			return *(stkptr+i);
		}
		else
			continue;
	}

	cout<<"stack is empty"<<endl;
	return NULL;


}



