#include"Tree.h"
#include<iostream> 
#include"stack.h"

Tree::Tree()
{
	Root = nullptr;
}
Tree::~Tree(){}

void Tree::insert(int val)
{
	if (Root == NULL) 
	{
		Root = new Node(val, NULL, NULL);
	}
	else 
	{
		Node* current;
		current = Root;
		while(true) 
		{
			if (val <= current->value) 
			{
				if (current->Left == NULL) 
				{
					current->Left = new Node(val, current);
					break;
				}
				current = current->Left;
			}
			else {
				if (current->Right == NULL) 
				{
					current->Right = new Node(val, current);
					break;
				}
				current = current->Right;
			}
		}
	}
}

void Tree::remove(int val)
{
	if (!contains(val)) 
	{
		throw "element is absent";
	}
	else 
	{
	Node* current;
	current = Root;
	if (current->value == val) {
		if (current->Left == NULL && current->Right == NULL) 
		{
			delete current;
			return;
		}
		if (current->Left != NULL && current->Right == NULL) 
		{
			current->Left->parent = current->parent;
			Root = current->Left;
			delete current;
			return;
		}
		if (current->Left == NULL && current->Right != NULL) 
		{
			current->Right->parent = current->parent;
			Root = current->Right;
			delete current;
			return;
		}
		else 
		{
			Node* supCurrent;
			supCurrent = current->Right;
			if (supCurrent->Left != NULL) 
			{
				while (supCurrent->Left != NULL) 
				{
					supCurrent = supCurrent->Left;
				}
				supCurrent->parent->Left = NULL;
			}
			else 
			{
				supCurrent->parent->Right = supCurrent->Right;
			}
			current->Left->parent = supCurrent;
			supCurrent->Left = current->Left;
			supCurrent->parent = current->parent;
			while (supCurrent->Right != NULL)
			{
				supCurrent = supCurrent->Right;
			}
			current->Right->parent = supCurrent;
			supCurrent->Right = current->Right;
			return;
		}
	}
	while (true)
	{
		if (val <= current->value) 
		{
			current = current->Left;
			if (current->parent->Left->value == val) 
			{
				if (current->Left == NULL && current->Right == NULL) 
				{
					current->parent->Left = NULL;
					delete current;
					break;
				}
				if (current->Left != NULL && current->Right == NULL) 
				{
					current->parent->Left = current->Left;
					current->Left->parent = current->parent;
					delete current;
					break;
				}
				if (current->Left == NULL && current->Right != NULL) 
				{
					current->parent->Left = current->Right;
					current->Right->parent = current->parent;
					delete current;
					break;
				}
				else 
				{
					Node* supCurrent;
					supCurrent = current->Right;
					if (supCurrent->Left != NULL) 
					{
						while (supCurrent->Left != NULL) 
						{
							supCurrent = supCurrent->Left;
						}
						supCurrent->parent->Left = NULL;
					}
					else 
					{
						supCurrent->parent->Right = supCurrent->Right;
					}
					current->parent->Left = supCurrent;
					current->Left->parent = supCurrent;
					supCurrent->Left = current->Left;
					supCurrent->parent = current->parent;
					while (supCurrent->Right != NULL)
					{
						supCurrent = supCurrent->Right;
					}
					current->Right->parent = supCurrent;
					supCurrent->Right = current->Right;
					delete current;
					break;
				}
			}
		}
		else 
		{
			current = current->Right;
			if (current->parent->Right->value == val) 
			{
				if (current->Left == NULL && current->Right == NULL) 
				{
					current->parent->Right = NULL;
					delete current;
					break;
				}
				if (current->Left != NULL && current->Right == NULL) 
				{
					current->parent->Right = current->Left;
					current->Left->parent = current->parent;
					delete current;
					break;
				}
				if (current->Left == NULL && current->Right != NULL) 
				{
					current->parent->Right = current->Right;
					current->Right->parent = current->parent;
					delete current;
					break;
				}
				else 
				{
					Node* supCurrent;
					supCurrent = current->Right;
					if (supCurrent->Left != NULL)
					{
						while (supCurrent->Left != NULL) 
						{
							supCurrent = supCurrent->Left;
						}
						supCurrent->parent->Left = NULL;
					}
					else
					{
						supCurrent->parent->Right = supCurrent->Right;
					}
					current->parent->Right = supCurrent;
					current->Left->parent = supCurrent;
					supCurrent->Left = current->Left;
					supCurrent->parent = current->parent;
					while (supCurrent->Right != NULL)
					{
						supCurrent = supCurrent->Right;
					}
					supCurrent->Right = current->Right;
					current->Right->parent = supCurrent;
					delete current;
					break;
				}
			}

		}
	}
	}

}

bool Tree::contains(int val)
{
	if (Root == NULL)
	{
		return 0;
	}
	else {
		Node* current;
		current = Root;
		for (;;) {
			if (val <= current->value) {
				if (current->value == val)
				{
					return 1;
				}
				if (current->Left == NULL)
				{
					return 0;
				}
				current = current->Left;
			}
			else {
				if (current->value == val)
				{
					return 1;
				}
				if (current->Right == NULL)
				{
					return 0;
				}
				current = current->Right;
			}
		}
	}
}

Tree::DepthIterator::DepthIterator(Node* root) 
{
	current = root;
	if (current != nullptr) 
	{
		Stack.push(current);
	}
	else {
		throw "Tree is empty";
	}
}

Tree::DepthIterator::~DepthIterator(){}

int Tree::DepthIterator::next() 
{
	int tmp = current->value;
	if (!has_next()) {
		throw "Tree is empty";
	}
	if (current->Right != nullptr) 
	{
		if (check) {
			Stack.pop_front();
			check = false;
		}
		Stack.push(current->Right);
	}
	if (current->Left != nullptr) 
	{
		current = current->Left;
	}
	else
	{
		if (check) {
			Stack.pop_front();
		}
		if (has_next()) {
			current = Stack.head->date;
		}
		check = true;
	}
	return tmp;
}

bool Tree::DepthIterator::has_next()
{
	if (current->Left == nullptr && current->Right == nullptr && Stack.size == 0) return false;
	else return true;
}
Tree::WidthIterator::WidthIterator(Node* root) 
{
	current = root;
	if (current != nullptr) {
		Queue.push(current);
	}
	else {
		throw "Tree is empty";
	}

}

Tree::WidthIterator::~WidthIterator() 
{
	delete current;
	Queue.clear();
}

int Tree::WidthIterator::next() 
{

	if (!has_next()) 
	{
		throw "Tree is empty";
	}
	current = Queue.head->Element;
	Queue.pop();
	if (current->Left != nullptr) 
	{
		Queue.push(current->Left);
	}
	if (current->Right != nullptr) 
	{
		Queue.push(current->Right);
	}
	return current->value;
}

bool Tree::WidthIterator::has_next() 
{
	if (current->Left == nullptr && current->Right == nullptr && Queue.size == 0) return false;
	else return true;
}