#ifndef _CDAL_H_
#define _CDAL_H_
#include <stdexcept>
#include "List.h"

namespace cop3530
{
	template <typename E>
	class CDAL: public List<E> 
	{
		public:
			CDAL(void);
			CDAL(size_t s);
			~CDAL(void) override;
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
			void clear(void) override; //clears list
			bool contains(E element) override;//returns true IFF at least one element in list matches argument
			void print(void) override;
			/*#ifdef DEBUG
				E* const contents_as_array() override; //returns pointer to array copy of list (DOES NOT REFERENCE TO DEQUEUE)
			#endif*/
		private:
			struct Node{
				E* backing;
				Node * next;
			};
			
			size_t node_ct;
			size_t tail;
			Node * data;//pointer to first node in chain
			Node * make_new_node();//returns pointer to new node
			Node * create_list_of_size(size_t s);//makes chain of nodes
			void shift_right(int position);//shifts all values starting@position right once, increments tail
			void shift_node_right(Node * ptr, int shiftpos);//shifts elements in given node to the right from shiftpos
			void shift_node_right(Node * ptr);//when shiftpos==0
			void shift_left(int position);//shifts all units to the right of postion left 1, decrements tail
			void shift_node_left(Node * ptr, int shiftpos, E next_data);
			void shift_node_left(Node * ptr, E next_data);//when shiftpos==0
			E * go_to(int index);//returns pointer of a given index in the list
			Node* go_to_node(int index);//returns pointer to node where index is contained
			void resize();

	};
//==============Constructor/Destructor===================
	template <typename E>
	CDAL<E>::CDAL( void )	
	:data(make_new_node()),tail(0)//constructor sets head to point to new node and tail points to same node as head
	{
	}

	template <typename E>
	CDAL<E>::CDAL( size_t s)
	:data(create_list_of_size(s)),tail(0)	//overloaded constructor sets head to point to head of new empty list, (tail is set in create_list_of_size(s))
	{

	}

	template <typename E>
	CDAL<E>::~CDAL( void )
	{		//destructor
		clear();
		delete data;
	}
//======================Operations=========================================
//------adding to list
	template <typename E>
	void CDAL<E>::push_front(E element)
	{
		if(is_full()){//if full add a node to list
			resize();
			std::cout<<"list full: made new node\n";
		}
		shift_right(0);//shift elements from front of the CDAL on to the right once
		*(data->backing)=element;//set value at front of list to element	

	}

	template <typename E>
	void CDAL<E>::push_back(E element)
	{
		Node * ptr;
		if (is_full())//if full append new node to list for insertion
		{
			resize();
		}
		//just insert
		*(go_to(tail))=element;
		++tail;//increment tail
	}

	template <typename E>
	void CDAL<E>::insert(E element, int position)//inserts element before element at current position, displacing element[position] one to the right
	{
		if (is_full())//if full append new node to list for insertion
		{
			resize();
		}
		E* ptr=go_to(position);//get pointer to slot in CDAL
		shift_right(position);//shift everything from slot on to the right once
		*ptr=element;//set element at slot
	}

//-------replacing and removing-------------
	template <typename E>
	E CDAL<E>::pop_front(void)
	{
		E element= *(data->backing);
		shift_left(0);//shift elements into position and decrement tail
		return element;
	}

	template <typename E>
	E CDAL<E>::pop_back(void)//O(n)
	{
		E element= *(go_to(tail));
		--tail;//decrement tail
		return element;
	}

	template <typename E>
	void CDAL<E>::remove(int position)//inserts element before element at current position, displacing element[position] one to the right
	{
		shift_left(position);//shift left into position and decrement tail
	}

	template <typename E>
	void CDAL<E>::replace(E element, int position)
	{
		*(go_to(position))=element;
	}

//---------searching the list-------
	template <typename E>
	E CDAL<E>::item_at(int position)
	{
		return *(go_to(position)); //return value at position
	}

	template <typename E>
	E CDAL<E>::peek_front(void)//O(1)
	{
		return *(data->backing);//return value of first elements
	}

	template <typename E>
	E CDAL<E>::peek_back(void)
	{
		return *(go_to(tail-1));//returns value at last element
	}

//----------semantics----------
	template <typename E>
	bool CDAL<E>::is_full(void)
	{
		return ((tail%50==0)&&tail!=0); 
	}

	template <typename E>
	bool CDAL<E>::is_empty(void)
	{
		return tail==0;
	}

	template <typename E>
	size_t CDAL<E>::length(void)//inserts element before element at current position, displacing element[position] one to the right
	{
		return tail;
	}

	template <typename E>
	void CDAL<E>::clear(void)//possible memory leak CHECK BEFORE SUBMISSION 
	{
		tail=0;
		delete data;
		data=make_new_node();
	}

	template <typename E>
	bool CDAL<E>::contains(E element)//inserts element before element at current position, displacing element[position] one to the right
	{
		Node * ptr= data;
		while(ptr)
		{
			for(int i=0;i<50;++i)
			{
				if(*(ptr->backing+i)==element)
					return true;
			}
			ptr=ptr->next;
		}
		return false;
	}

	template <typename E>
	void CDAL<E>::print(void)
	{
		if(is_empty())
		{
			std::cout<<"[ ]\n";
			return;
		}
		std::cout<<"[ ";
		Node * ptr=data;
		int node_ind=0;
		while(ptr)
		{
			for(int i=0;i<50;++i)
			{
				if(node_ind*50+i==tail-1){
					std::cout<<*(ptr->backing+i)<<" ]\n";
					return;
				}
				std::cout<<*(ptr->backing+i)<<" , ";
			}
			ptr=ptr->next;
			node_ind++;
		}
	}

//------------helper functions
	template<typename E>
	typename CDAL<E>::Node * CDAL<E>::go_to_node(int position)// returns pointer to node at [position]
	{
		Node * ptr = data;
		int node_ind=(position/50);
		int node_ctr=0;
		while(node_ctr!=node_ind)
		{
			ptr=ptr->next;
			++node_ctr;
		}
		return ptr;
	}

	template<typename E>
	E* CDAL<E>::go_to(int position)// goes to that position
	{
		Node * ptr=go_to_node(position);
		E* desired_index= (ptr->backing+(position%50));
		return desired_index;
	}

	template<typename E>
	typename CDAL<E>::Node * CDAL<E>::make_new_node()
	{
		Node * ptr= new Node;
		ptr->next=nullptr;
		ptr->backing=new E[50];
		node_ct++;//increase node_ct upon creation because function is only used internally
		return ptr;
	}

	template <typename E>
	typename CDAL<E>::Node * CDAL<E>::create_list_of_size(size_t s)
	{
		if(s<49)
			return make_new_node();
		Node* headptr= make_new_node();
		Node* ptr=headptr;
	
		int node_count = 1;
		while((node_count*50)<s)
		{
			ptr->next=make_new_node();
			ptr=ptr->next;
			node_count++;
		}

		return headptr;
	}

	template <typename E>
	void CDAL<E>::shift_right(int position)//in place shift righ w/2 variables to hold edge values
	{
		if(is_empty()){
			tail++;
			return;
		}
		Node * ptr= go_to_node(position);
		int pos_in_list=position%50;
		//first case
	
		E last_element= *(ptr->backing+49);//set last_element to element at back 
		shift_node_right(ptr, pos_in_list); //shift elements after desired position 1 to the right										//go to next nodes which are all shifted from start of backing array
		while(ptr->next)//while ptr has a next node to go to
		{	
			ptr=ptr->next;// go to next
			E temp= *(ptr->backing+49);//store last element in temp variable
			std::cout<<"hey IM HERE\n";
			shift_node_right(ptr); //shift all elements 1 to the right
			*(ptr->backing)=last_element;//set 1st elemnt of current node to last element of prev node
			last_element=temp;//make last_element temp for next nodes shift
		}
		tail++;
	}

	template <typename E>
	void CDAL<E>::shift_node_right(Node * ptr, int shiftpos)
	{
			for(unsigned int i=49;i>shiftpos;i--)
			{
				*(ptr->backing+i)=*(ptr->backing+i-1);//set current index to one before it
			}
	}

	template <typename E>
	void CDAL<E>::shift_node_right(Node * ptr)
	{
			shift_node_right(ptr,0);
	}

	template <typename E>
	void CDAL<E>::shift_left(int position) //shifts all elements right of position left by 1 slot
	{
		int pos_in_list=position%50;
		//first node
		Node * ptr= go_to_node(position);
		shift_node_left(ptr, pos_in_list, *(ptr->next->backing));//shifts values 1 left from pos_in_list+1
		ptr=ptr->next;
		//rest of list
		while(ptr){
			if(!ptr->next)//case for last node 
			{
				for(int i=0;i<(tail%50);i++)
				{
				*(ptr->backing+i)= *(ptr->backing+i+1);//set current index to one after it
				}
				tail--;
				return;
			}
			shift_node_left(ptr, *(ptr->next->backing));//shifts values 1 from beginning of backing array
			ptr=ptr->next;
		}
	}

	template <typename E>
	void CDAL<E>::shift_node_left(Node * ptr, int shiftpos, E next_data)
	{		
			unsigned int i;
			for(i=shiftpos;i<49;i++)
			{
				*(ptr->backing+i)= *(ptr->backing+i+1);//set current index to one after it
			}
			*(ptr->backing+i)=next_data;//set tail of node to head of next node

	}

	template <typename E>
	void CDAL<E>::shift_node_left(Node * ptr,E next_data)
	{
			shift_node_left(ptr,0, next_data);
	}

	template <typename E>
	void CDAL<E>::resize()
	{
			(go_to_node(tail-1))->next=make_new_node();		
	}

	/*template <typename E>
	E& operator++(int position){
		Node * ptr= go_to_node(postion);
		return ptr->backing+(position%50);
	}

	template<typename E>
	E* const CDAL<E>::contents_as_array(){
		return ;
	}
	*/
};
#endif

