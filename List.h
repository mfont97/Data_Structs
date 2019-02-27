#ifndef _LIST_H_
#define _LIST_H_
//ADT List

namespace cop3530{

	template <typename E>
	class List{
		public:
			virtual void insert(E element, int position)=0;
			virtual void push_front(E element)=0;//pushes element to front of dequeue
			virtual void push_back(E element)=0;//pushes element to back of dequeue.
			virtual void replace(E element, int position)=0;
			virtual void remove(int position)=0; 
			virtual E pop_front(void)=0;// removes and returns element in front of dequeue
			virtual E pop_back(void)=0;// removes and returns element in back of dequeue
			virtual E item_at(int position)=0;
			virtual E peek_front(void)=0;//returns copy of first element
			virtual E peek_back(void)=0; //returns copy of element in back of dequeue
			virtual bool is_full(void)=0;// true if deque is full
			virtual bool is_empty(void)=0;// true if deque is empty
			virtual size_t length(void)=0;// returns int type size_t for length of dequeue
			virtual void clear(void)=0; //clears dequeu
			virtual bool contains(E element)=0;//returns true IFF at least one element in list matches argument
			virtual void print()=0;
			


			#ifdef DEBUG
				virtual E* const contents_as_array()=0; //returns pointer to array copy of dequeue (DOES NOT REFERENCE TO DEQUEUE)
			#endif

			virtual ~List() {}; //Destructor




	};
	

}
#endif