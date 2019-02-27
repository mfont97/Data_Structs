#ifndef _LOSER_TREE_H_
#define _LOSER_TREE_H_
//ADT Loser tre

namespace cop3530{

	template <typename E>
	class Loser_Tree{
		public:
			virtual ~Loser_Tree() {}; //Destructor
			virtual E get_and_remove_winner()=0;
			virtual void replace( size_t player)=0;
			virtual void eliminate(size_t player)=0;
			virtual E compare(E a, E b)=0;



		private:



	};
}