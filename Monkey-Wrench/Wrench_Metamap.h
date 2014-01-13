#include "Wrench.h"

template<class A, class B, class C>
class WRENCHLIB_API MetaMap
{
	public:
		MetaMap() {};
		inline void push_newmap(A outter, B inner, C result) 
		{
			std::map<B, C> s;
			s[inner] = result;
			mmap[outter] = s;
		}
		inline void push_subvar(A outter, B inner, C result)
		{
			mmap[outter][inner] = result;
		}

		inline std::map<B, C> get(A outter)
		{
			return mmap[outter];
		}

		inline C get(A outter, B inner)
		{
			return mmap[outter][inner];
		}

		inline std::map<B, C> search_master(A outter)
		{
			if(mmap.find(outter) != mmap.end())
			{
				return mmap[outter];
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