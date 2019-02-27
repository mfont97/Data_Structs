#ifndef _Tree_H_
#define _Tree_H_
//ADT List

namespace cop3530{

	template <typename E>
	class Tree{
		public:
		 	virtual void pre_order_traverse(Node * in, void f ( E&) )=0;
		 	virtual void in_order_traverse(Node * in, void f ( E&) )=0;
		 	virtual void post_order_traverse(Node * in, void f ( E&) )=0;
		 	virtual void Morris_preorder(Node * in, void f ( E&) )=0;
		 	virtual void Morris_inorder(Node * in, void f ( E&) )=0;
		 	virtual void insert(E data, size_t depth)=0;//inserts at a given depth
		 	virtual void append_as_leaf(E data, size_t depth)=0;
		 	virtual void clear(void)=0; //sets tree back to single empty node
			virtual bool contains(E element)=0;//seatches tree for value
			virtual void print(Node * in)=0; //prints element at a given node
			virtual size_t number_of_nodes(Node * head)=0; //counts number of nodes
			virtual size_t depth(Node * head)=0;


		private:
			struct Node{
				E element;
				Node *[] children;
			}
	};
	
			#ifdef DEBUG
				virtual E* const contents_as_stack()=0; //returns pointer to stack copy of tree
			#endif

			virtual ~Tree() {}; //Destructor
}
#endif