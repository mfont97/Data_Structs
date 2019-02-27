#ifndef _SDAL_H_
#define _SDAL_H_
#include <stdexcept>
#include "List.h"

namespace cop3530
{
	template <typename E>
	class SDAL: public List<E> 
	{
		public:
			SDAL(void);
			SDAL(size_t s);
			~SDAL(void) override;
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
    		size_t cap;
    		size_t tail;
    		E* data;
    		E* get_new_size(size_t newSize);
    		E* resize_and_copy(E* oldArr, size_t newSize, int startPos);
    		E* resize_and_copy(E* oldArr, size_t newSize);
    		E* split_at_point(E* oldArr, int pos);
			
	};
//==============Constructor/Destructor===================
	template <typename E>
	SDAL<E>::SDAL( void )	//constructor sets tail points to same node as head
	:cap(50), tail(0), data(new E[cap])
	{
	}

	template <typename E>
	SDAL<E>::SDAL( size_t s)
	: cap (s), tail(0), data(new  E[cap] )	//overloaded constructor sets data to new empty list
	{
	}

	template <typename E>
	SDAL<E>::~SDAL( void )
	{		//destructor
		if(!is_empty())
			clear();
		delete data;
	}
//======================Operations=========================================
//------adding to list
	template <typename E>
	void SDAL<E>::push_front(E element)
	{
		if(is_full()){
			data=resize_and_copy(data, 1.5*tail, 1);//resizes by 150% and returns pointer to &(new arr[0])
			*data=element;
			return;
		}

		*split_at_point(data, 0)=element;//shifts all elements to right when position==0
	}

	template <typename E>
	void SDAL<E>::push_back(E element)
	{
		if(is_full())
			data=resize_and_copy(data,tail*1.5); //no 3rd parameter indicates no shift because insertion is at tail
		data[tail]= element;		//set data at tail to element
		tail++;
	}

	template <typename E>
	void SDAL<E>::insert(E element, int position)//inserts element such that (item_at(position)==element)
	{
		if(position<0)//if negative index start from back 
		{
			position=tail+(position%(int)tail)+1;//+1 to match -ith element is ith element from the tail of list
			
		}
		if(position>tail)
			push_back(element);
		*split_at_point(data, position)=element;
	}

//-------replacing and removing-------------
	template <typename E>
	E SDAL<E>::pop_front(void)
	{
		if(is_empty())
			throw std::runtime_error("SDAL<E>.pop_front(): empty list");
		E item= *data;
		for(int i=0; i<tail; ++i)
		{
			*(data+i)=*(data+i+1);
		}
		tail--;
		return item;
	}

	template <typename E>
	E SDAL<E>::pop_back(void)//O(n) //decrements tail and pops
	{
		if(is_empty())
			throw std::runtime_error("SDAL<E>.pop_front(): empty list");
		tail--;
		return *(data+tail);
	}

	template <typename E>
	void SDAL<E>::remove(int position)//shifts all elements to the right of 'position' left by 1 and decrements tail
	{
		if(position<0)//if negative index start from back 
		{
			position=tail+(position%(int)tail);//-1 to match -ith element is ith element from the tail of list
			
		}
		for(int i=position;i<tail;i++)
		{
			E temp=*(data+i);
			*(data+i)=*(data+i+1);
			*(data+i+1)=temp;
		}
		tail--;
	}

	template<typename E>
	void SDAL<E>::replace(E element, int position)
	{
		if(position<0)//if negative index start from back 
		{
			position=tail+(position%(int)tail);//-1 to match -ith element is ith element from the tail of list
		}
		*(data+position)=element;
	}

//---------searching the list-------
	template <typename E>
	E SDAL<E>::item_at(int position)//O(1)
	{
		if(position<0)//if negative index start from back 
		{
			position=tail+(position%(int)tail);//-1 to match -ith element is ith element from the tail of list
			
		}
		return *(data+position);
	}

	template <typename E>
	E SDAL<E>::peek_front(void)//O(1)
	{
		return *data;
	}

	template <typename E>
	E SDAL<E>::peek_back(void){//O(1)
		E item=*(data+tail-1);
		return item;
	}

//----------semantics----------
	template <typename E>
	bool SDAL<E>::is_full(void)//tail is zero index so list is full when tail== capacity
	{
		return (tail==cap);
	}

	template <typename E>
	bool SDAL<E>::is_empty(void)
	{
		return tail==0;
	}

	template <typename E>
	size_t SDAL<E>::length(void)//returns number of elements in list
	{
		return tail;
	}

	template <typename E>
	size_t SDAL<E>::capacity(void)//returns number of slots (empty or full) in list
	{
		return cap;
	}

	template <typename E>
	void SDAL<E>::clear(void)
	{
		tail=0;
	}

	template <typename E>
	bool SDAL<E>::contains(E element)//inserts element before element at current position, displacing element[position] one to the right
	{
		for(int i=0;i<tail;i++)
		{
			if(*(data+i)==element)
				return true;
		}
		return false;
	}

	template <typename E>
	void SDAL<E>::print(void)
	{
		if(!tail){
			std::cout<<"[ ]\n";
			return;
		}
		int i;
		std::cout<<"[ ";
		for(i=0;i<tail-1;i++)
		{
				std::cout<<*(data+i)<<" , ";
		}

		std::cout<<*(data+i)<<" ]\n";
	}

//------------helper functions
	/*
	template<typename E>
	E* const SDAL<E>::contents_as_array()
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
   	E* SDAL<E>::get_new_size(size_t newSize)
   	{
   		cap=newSize;
   		E* arr=new E[cap];
   		return arr;
   	}


   	template <typename E>
   	E* SDAL<E>::resize_and_copy(E* oldArr, size_t newSize, int startPos) //startPos represents how many index shifts to the right the new list is going to start at
   	{
   		cap=newSize;
   		E* arr= new E[cap];
   		for(int i=0;i<tail;++i)
   		{
   			*(arr+startPos+i)=*(oldArr+i);
   		}
   		tail=tail+startPos;
   		return arr;
   	}

	template <typename E>
   	E* SDAL<E>::resize_and_copy(E* oldArr, size_t newSize)
   	{
   		E* ans=resize_and_copy(oldArr,newSize,0);
   		return ans;
   	}

   	template<typename E>
   	E* SDAL<E>::split_at_point(E* oldArr, int pos)//returns pointer to insertion point, splitting the list, and shifting elements after split to the right
   	{
   	 	E* split;
   	 	E* out_to= get_new_size(tail*1.5);
   	 	for(int i=0;i<pos;++i)
   	 	{
   	 		*(out_to+i)=*(data+i);
   	 	}
   	 	for(int i=pos+1;i<tail+1;++i)
   	 	{
   	 		*(out_to+i)=*(data+i-1);
   	 	}
   	 	data=out_to;
   	 	split=data+pos;
   	 	tail++;//increments tail ptr because the function is only called for inserts meaning tail would increase 1 after shift
   	 	return split;

   	}

}; 
#endif