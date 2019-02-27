#ifndef _BSTRand_H_
#define _BSTRand_H_
#include <stdexcept>


namespace cop3530
{
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	class BSTRand
	{
		private:
			struct Node
			{
				K key;
				V value;
				Node * left = nullptr;
				Node * right = nullptr;
				unsigned int height=0;
			};
		public:
			BSTRand(void);
			BSTRand(K key, V value);
			void insert(K key, V value);
			void remove(K key);
			V& lookup(K key);
			bool contains(K key);
			bool is_empty(void);
			bool is_full(void);
			unsigned int size(void);
			unsigned int height(void);
			int balance(void);
			void clear(void);
			void print(void);
			~BSTRand() ; //Destructor

			
		private:
			unsigned int numNodes;
			Node * root;
			int update_heights(Node * in);
			Node * goto_insert(K key, Node * in);
			Node * find_iop(K key, Node * in);
			Node * new_node(K key, V value);	
			void print(Node * in);
			void delete_node(Node * del);
			void swap(Node * parent, Node * child);
			void insert_at_root(Node * in, K key,V value);
			void rotate_left(Node *& in);
			void rotate_right(Node *& in);
	};
	//-----------------------FUNCTION DECLARATIONS------------------------
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	BSTRand<K,V,C,E>::BSTRand(void)
	:root(nullptr), numNodes(0)
	{
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	BSTRand<K,V,C,E>::BSTRand(K key, V value)
	:numNodes(0), root(new_node(key, value))
	{
	}
	
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::insert_at_root(Node * in, K key, V value)//insert in O(log n)
	{
		if(!root){
			root=new_node(key,value);
			return;
		}
		Node * ptr=new_node(root->key,root->value);
		in->key=key;
		in->value=value;
		Node * insert=goto_insert(ptr->key, root);
			if(E(ptr->key,insert->key)){
				//std::cout<<"New value at Key: "<<key<<"="<<value<<"\n";
				insert->value=ptr->value;
			}else if(C(ptr->key,insert->key))
			{
				insert->right=ptr;
			//	std::cout<<"inserted_r: ("<<key<<","<<value<<")\n";
			}else
			{
				insert->left=ptr;
			//	std::cout<<"inserted_l: ("<<key<<","<<value<<")\n";
			}
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::insert(K key, V value)//insert in O(log n)
	{
		insert_at_root(root,key, value);
		update_heights(root);
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	typename cop3530::BSTRand<K,V,C,E>::Node * BSTRand<K,V,C,E>::goto_insert(K key, Node * in)//insert in O(log n)
	{
		while(in)
		{
			if(E(key,in->key))
				return in;
			else if(C(key, in->key))
			{
				if(in->right)
					in=in->right;
				else
					return in;
			}else{
				if(in->left)
					in=in->left;
				else
					return in;
			}
		}
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::remove(K key)
	{
		if(numNodes==0){
			std::cout<<"Map is empty\n";
			return;
		}
		Node *ptr= root;
		Node *iop;
		while(ptr!=nullptr)
		{
			if(E(key,ptr->key)){
				iop=find_iop(key, ptr);
				ptr->key=iop->key;
				ptr->value=iop->value;
				while(iop->left){
					swap(iop,iop->left);//swaps iop key value pair with child
					iop=iop->left;//set iop (to_delete) to leftmost child
				}
				delete_node(iop);
				return;
			}
			else if(C(key,ptr->key)){
				ptr=ptr->right;
			}
			else{
				ptr=ptr->left;
			}
		}
		throw std::runtime_error("RUNTIME_ERROR: Key does not exist in map");
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	typename cop3530::BSTRand<K,V,C,E>::Node * BSTRand<K,V,C,E>::find_iop(K key, Node * in)//insert in O(log n)
	{
		Node *ptr=in;
		if(!ptr->left) //in case of removal from left most leaf of right subtree return in to be deleted
			return in;
        if (ptr->left != nullptr)
        {
            	ptr = ptr->left;
            	while (ptr->right)
               		ptr = ptr->right;
        }
        return ptr;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	V& BSTRand<K,V,C,E>::lookup(K key)
	{
		if(numNodes==0){
			throw std::runtime_error("Map is empty!");
		}
		Node *ptr= root;
		while(ptr!=nullptr)
		{
			if(E(key,ptr->key)){
				return (ptr->value);
			}
			else if(C(key,ptr->key)){
				ptr=ptr->right;
			}
			else{
				ptr=ptr->left;
			}
		}
		throw std::runtime_error("RUNTIME_ERROR: Key does not exist in map");
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	bool BSTRand<K,V,C,E>::contains(K key)
	{
		Node *ptr= root;
		while(ptr!=nullptr)
		{
			if(E(key,ptr->key)){
				return true;
			}
			else if(C(key,ptr->key)){
				ptr=ptr->right;
			}
			else{
				ptr=ptr->left;
			}
		}
		return false;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	bool BSTRand<K,V,C,E>::is_empty(void)
	{
		return root==0;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	bool BSTRand<K,V,C,E>::is_full(void)
	{
		return root!=0;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	unsigned int BSTRand<K,V,C,E>::size(void)
	{
		return numNodes;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	unsigned int BSTRand<K,V,C,E>::height(void)
	{
		update_heights(root);
		return root->height;
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	int BSTRand<K,V,C,E>::balance(void)
	{
		update_heights(root);
		return (root->left->height)-(root->right->height);//returns balance factor
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::clear(void)
	{
		while(!is_empty())
			remove(root->key);
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	int BSTRand<K,V,C,E>::update_heights(Node * in)
	{
		if(in==nullptr)
			return 0;
		if(in->left&&in->right)
			in->height=(update_heights(in->left)>update_heights(in->right)) ?  update_heights(in->left)+1:update_heights(in->right)+1;
		else if(in->left)
			in->height=update_heights(in->left)+1;
		else if(in->right)
			in->height=update_heights(in->right)+1;
		return in->height;
	}

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::print(void)	
	{
		if(!root){
			std::cout<<"Map is empty";
		}
		print(root);
		
	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::print(Node * in)
	{
		if(in==nullptr)
			return;
		print(in->left);
		std::cout<<"( "<<in->key<<","<<in->value<<" ) " ;
		print(in->right);

	}	

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void BSTRand<K,V,C,E>::delete_node(Node * del)
	{
		Node * ptr=root;
		while(ptr!=del)
		{
			if(C(del->key,ptr->key))
			{
				if(ptr->right==del)
				{
					delete ptr->right;
					ptr->right=nullptr;
					numNodes--;
					return;
				}
				ptr=ptr->right;
			}
			else
			{
				if(ptr->left==del)
				{
					delete ptr->left;
					ptr->left=nullptr;
					numNodes--;
					return;
				}
				ptr=ptr->left;
			}
		}
	}
		

	

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	typename cop3530::BSTRand<K,V,C,E>::Node * BSTRand<K,V,C,E>::new_node(K key, V value)
	{
		Node* ptr=new Node;
		ptr->key=key;
		ptr->value=value;
		numNodes++;
		return ptr;

	}
	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void  BSTRand<K,V,C,E>::swap(Node* parent, Node* child)
	{
		Node * tmp=new Node;
		tmp->key=parent->key;
		tmp->value=parent->value;
		parent->key=child->key;
		parent->value=child->value;
		child->key=tmp->key;
		child->value=tmp->value;
	}

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void  BSTRand<K,V,C,E>::rotate_left(Node*& in)
	{
		if(!in->left)
			return;
		Node * ptr=in;
		in=in->left;
		ptr->left=in->right;
		in->right=ptr;
	}

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	void  BSTRand<K,V,C,E>::rotate_right(Node*& in)
	{
		if(!in->right)
			return;
		Node * ptr=in;
		in=in->right;
		ptr->right=in->left;
		in->left=ptr;
	}

	template <typename K, typename V, bool (*C)(K &, K &), bool (*E)(K &, K &) >
	BSTRand<K,V,C,E>::~BSTRand(void)
	{
	}

	
}
#endif