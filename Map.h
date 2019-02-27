#ifndef _Map_H_
#define _Map_H_
//ADT Map

namespace cop3530{

	template <typename K, typename V, void (*C)(K &, K &), void (*E)(K &, K &) >
	class Map{
		public:
			virtual void insert(K key, V value)=0;
			virtual void remove(K key)=0;
			virtual void lookup(K key)=0;
			virtual bool contains(K key)=0;
			virtual bool is_empty()=0;
			virtual bool is_full()=0;
			virtual unsigned int size()=0;
			virtual unsigned int height()=0;
			virtual void balance()=0;
			virtual void clear()=0;

			virtual ~Map() {}; //Destructor
	};
	

}
#endif