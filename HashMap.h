#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <stdexcept>
#include <iostream>

namespace cop3530
{
	using size_t = std::size_t;
	template <typename K, typename V, size_t (*H)(K &)>
	class HashMap
	{
		public:
			HashMap();
			~HashMap();
			V get(K key);
			V put(K key, V value);
			int size();
			void clear();
			bool is_empty();
			bool contains_key(K key);
			bool contains_value(V value);

		private:
			struct Node{
				K key;
				V value;
			};
			Node data[];
	};
	
}
#endif