#ifndef _Heap_H_
#define _Heap_H_
//ADT Loser tre

namespace cop3530{

	template <typename E>
	class Heap{
		public:
			virtual ~Heap() {}; //Destructor
			virtual E get_and_remove_winner()=0;
			virtual void replace( size_t player)=0;
			virtual void eliminate(size_t player)=0;
			virtual E compare(E a, E b)=0;

	};
}