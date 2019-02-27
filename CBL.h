#ifndef _CBL_H_
#define _CBL_H_
#include <stdexcept>
#include "List.h"

namespace cop3530
{
	template <typename E>
	class CBL: public List<E> 
	{
		public:
			CBL(void);
			CBL(size_t s);
			~CBL(void) override;
			void insert(E element, int position) override;
			void push_front(E element) override;//pushes element to front of list
			void push_back(E element) override;//pushes element to back of list
			void replace(E element, int position) override;
			void remove(int position) override; 
			E pop_front(void) override;// removes and returns element in front of list
			E pop_back(void) override;// removes and returns element in back of list
			E item_at(int position) override;
			E peek_front(void) override;//returns copy of first element
			E peek_back(void) override; //returns copy of element in back of list
			bool is_full(void) override;// list is always full
			bool is_empty(void) override;// true if deque is empty
			size_t length(void) override;// returns int type size_t for length of list
			size_t capacity(void);
			void clear(void) override; //clears list
			bool contains(E element) override;//returns true IFF at least one element in list matches argument
			void print(void) override;
			/*
			#ifdef DEBUG
				E* const contents_as_array() override; //returns pointer to array copy of list (DOES NOT REFERENCE TO DEQUEUE)
			#endif
			*/
		private:
    		size_t cap, size;
    		size_t head, tail;
    		E* data;
    		size_t next_index( int i);
    		size_t prev_index( int i);
    		E* get_new_size(size_t newSize);
    		E* resize_and_copy(E* oldArr, size_t newSize, int startPos);
    		E* resize_and_copy(E* oldArr, size_t newSize);
    		E* split_at_point(E* oldArr, int pos);
			
	};
//==============Constructor/Destructor===================
	template <typename E>
	CBL<E>::CBL( void )	//constructor sets tail points to same node as head
	:cap(50),size(0), head(0), tail(0), data (new E[cap+1])
	{
	}

	template <typename E>
	CBL<E>::CBL( size_t s)
	: cap (s),size(0), head(0), tail(0), data (new  E[cap+1] )	//overloaded constructor sets data to new empty list
	{
	}

	template <typename E>
	CBL<E>::~CBL( void )
	{		//destructor
		if(!is_empty())
			clear();
		delete data;
	}
//======================Operations=========================================
//------adding to list
	template <typename E>
	void CBL<E>::push_front(E element)
	{
		if(is_full()){
			data=resize_and_copy(data, 1.5*size, head+1);//resizes by 150% and returns pointer to new arr
			*(data+head)=element;
			return;
		}

		head=prev_index(head);
		*(data+head)=element;
		size++;
	}

	template <typename E>
	void CBL<E>::push_back(E element)
	{
		if(is_full())
			data=resize_and_copy(data,size*1.5,head); 
		*(data+tail)= element;		//set data at tail to element
		tail=next_index(tail);
		size++;
	}

	template <typename E>
	void CBL<E>::insert(E element, int position)//inserts element such that (item_at(position)==element)
	{
		if(position>tail)
			throw runtime_error("Index_Out_Of_Range: Cannot access index greater than length of List");
		*split_at_point(data, next_index(head+position-1))=element;
		tail=next_index(tail);
		size++;
	}

//-------replacing and removing-------------
	template <typename E>
	E CBL<E>::pop_front(void)
	{
		if(is_empty())
			throw std::runtime_error("CBL<E>.pop_front(): empty list");
		E item= *(data+head);
		head=next_index(head);
		size--;
		return item;
	}

	template <typename E>
	E CBL<E>::pop_back(void)//O(n) //decrements tail and pops
	{
		if(is_empty())
			throw std::runtime_error("CBL<E>.pop_front(): empty list");
		tail=prev_index(tail);
		return *(data+tail);
		size--;
	}

	template <typename E>next_index(position-1)
	void CBL<E>::remove(int position)//shifts all elements to the right of 'position' left by 1 and decrements tail
	{
		for(int i=position;i<tail;i++)
		{
			*(data+next_index(head+position-1))=*(data+next_index(head+position));
		}
		tail=prev_index(tail);
		size--;
	}

	template<typename E>
	void CBL<E>::replace(E element, int position)
	{
		*(data+next_index(head+position-1))=element;
	}

//---------searching the list-------
	template <typename E>
	E CBL<E>::item_at(int position)//O(1)
	{
		return *(data+next_index(head+position-1));
	}

	template <typename E>
	E CBL<E>::peek_front(void)//O(1)
	{
		return *(data+head);
	}

	template <typename E>
	E CBL<E>::peek_back(void)//O(1)
		return *(data+tail-1);
	}

//----------semantics----------
	template <typename E>
	bool CBL<E>::is_full(void)//tail is zero index so list is full when tail== capacity
	{
		return tail==prev_index(head);
	}

	template <typename E>
	bool CBL<E>::is_empty(void)
	{
		return tail==head;
	}

	template <typename E>
	size_t CBL<E>::length(void)//returns number of elements in list
	{
		return size;
	}

	template <typename E>
	size_t CBL<E>::capacity(void)//returns number of slots (empty or full) in list
	{
		return cap;
	}

	template <typename E>
	void CBL<E>::clear(void)
	{
		while(!is_empty())
			pop_back();
	}

	template <typename E>
	bool CBL<E>::contains(E element)//inserts element before element at current position, displacing element[position] one to the right
	{
		for(int i=0;i<tail;i++)
		{
			if(*(data+next_index(i-1))==element)
				return true;
		}
		return false;
	}

	template <typename E>
	void CBL<E>::print(void)
	{
		int i;
		std::cout<<"[ ";
		for(i=head;i<tail-1;i=next_index(i))
		{
				std::cout<<*(data+i)<<" , ";
		}

		std::cout<<*(data+i)<<" ]\n";
	}

//------------helper functions
	/*
	template<typename E>
	E* const CBL<E>::contents_as_array()
	{
		E arr[]=*new E[size];
		for(int i=0;i<size;++i)
		{
			arr[i]=*(data+i)
		}
		return &arr[0];
	}
	*/

   	template <typename E>
   	E* CBL<E>::get_new_size(size_t newSize)
   	{
   		cap=newSize;
   		E* arr[]=new E[cap];
   		return arr;
   	}


   	template <typename E>
   	E* CBL<E>::resize_and_copy(E* oldArr, size_t newSize, int startPos) //startPos represents how many index shifts to the right the new list is going to start at
   	{
   		size_t oldsize=cap;
   		cap=newSize;
   		E* arr[]= new E[cap];
   		for(int i=0;i<tail;++i)
   		{
   			*(arr+((startPos+i)%oldsize))=*(oldArr+next_index(i-1));
   		}
   		for(int j=0;j<startPos;j++)
   			tail=next_index(tail);
   		return arr;
   	}

	template <typename E>
   	E* CBL<E>::resize_and_copy(E* oldArr, size_t newSize)
   	{
   		return resize_and_copy(oldArr,newSize,head);
   	}

   	template<typename E>
   	E* CBL<E>::split_at_point(E* oldArr, int pos)//returns pointer to insertion point, splitting the list, and shifting elements after split to the right
   	{
   	 	E* split;
   	 	E* out_to;
   	 	if(is_full())
   	 		out_to= get_new_size(tail*1.5);
   	 	else
   	 		out_to=oldArr;
   	 	for(int i=0;i<pos;++i)
   	 	{
   	 		*(out_to+next_index(head+i-1))=*(data+next_index(head+i-1));
   	 	}
   	 	for(int i=pos+1;i<tail+1;++i)
   	 	{
   	 		*(out_to+next_index(head+i-1))=*(data+next_index(head+i-2));
   	 	}
   	 	delete data[];
   	 	data=out_to;
   	 	split=next_index(data+pos-1);
   	 	tail=next_index(tail);//increments tail ptr because the function is only called for inserts meaning tail would increase 1 after shift
   	 	return split;
   	}

   	template <typename E>
   	size_t* CBL<E>::next_index(size_t index)
   	{
   		return (index+1)%cap;
   	}

   	template <typename E>
   	size_t* CBL<E>::prev_index(size_t index)
   	{
   		if(head==0 && index==0)
   			return cap;
   		return (head+index-1)%cap;
   	}

}; 
#endif