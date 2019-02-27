#ifndef _BOUNDED_DEQUEUE_H_
#define _BOUNDED_DEQUEUE_H_
#include <stdexcept>
#include "Dequeue.h"

namespace cop3530
{
	template <typename E>
	class Bounded_Dequeue: public Dequeue<E> 
	{
		public:
			Bounded_Dequeue(size_t  s);
			~Bounded_Dequeue() override;
			void push_front(E element) override;//pushes element to front of dequeue
			void push_back(E element) override;//pushes element to back of dequeue
			E pop_front(void) override;// removes and returns element in front of dequeue
			E pop_back(void) override;// removes and returns element in back of dequeue
			E peek_front(void) override;// returns copy of first element
			E peek_back(void) override;// returns copy of last element
			bool is_empty(void) override;// true if deque is empty 
			bool is_full(void) override;// true if deque is full
	    	size_t length(void) override;// returns int type size_t for length of dequeue
        	void clear(void) override; //clears dequeue
        	#ifdef DEBUG
        		E* const contents_as_array() override;
        	#endif
    	private:
    		size_t size;
    		E* const data;
    		size_t head=0;
    		size_t tail=1;
    		size_t next_index( size_t i);
    		size_t prev_index( size_t i);
	};
//=======================Constructors/ Destructors===================================
	template <typename E>
	Bounded_Dequeue<E>::Bounded_Dequeue( size_t s)	//constructor
	: size (s), data (new  E[s+1] )
	{
	}

	template <typename E>
	Bounded_Dequeue<E>:: ~Bounded_Dequeue()
	{		//destructor
		delete [] data;
	}
//======================Operations=========================================
//------the pushes
	template <typename E>
	void Bounded_Dequeue<E>::push_front(E element)
	{
		if( is_full())
			throw std::runtime_error("Bounded_Dequeue<E>.push_front(): full dequeue");
		data[head]= element;		//set data at head to element
		head = prev_index(head);	//decrement head pointer
	}//pushes element to front of dequeue
	template <typename E>	
	void Bounded_Dequeue<E>::push_back(E element)
	{
		if( is_full())
			throw std::runtime_error("Bounded_Dequeue<E>.push_back(): full dequeue");
		data [tail] = element;
		tail = next_index( tail );
	}//pushes element to back of dequeue
//-------the pops
	template <typename E>
	E Bounded_Dequeue<E>::pop_front ( void )
	{
		if(is_empty()){
			std::cout<<"im empty bro\n";
			throw std::runtime_error("Bounded_Dequeue<E>.pop_front(): empty dequeue");
		}
		head =next_index(head); 
		size_t item=head;
		return data[item]; //since pointer to head is changed, data[item] will never be accessed unless it's overwritten
	}//pops and returns element from front of dequeue
	template <typename E>	
	E Bounded_Dequeue<E>::pop_back()
	{
		if(is_empty())
			throw std::runtime_error("Bounded_Dequeue<E>.pop_back(): empty dequeue");
		tail =prev_index(tail);
		size_t item = tail;
		return data[item]; //since pointer to tail is changed, data[item] will never be accessed unless it's overwritten
	}//pops and returns element from back of dequeue 
//---------the peeks
	template <typename E>
	E Bounded_Dequeue<E>::peek_front( void )
	{
		if(is_empty())
			throw std::runtime_error("Bounded_Dequeue<E>.peek_front(): empty dequeue");

		E item = data[next_index(head)];
		return item;
	}//returns copy of element in front of dequeue	
	template <typename E>	
	E Bounded_Dequeue<E>::peek_back( void )
	{
		if(is_empty())
			throw std::runtime_error("Bounded_Dequeue<E>.peek_back(): empty dequeue");

		E item = data[prev_index(tail)];
		return item;
	}//returns copy of element in back if dequeue
//--------the semantics
	template <typename E>
	size_t Bounded_Dequeue<E>::length( void )
	{
		if(is_full())
			return size;
		else if( head <= tail)
			return (tail - head)-1;
		else if (head > tail)
			return (tail+(size-head));
	}//returns length of current deque
	template <typename E>	
	bool Bounded_Dequeue<E>::is_full( void )
	{
		if(head==tail)
			return true;
		else 
			return false;
	}//checks if dequeue is full
	template <typename E>	
	bool Bounded_Dequeue<E>::is_empty( void )
	{
		return tail==next_index(head);
	}//checks if dequeue is empty

	template <typename E>	
	void Bounded_Dequeue<E>::clear( void )
	{
		while(!is_empty())
			pop_back();
	}//pops elements until dequeue is empty;
	template <typename E>	
	E* const Bounded_Dequeue<E>::contents_as_array( void )
	{
		E arr[size];
		size_t ptr=head; //ptr to head so as to not move actual head ptr
		int i=0;
		while(ptr!=tail)	//ptr follows same path rules as head ie next_element(ptr) is populated while ptr is not
		{
			arr[i]=data[next_index(ptr)];//set arr[i] to next element ie if head=0 1stElement=1
			ptr=next_index(ptr);//increment ptr and i
			i++;
		}
	}//
//-----------------------Helper functions
	template <typename E>
	size_t Bounded_Dequeue<E>::next_index( size_t i)
	{
		if (i==size||i==-1)
			return 0;
		else
			return i+1;
	}
    template <typename E>
    size_t  Bounded_Dequeue<E>::prev_index( size_t i)
    {
    	if(i==0)
    		return size;
    	else
    		return i-1;
    }
}//closes namespace
#endif