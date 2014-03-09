#include "Wrench.h"
#include <vector>

template<class Type>
class AbstractNode
{
	public:
		AbstractNode();
		void SetVal(Type nval) {val = nval;}

	protected:
		//For every new Neighbor, those Neighbors will receive this node as a Neighbor as well.
		std::vector<AbstractNode*> Neighbors; 
		Type val;
};