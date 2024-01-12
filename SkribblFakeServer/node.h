#include <iostream>

namespace skribbl
{
	using std::uint16_t;

	class Node
	{
		std::pair<uint16_t, uint16_t> pos;
	public:
		Node();
		Node(std::pair<uint16_t, uint16_t> p);
		void setCoord(std::pair<uint16_t, uint16_t> p) {
			pos = p;
		}
		std::pair<uint16_t, uint16_t> getPosition() {
			return pos;
		}
	};
}