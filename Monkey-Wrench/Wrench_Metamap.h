#include "Wrench.h"

template<class A, class B, class C>
class WRENCHLIB_API MetaMap
{
	public:
		MetaMap() {};
		inline void push_newmap(A outer, B inner, C result) 
		{
			std::map<B, C> s;
			s[inner] = result;
			mmap[outer] = s;
		}
		inline void push_subvar(A outer, B inner, C result)
		{
			mmap[outer][inner] = result;
		}

		inline std::map<B, C> get(A outer)
		{
			return mmap[outer];
		}

		inline C get(A outer, B inner)
		{
			return mmap[outer][inner];
		}

		inline std::map<B, C> search_master(A outer)
		{
			if(mmap.find(outer) != mmap.end())
			{
				return mmap[outer];
			}
			else
			{
				std::map<B, C> a;
				a[NULL] = NULL;
				return a;
			}
		}

		inline C search_recursive(B inner)
		{
			std::map<A,std::map<B,C>>::iterator it;
			for(it = mmap.begin(); it != mmap.end(); ++it)
			{
				std::cout << "First:" << it->first;// << " Second:" << it->second << std::endl;
				if(mmap[it->first].find(inner) != mmap[it->first].end())
					return mmap[it->first][inner];
			}
			return NULL;
		}

	private:
		std::map<A,std::map<B,C>> mmap;

};
