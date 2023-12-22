#ifndef NODE_H
#define NODE_H

#include <QPainter>

class Node
{
	QPoint pos;
public:
	Node();
	Node(QPoint p);
	void setCoord(QPoint p) {
		pos = p;
	}
	QPoint getPosition() {
		return pos;
	}
};

#endif // NODE_H
