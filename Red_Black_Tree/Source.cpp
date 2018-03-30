#include <cstdlib>
#include <iostream>
#include <fstream>

enum Color { RED, BLACK};

using namespace std;

typedef struct node
{
	node *left;         /* left child */
	node *right;        /* right child */
	node *parent;       /* parent */
	int color;            /* node color (BLACK - true, RED - false) */
	int data;                     /* data stored in node */
}*nodePtr;

class tree
{
private:


	nodePtr root;
	nodePtr curr;
	nodePtr temp;
public:
	tree();
	void insertNode(int data);
	void rotateLeft(nodePtr data);
	void rotateRight(nodePtr data);
	void insertfixup(nodePtr data);
	void deleteNode(int data);
	void deletefixup(nodePtr data);
	void found(int data);
	void print(nodePtr data);
	void printTree();
	
	


};


tree::tree()
{
	root = NULL;
	curr = NULL;
	temp = NULL;
}



void tree::rotateLeft(nodePtr ptr) {
	nodePtr right_child = ptr->right;
	ptr->right = right_child->left;

	if (ptr->right != NULL)
		ptr->right->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == NULL)
		root = right_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = right_child;
	else
		ptr->parent->right = right_child;

	right_child->left = ptr;
	ptr->parent = right_child;
}

void tree::rotateRight(nodePtr ptr) {
	nodePtr left_child = ptr->left;
	ptr->left = left_child->right;

	if (ptr->left != NULL)
		ptr->left->parent = ptr;

	left_child->parent = ptr->parent;

	if (ptr->parent == NULL)
		root = left_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = left_child;
	else
		ptr->parent->right = left_child;

	left_child->right = ptr;
	ptr->parent = left_child;
}


void tree::insertfixup(nodePtr z)
{
	if (z->parent != NULL && z->parent->parent != NULL)
	{
		while (z != NULL && z->parent != NULL &&
			z->parent->parent != NULL && !z->parent->color == BLACK)
			
		{
			if (z->parent == z->parent->parent->left)
			{
				nodePtr y = z->parent->parent->right;
				if (y != NULL && y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else if (z == z->parent->right)
				{
					z = z->parent;
					rotateLeft(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rotateRight(z->parent->parent);

			}
			else
			{

				nodePtr y = z->parent->parent->left;
				if (y != NULL && y->color == RED) 
				{
					z->parent->color = BLACK; 
					y->color = BLACK; 
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						rotateRight(z);
					}
					z->parent->color = BLACK; 
					z->parent->parent->color = RED; 
					rotateLeft(z->parent->parent);
				}
			}
		}
	}
}

void tree::insertNode(int z)
{
	int i = 0;
	nodePtr p = new node;
	nodePtr q = new node;
	nodePtr t = new node;
	t->data = z;
	t->left = NULL;
	t->right = NULL;
	t->color = RED;
	p = root;
	q = NULL;
	if (root == NULL)
	{
		root = t;
		t->parent = NULL;
	}
	else
	{
		while (p != NULL)
		{
			q = p;
			if (p->data < t->data)
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (q->data < t->data)
			q->right = t;
		else
			q->left = t;
	}
	insertfixup(t);
}


void tree::deletefixup(nodePtr x) {


	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			nodePtr w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rotateRight(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotateLeft(x->parent);
				x = root;
			}
		}
		else {
			nodePtr w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					rotateLeft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotateRight(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}


void tree::deleteNode(int deldata)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	nodePtr p = new node;
	p = root;
	nodePtr y = NULL;
	nodePtr q = NULL;
	int found = 0;
	while (p != NULL && found == 0)
	{
		if (p->data == deldata)
			found = 1;
		if (found == 0)
		{
			if (p->data < deldata)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == 0)
	{
		cout << "\nElement Not Found.";
		return;
	}
	else
	{
		cout << "\nDeleted Element: " << p->data << endl;;

		if (p->left == NULL || p->right == NULL)
			y = p;
		else 
		{
			if (p->left != NULL)
			{
				y = p->left;
				while (y->right != NULL)
					y = y->right;
			}
			else
			{
				y = p->right;
				while (y->left != NULL)
					y = y->left;
			}
		}
			if (y->left != NULL)
			q = y->left;
		else
		{
			if (y->right != NULL)
				q = y->right;
			else
				q = NULL;
		}
		if (q != NULL)
			q->parent = y->parent;
		if (y->parent == NULL)
			root = q;
		else
		{
			if (y == y->parent->left)
				y->parent->left = q;
			else
				y->parent->right = q;
		}
		if (y != p)
		{
			p->color = y->color;
			p->data = y->data;
		}
		if (y->color == BLACK)
			deletefixup(p);
	}
}



void tree::print(nodePtr p)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	if (p != NULL)
	{
		if (p->left)
		{

			cout << p->data << "--" << p->left->data << endl;
		}
		if (p->right)
		{

			cout << p->data << "--" << p->right->data << endl;
		}
		if (p->left)
		{
			print(p->left);
		}

		if (p->right)
		{
			print(p->right);
		}

	}
}

void tree::printTree()
{
	print(root);
}


//void tree::print(nodePtr p)
//{
//	int h, ch;
//	ofstream F;
//	
//
//	if (root == NULL)
//	{
//		cout << "\nEmpty Tree.";
//		return;
//	}
//	if (p != NULL)
//	{
//		if (p->left)
//		{
//			
//			h = p->data;
//			ch = p->left->data;
//			ofstream file4("C:/Users/plaer/Desktop/graph.dot", ios_base::app);
//			file4 << h;
//			file4 << "--";
//			file4 << ch << endl;
//			file4.close();
//		}
//		if (p->right)
//		{
//			
//			h = p->data;
//			ch = p->right->data;
//			ofstream file2("C:/Users/plaer/Desktop/graph.dot", ios_base::app);
//			file2 << h << "--" << ch << ";" << endl;
//			file2.close();
//		}
//		if (p->left)
//		{
//			print(p->left);
//		}
//		
//		if (p->right)
//		{
//			print(p->right);
//		}
//		
//	}
//	F.close();
//
//}

//void tree::printTree()
//{
//	ofstream file("C:/Users/plaer/Desktop/graph.dot", ios_base::out);
//	file << "graph tree {\n";
//	file.close();
//	
//	print(root);
//
//	ofstream file1("C:/Users/plaer/Desktop/graph.dot", ios_base::app);
//	file1 << "}";
//	file1.close();
//}

void tree::found(int data)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	nodePtr p = new node;
	p = root;
	int found = 0;
	while (p != NULL && found == 0)
	{
		if (p->data == data)
			found = 1;
		if (found == 0)
		{
			if (p->data < data)
				p = p->right;
			else
				p = p->left;
		}
	}
	
	if (found == 0)
	{
		cout << "\nElement Not Found.";
		return;
	}

	else
	{
		nodePtr w = new node;
		w = root;
		cout << w->data;
		int f = 0;
		if (w->data < data)
			w = w->right;
		else
			w = w->left;
		while (w != NULL && f == 0)
		{
			
			if (w->data == data)
				f = 1;
			cout << "->" << w->data;
			if (f == 0)
			{
				if (w->data < data)
				w = w->right;
				else 
				w = w->left;
			}
			
		}
		delete(w);
		
	}
}




int menu()
{
	cout << "\n1 : Add number \n";
	cout << "2 : Delete number \n";
	cout << "3 : Found number \n";
	cout << "4 : Print tree \n";
	cout << "5 : Exit \n";
	return 0;
}


int main()
{
	int a, v, d;
	int ex = 20202;
	tree node;
	do
	{
		menu();
		cout << "Enter you choice\n";
		cin >> a;
		switch (a)
		{
		case 1: cout << "Enter Value of new element\n ";
			cin >> v;
			node.insertNode(v);
			break;

		case 2: cout << "Enter removable elevent \n";
			cin >> d;
			node.deleteNode(d);
			break;

		case 3: cout << "Enter Value of element\n ";
			cin >> v;
			node.found(v);
			break;

		case 4:
			node.printTree();
			break;

		case 5: a = ex; exit;
			break;
		default: cout << "Bad choise! Enter you choice\n";
			break;
		}
	} while (a != ex);


	return (0);
}