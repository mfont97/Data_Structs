#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdexcept>
#include "Tree.h"

namespace cop3530
{
	template <typename E>
	class Binary_Tree: public Tree<E> 
	{	
	public:
		Binary_Tree(void);//make empty tree with only head node
		Binary_Tree(E data_at_head); // sets head node to value at intitilization
		Binary_Tree(size_t num_nodes); //makes empty binary tree of n nodes
		~Binary_Tree(void);
		void pre_order_traverse(Node * in, void f ( E&) )override; //recursively traverse in preorder
		void in_order_traverse(Node * in, void f ( E&) )override;	//recursively traverse in in_order
		void post_order_traverse(Node * in, void f ( E&) )override; //recursive post order
		void Morris_preorder(Node * in, void f ( E&) )override;
		void Morris_inorder(Node * in, void f ( E&) )override;
		void insert(E data, size_t depth)override;//inserts at a given depth
		void append_as_leaf(E data)override; //appends as first available leaf at depth
		void clear(void)override; //sets tree back to single empty node
		bool contains(E element)override;//seatches tree for value
		void print(Node * in)override; //prints element at a given node
		size_t number_of_nodes(Node * head)override; //counts number of nodes
		size_t depth(Node * head)override; //number of layers from root to leaf

	private:
		struct Node
		{
			E data;
			Node * left,right;
		};
		Node * root;
		Node * make_tree_of_size(size_t in);
		size_t depth;
	};
//---------Constructos and destructors---------------
	template <typename E>
	Binary_Tree<E>::Binary_Tree(void)
	:root(new Node), depth(1)
	{}

	template <typename E>
	Binary_Tree<E>::Binary_Tree(E data)
	:root(new Node), depth(1)
	{
		root->data=data;
	}

	template <typename E>
	Binary_Tree<E>::Binary_Tree(num_nodes)
	:root(make_tree_of_size(num_nodes))
	{
	}

	template <typename E>
	Binary_Tree<E>::~Binary_Tree(size_t num_nodes)
	{
		delete root;
	}

//-------the Traversals----------------
	template <typename E>
	void Binary_Tree<E>::pre_order_traverse(Node * in, void f ( E&) )//recursively traverse in preorder
	{
		if(in==nullptr)
			return;
		f(E);
		pre_order_traverse(in->left, f(E));
		pre_order_traverse(in->right, f(E));
	}

	template <typename E>
	void Binary_Tree<E>::in_order_traverse(Node * in, void f ( E&) )	//recursively traverse in in_order
	{
		if(in==nullptr)
			return;
		in_order_traverse(in->left, f(E));
		f(E);
		in_order_traverse(in->right, f(E));
	}

	template <typename E>
	void Binary_Tree<E>::post_order_traverse(Node * in, void f ( E&) ) //recursive post order
	{
		if(in==nullptr)
			return;
		in_order_traverse(in->left, f(E));
		in_order_traverse(in->right, f(E));
		f(E);

	}

	template <typename E>
	void Binary_Tree<E>::Morris_preorder(Node * in, void f ( E&) )
	{
		Node* anchor=in;
		while(anchor)
		{
			if(!anchor->left)
			{
				f(data);
				anchor=anchor->right;
			}else
			{
				Node iop=find_iop(in);
				if(iop->right==anchor)
				{
					iop->right=nullptr;
					anchor=anchor->right;
				}else
				{
					f(data);
					iop->right=anchor;
					anchor=anchor->left;
				}
			}
		}
	}

	template <typename E>
	void Binary_Tree<E>::Morris_inorder(Node * in, void f (E&) )
	{
		Node* anchor=in;
		while(anchor)
		{
			if(!anchor->left)
			{
				f(data);
				anchor=anchor->right;
			}else
			{
				Node iop=find_iop(in);
				if(iop->right==anchor)
				{
					f(data);
					iop->right=nullptr;
					anchor=anchor->right;
				}else //when iiop is not threaded
				{
					f(data);
					iop->right=anchor;
					anchor=anchor->left;
				}
			}
		}
	}

//----------Expected Tree Operations------
	template <typename E>
	void Binary_Tree<E>::insert(E data, size_t level)//inserts at a given depth
	{

	}
	template <typename E>
	void Binary_Tree<E>::append_as_leaf(E data) //appends as first available leaf at depth
	{
		append_as_leaf(data, root, 0);
	}

	template <typename E>
	bool Binary_Tree<E>::append_as_leaf(E data, Node * in, size_t level) //appends as first available leaf at depth
	{
			if(!depth)
			{
				in->left=new Node;
				in->left->data=data;
				++depth;
				return true;
			}
			if(level==depth)
				return false;

			if(!in->left&&level==depth-1)//if at layer befor depth and nothing is in left put something there
			{
				in->left=new Node;
				in->left->data=data;
				return true;
			} else if (!in->right&&level==depth-1)
			{
				in->left=new Node;
				in->left->data=data;
				return true;
			}

			if(!(append_as_leaf(data,in->left,level++)||append_as_leaf(data,in->right,level++)))// if tree is full
			{
				in=root;
				while(in)//go to left most node at depth and 
					in=in->left;
				in->data=data;
				depth++;
				return true;
			}

	}

	template <typename E>
	void Binary_Tree<E>::clear(void)//sets tree back to single empty node
	{
		delete root;
		root= new Node;
	}
	template <typename E>
	bool Binary_Tree<E>::contains(E element)//seatches tree for value
	{
		return contains(element, root );
	}

	template <typename E>
	bool Binary_Tree<E>::contains(E element,Node * in)//seatches tree for value
	{
		if(compare(element,root))
			return true;
		return (contains(element, root->left)||contains(element, root->right));

	}

	template <typename E>
	void Binary_Tree<E>::print(Node * in)//prints element at a given node
	{
		std::cout<<in->data;
	}

//--------helper functions
	template<typename E>
	Node * Binary_Tree<E>::make_tree_of_size(size_t in);
	{
		Node ptr = new Node;//make new node
		ptr->left=make_tree_of_size(in/2);//populate left sub tre
		ptr->right=make_tree_of_size(in/2);//populate right
		return ptr;
	}

	template<typename E>
	bool Binary_Tree<E>::compare(E first, E second)
	{
		return first==second;
	}








}

