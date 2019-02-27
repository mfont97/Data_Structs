#ifndef _PSLL_H_
#define _PSLL_H_
#include <stdexcept>
#include "List.h"

namespace cop3530
{
	template <typename E>
	class PSLL: public List<E> 
	{
		public:
			PSLL(void);
			PSLL(size_t s);
			~PSLL(void) override;
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
			#endif
			*/
		private:
			struct Node{
				E value;
				Node * next= nullptr;
			}; 
			size_t size, free_size;
			Node * head, *tail, *free;
			Node * create_list_of_size(size_t s);	//returns pointer to new head of new list of size s
			Node * go_to(size_t position);			//goes to node right before positions such that go_to(s)->next=position
			Node * new_node(void);					//gets new node from pool
			void resize();
			void add_to_pool(Node * recycle);		//resets Node value and adds to pool of free nodes, adjusts size counters for both lists
			size_t const MAX_SIZE = 50;
			
	};
//==============Constructor/Destructor===================
	template <typename E>
	PSLL<E>::PSLL(void)	//size of list 0  (initialized on pushes)
	: size(0), free_size(0), head(new_node()), tail(head)
	{
	}

	template <typename E>
	PSLL<E>::PSLL(size_t s)	//head is dummy node initializes pool of free nodes as size of list
	: size(0), head(new Node),tail(head), free_size(s), free(create_list_of_size(free_size))
	{
	}

	template <typename E>
	PSLL<E>:: ~PSLL(void)
	{		//destructor
		if(!is_empty())
			clear();
		delete head;
		delete tail;
		delete free;
	}
//======================Operations=========================================
//------adding to list
	template <typename E>
	void PSLL<E>::push_front(E element)	// get node from pool of free nodes and push to front
	{
		
		resize();//handles size>100&&free_size>size/2		
		head->value=element; //sets value at head to element
		Node* ptr= new_node();//get new node from pool to be new head
		ptr->next=head;//set dummy nodes next to current head now with value in it
		head=ptr;//set head of list to new dummy node taken from pool
		size++;//increment size
	
	}

	template <typename E>
	void PSLL<E>::push_back(E element) //change to get node from pool of free nodes
	{
		resize();//handles size>100&&free_size>size/2	
		Node* ptr= new_node();
		ptr->value= element;
		tail->next=ptr;
		tail=ptr;
		size++;
	}

	template <typename E>							//change to get node from pool of free nodes
	void PSLL<E>::insert(E element, int position)//inserts element before element at current position, displacing element[position] one to the right
	{
		resize();//handles size>100&&free_size>size/2	
		if(is_empty())
		{
			std::cout<<"List is empty: Setting element to head of list\n";
			push_front(element);
			return;
		}
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size)+1;//-1 to match -ith element is ith element from the tail of list
			
		}
		if(position>=size)
		{
			std::cout<<"Index_Out_Of_Bounds: Pushing element to back of list\n";
			push_back(element);
			return;
		}
		Node * ptr=go_to(position);
		Node * to_insert=new_node();
		to_insert->value= element;
		to_insert->next=ptr->next;
		ptr->next= to_insert;
		size++;
	}

//-------replacing and removing-------------
	template <typename E>
	E PSLL<E>::pop_front(void)//change to add popped node to free node pool
	{
		if(!size){
			throw std::runtime_error("PSLL<E>.pop_front(): list is empty");
		}

		E temp=head->next->value;//set temp to value of 1st element
		Node * ptr= head->next->next;//keep ptr to new head
		add_to_pool(head->next);
		head->next=ptr;
		size--;
		return temp;
	}

	template <typename E>
	E PSLL<E>::pop_back(void)//change to add popped node to free node pool
	{
		if(!size)
			throw std::runtime_error("PSLL<E>.pop_back(): list is empty");
		E temp= tail->value;
		add_to_pool(tail);
		tail=go_to(size-1);
		size--;
		return temp;
	}

	template <typename E>
	void PSLL<E>::remove(int position)////change to add popped node to free node pool
	{

		if(!size)
			throw std::runtime_error("PSLL<E>.remove(): list is empty");
		else if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			
		}else if(size<position)
			throw std::runtime_error("PSLL<E>.remove(): INDEX_OUT_OF_BOUNDS -1");
		else if(position==size-1){
			pop_back();
			return;
		}

		Node * ptr=go_to(position);
		Node * temp=ptr->next->next;
		add_to_pool(ptr->next);
		ptr->next=temp;
		size--;
	}

	template<typename E>
	void PSLL<E>::replace(E element, int position)
	{
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			
		}
		Node * ptr= go_to(position+1);

	}

//---------searching the list-------//stays the same as PSLL
	template <typename E>
	E PSLL<E>::item_at(int position)
	{
		if(position>(int)size)
			throw std::runtime_error("PSLL<E>.item_at(): INDEX_OUT_OF_BOUNDS -1");
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			
		}
		Node * ptr = go_to(position);
		return ptr->next->value;
	}

	template <typename E>
	E PSLL<E>::peek_front(void)//O(n)
	{
		if(!size)
			throw std::runtime_error("PSLL<E>.peek_front(): list is empty");
		return head->next->value;
	}

	template <typename E>
	E PSLL<E>::peek_back(void)//inserts element before element at current position, displacing element[position] one to the right
	{
		if(!size)
			throw std::runtime_error("PSLL<E>.peek_back(): list is empty");
		return tail->value;
	}

//----------semantics----------
	template <typename E>
	bool PSLL<E>::is_full(void)//if free_list empty list is full
	{
		if(!free_size&&size>0)
			return true;
		else 
			return false;
	}

	template <typename E>
	bool PSLL<E>::is_empty(void)//if size==0 list is empty 
	{
		return size==0;
	}

	template <typename E>
	size_t PSLL<E>::length(void)//should be fine check if needs updating
	{
		return size;
	}

	template <typename E>
	void PSLL<E>::clear(void)//send all cleared nodes to pool
	{
		while(head!=tail)
		{
			pop_back();
		}
	}

	template <typename E>
	bool PSLL<E>::contains(E element)//stays the same
	{
		Node * ptr=head->next;
		while(ptr!=nullptr)
		{
			if (ptr->value==element)
				return true;
			ptr=ptr->next;
		}
		return false;
	}

	template <typename E>
	void PSLL<E>::print(void)//stays the same
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
	typename PSLL<E>::Node * PSLL<E>::go_to(size_t position)// returns pointer to node at [position-1]
	{
		if(position<0)//if negative index start from back 
		{
			position=size+(position%(int)size);//-1 to match -ith element is ith element from the tail of list
			
		}
		if(position==0)
			return head;
		Node * ptr=head->next;
		size_t node_ind=0;
		while(node_ind!=position-1)//stops at before position because nodes have no prev* (useful for appending)
		{
			ptr=ptr->next;
			node_ind++;
		}
		return ptr;
	}

	template<typename E>
	typename PSLL<E>::Node * PSLL<E>::new_node(void)//returns ptr to new node taken from pool and decrements free_size
	{
		
		if(free_size==0)
			return new Node;
		Node * ptr = free;
		if(free->next!=nullptr)
			free=free->next;
		free_size--;
		std::cout<<"done\n";
		return ptr;

	}

	template<typename E>
	typename PSLL<E>::Node * PSLL<E>::create_list_of_size(size_t s)// creates empty list of size s and returns pointer to head of list (from memory)
	{
		Node * ptr= new Node;
		Node * temp= ptr;//temp is head of new node
		int sz=1;
		while(size != s)
		{
			ptr->next=new Node;
			ptr=ptr->next;
			sz++;
		}
		return temp;
	}

	template<typename E>
	void PSLL<E>::add_to_pool(Node * recycle) //adds node to pool and updates ONLY free_size counter
	{
		if(free_size==MAX_SIZE)//if pool is at size of 50 delete node
		{
			delete recycle;
			return;
		}///else add to front of pool and incrememnt pool size
		recycle->value=0;
		recycle->next=free;
		free=recycle;
		free_size++;
	}

	template<typename E>
	void PSLL<E>::resize()
	{
		while(free_size>MAX_SIZE)
		{
			free=free->next;
			free_size--;
		}

		return;
	}
/*
	template<typename E>
	E* const PSLL<E>::contents_as_array(void) //returns contents as array for debuging
	{
		E arr[size];
		E * arr_ptr=&arr[0];
		Node* ptr=head; //ptr to head so as to not move actual head ptr
		int i=0;
		while(ptr!=NULL)	//ptr follows same path rules as head ie next_element(ptr) is populated while ptr is not
		{
			arr[i]=ptr->value;//set arr[i] to next element ie if head=0 1stElement=1
			ptr=ptr->next;//increment ptr and i
		}
		return arr_ptr;
	}
*/
};
#endif

