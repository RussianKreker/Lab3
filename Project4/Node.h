#ifndef Node_H
#define Node_H
class Node 
{
public:
	int value;
	Node* Left;
	Node* Right;
	Node* parent;

	Node(int value, Node* parent, Node* Left = nullptr, Node* Right = nullptr)
	{
		this->parent = parent;
		this->value = value;
		this->Left = Left;
		this->Right = Right;
	};

	~Node()
	{
		int key;
		Left = nullptr;
		Right = nullptr;
		parent = nullptr;
	}
};
#endif