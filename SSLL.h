#ifndef _SSLL_H_
#define _SSLL_H_
#include <stdexcept>
#include "List.h"

namespace cop3530
{
	template <typename E>
	class SSLL:public List<E> 
	{
		public:
			SSLL(void);
			~SSLL(void) override;
			void insert(E element, int position) override;// element will be at data[position]
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
			void clear(void) override; //clears list
			bool contains(E element) override;//returns true IFF at least one element in list matches argument
			void print(void) override;
			//#ifdef DEBUG
			//E* const contents_as_array() override; //returns pointer to array copy of list (DOES NOT REFERENCE TO DEQUEUE)
			//#endif
		private:
			struct Node{
				E value;
				Node* next=nullptr;
			}; 
			
			Node * go_to(size_t position);
			size_t size;
			Node * head;
			Node * tail;

		
		public:
			
			template <typename T>
			class SSLL_Iter
			{
					public:
  					// type aliases required for C++ iterator compatibility
  					using value_type=T;
  					using reference = T&;
 					using pointer = T*;
  					using difference_type = std::ptrdiff_t;
  					using iterator_category = std::forward_iterator_tag;
  					
  					// type aliases for prettier code
                    using self_type = SSLL_Iter;
  					using self_reference = SSLL_Iter&;
					
      
					private:
 					Node* here;
      
					public:
  					explicit SSLL_Iter( Node* start = nullptr ) : here( start ) {
  					}
  					SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) 
  					{}
 					reference operator*() const {//dereference operator
 						return here->value;
 					}
  					pointer operator->() const {
  						return here;
  					}
  					self_reference operator=( SSLL_Iter<E> const& src ) {
  						here=src;
  						return *this;
  					}
 					self_reference operator++() {
 						here=here->next;
 						return *this;
 					} // preincrement
 					self_type operator++(int) {
 						iterator copy=*this;
 						here=here->next;
 						return copy;
 					} // postincrement
  					bool operator==( SSLL_Iter<E> const& rhs ) const {
  						return (*this==rhs);
  					}
 					bool operator!=( SSLL_Iter<E> const& rhs) const {
 						return (*this!=rhs);
 					}

			};
			using value_type = E;
			using iterator = SSLL_Iter<E>;
			using const_iterator = SSLL_Iter<E const>;
			iterator begin(){
				return SSLL_Iter<value_type>(head->next);
			}
			//const_iterator begin(){
			//	return const SSLL_Iter(const head);
			//}
			iterator end(){
				return SSLL_Iter<value_type>(tail->next);
			}
			//const_iterator end(){
			//	return const SSLL_Iter(const tail);
			//}
			
	}; 
//==============Constructor/Destructor===================
	template <typename E>
	SSLL<E>::SSLL( void )	//constructor sets head to point to dummy node and tail points to same node as head
	: size(0),head(new Node), tail(head)
	{
	}

	template <typename E>
	SSLL<E>::~SSLL( void )
	{		//destructor
		if(!is_empty())
			clear();
		delete head;
		delete tail;
	}
//======================Operations=========================================
//------adding to list
	template <typename E>
	void SSLL<E>::push_front(E element)
	{
		head->value=element; //sets value at head to element
		Node* ptr= new Node;//get new node from pool to be new head
		ptr->next=head;//set dummy nodes next to current head now with value in it
		head=ptr;//set head of list to new dummy node taken from pool
		size++;//increment size
	}

	template <typename E>
	void SSLL<E>::push_back(E element)
	{	
		Node* ptr= new Node;
		ptr->value= element;
		tail->next=ptr;
		tail=ptr;
		size++;
	}

	template <typename E>
	void SSLL<E>::insert(E element, int position)//inserts element before element at current position, displacing element[position] one to the right
	{
		if(is_empty())
		{
			std::cout<<"List is empty: Setting element to head of list\n";
			push_front(element);
			return;
		}
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			std::cout<<"pos is "<<position<<"\n";
		}
		else if(position>=size)
		{
			std::cout<<"Index_Out_Of_Bounds: Pushing element to back of list\n";
			push_back(element);
			return;
		}
		

		Node * ptr=go_to(position);
		Node * to_insert=new Node;
		to_insert->value= element;
		to_insert->next=ptr->next;
		ptr->next= to_insert;
		size++;
	}

//-------replacing and removing-------------
	template <typename E>
	E SSLL<E>::pop_front(void)
	{
		E temp=head->value;
		head=head->next;
		size--;
		return temp;
	}

	template <typename E>
	E SSLL<E>::pop_back(void)//O(n)
	{
		E temp= tail->value;
		tail=go_to(size-1);
		size--;
		return temp;
	}

	template <typename E>
	void SSLL<E>::remove(int position)//inserts element before element at current position, displacing element[position] one to the right
	{
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			std::cout<<"pos is "<<position<<"\n";
		}else if(position==size-1){
			pop_back();
			return;
		}

		Node * ptr=go_to(position);
		ptr->next=ptr->next->next;
		size--;
	}

	template<typename E>
	void SSLL<E>::replace(E element, int position)
	{
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			std::cout<<"pos is "<<position<<"\n";
		}
		Node * ptr= go_to(position+1);
		ptr->value=element;

	}

//---------searching the list-------
	template <typename E>
	E SSLL<E>::item_at(int position)
	{
		if(size<position)
			throw std::runtime_error("PSLL<E>.item_at(): INDEX_OUT_OF_BOUNDS");

		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			std::cout<<"pos is "<<position<<"\n";
		}
		Node * ptr = go_to(position);
		return ptr->next->value;
	}

	template <typename E>
	E SSLL<E>::peek_front(void)//O(n)
	{
		return head->next->value;
	}

	template <typename E>
	E SSLL<E>::peek_back(void)//inserts element before element at current position, displacing element[position] one to the right
	{
		return tail->value;
	}

//----------semantics----------
	template <typename E>
	bool SSLL<E>::is_full(void){ //in SSLL you can always add an extra node
		return false;
	}

	template <typename E>
	bool SSLL<E>::is_empty(void)
	{
		return head==tail; //list will never be empty unless case when head has no value or head points to nothing
	}

	template <typename E>
	size_t SSLL<E>::length(void)//returns number of nodes in list
	{
		return size;
	}

	template <typename E>
	void SSLL<E>::clear(void)
	{
		while(!is_empty())
		{
				pop_front();
		}
	}

	template <typename E>
	bool SSLL<E>::contains(E element)//inserts element before element at current position, displacing element[position] one to the right
	{
		if(is_empty())
			return false;

		Node * ptr=head;
		while(ptr!=nullptr)
		{
			if (ptr->value==element)
				return true;
			ptr=ptr->next;
		}
		return false;
	}

	template <typename E>
	void SSLL<E>::print(void)
	{
		if(is_empty())
		{
			std::cout<<"[ ]\n";
			return;
		}
		Node * ptr=head->next;
		std::cout<<"[ ";
		while(ptr!=tail)
		{
			std::cout<<ptr->value<<" , ";
			ptr=ptr->next;
		}
		std::cout<<ptr->value<<" ]\n";
	
	}

//------------helper functions
	template<typename E>
	typename SSLL<E>::Node * SSLL<E>::go_to(size_t position)// returns pointer to node at [position-1]
	{
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			std::cout<<"pos is "<<position<<"\n";
		}
		Node * ptr=head->next;
		size_t node_index= 0;
		while(node_index<position-1)//breaks when node_index==postition-1
		{
			ptr=ptr->next;
			node_index++;
		}
		return ptr;
	}



	/*
	template<typename E>
	E* const SSLL<E>::contents_as_array()
	{
		E arr[size];
		E* const arr_ptr= &arr[0];
		Node* ptr=head; //ptr to head so as to not move actual head ptr
		int i=0;
		while(ptr!=NULL)	//ptr follows same path rules as head ie next_element(ptr) is populated while ptr is not
		{
			arr[i]=ptr->value;//set arr[i] to next element ie if head=0 1stElement=1
			ptr=ptr->next;//increment ptr and i
			i++;
		}

		return arr_ptr;
	} */
	

};
#endif

