#include "node.h"

skribbl::Node::Node()
{
}

skribbl::Node::Node(std::pair<uint16_t, uint16_t> p)
{
	pos = p;
}
