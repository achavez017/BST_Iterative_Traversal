/*
* A. Chavez
* December 5, 2019
* BinaryTree.cpp
*
* 	   	     10
*		/          \
*	      6               14
*	   /     \         /      \
*	  3       8       12       16
*	 / \     /  \    /  \     /   \
*  	2   4   7    9  11   13  15    18
*
* Binary search tree created and different iterative tree traversal algorithms are used to navigate through it.
* 4 separate values are looked up in BST and if found return the memory address it is located in.
*
*/

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

class Node
{
	private:
		int 	Data;
		Node* 	Left;
		Node* 	Right;

	public:
		Node(int d = 0, Node* L =nullptr, Node* R = nullptr):Data(d), Left(L), Right(R){}

		//Setters
		void setData (int d)  {Data  = d;}
		void setLeft (Node* l){Left  = l;}
		void setRight(Node* r){Right = r;}

		//Getters
		int   getData (){return Data;}
		Node* getLeft (){return Left;}
		Node* getRight(){return Right;}

		//Doers
		bool hasLeftChild (){return this->getLeft()  != nullptr ? true : false;}
		bool hasRightChild(){return this->getRight() != nullptr ? true : false;}
		bool hasChildren  (){return this->hasLeftChild() || this->hasRightChild() ? true : false;}
};

class BinarySearchTree
{
	private:
		string Name;
		int Size;
		int Levels;
		int Height;
		int Width;
		Node* Root;
		Node* EmptyNode;

	public:
		BinarySearchTree(string n = "Binary Search Tree") : Name(n)
		{
			Root = nullptr;
			Size = 0;
			EmptyNode = new Node(0);
		}

		//Setters
		void setName(string n){Name = n;}

		//Getters
		string 	getName(){return Name;}
		int		getSize(){return Size;}
		Node*	getRoot(){return Root;}

		//Print
		void printInfo()
		{	
			cout << Name << endl;
			cout << "  Number of Nodes: " << Size << endl;
			cout << "  Height: " << Height << " Levels: " << Levels << endl;
			cout << "  Root Node: " << Root << endl;
			cout << endl;
		}

		//Print Tree values in Level Order (Breadth First)
		void printLevelOrder() 
		{
			if(this->isEmpty())
			{
				cout << "Tree is empty!" << endl; 
				return; 
			}

			queue <Node*> Nq;
			
			Nq.push(Root);

			while(!Nq.empty())
			{
				Node* currentnode = Nq.front();
				cout << currentnode->getData() << " ";

				if(currentnode->hasLeftChild ()){Nq.push(currentnode->getLeft ());}
				if(currentnode->hasRightChild()){Nq.push(currentnode->getRight());}

				Nq.pop();
			}

			cout << endl;
		}
		
		void printPreOrder() //Print Tree values in preorder (Root, Left, Right) using iteration
		{
			if(this->isEmpty())
			{
				cout << "Tree is empty!" << endl; 
				return; 
			}

			stack <Node*> Ns;	//used stack data structure for LIFO method

			Ns.push(Root);		//push root to stack

			while(!Ns.empty())	//while stack is not empty
			{
				Node* currentnode = Ns.top();	//set node pointer to top of stack

				cout << currentnode->getData() << " "; //print root node

				Ns.pop();
			
				if(currentnode->hasRightChild()){Ns.push(currentnode->getRight());}	//push right child of parent to stack
				if(currentnode->hasLeftChild()){Ns.push(currentnode->getLeft());}		//push left child of parent to stack
			}

			cout << endl;
		}

		void printInOrder() // //Print Tree values in order (Left, Root, Right) using iteration
		{
			if(this->isEmpty())
			{
				cout << "Tree is empty!" << endl; 
				return; 
			}

			stack <Node*> Ns;

			Node* currentnode = Root;	
			
			while(!Ns.empty() || currentnode != nullptr)
			{
				if(currentnode != nullptr)	//if node is not NULL push to stack and set pointer to left child
				{
					Ns.push(currentnode);
					currentnode = currentnode->getLeft();
				}
				
				else
				{
					currentnode = Ns.top();	//set node pointer to value at top of stack
					Ns.pop();	//pop stack
					cout << currentnode->getData() << " ";	//print value just popped
					currentnode = currentnode->getRight();	//set node pointer to right child
				}
			}
			cout << endl;
		}
		
		//Print Tree values in postorder (Left, Right, Root) using iteration
		void printPostOrder() 
		{
			if(this->isEmpty())
			{
				cout << "Tree is empty!" << endl; 
				return; 
			}

			stack <Node*> Ns;

			Node* currentnode = Root;	
			
			while(!Ns.empty() || currentnode != nullptr)
			{
				if(currentnode != nullptr)
				{
					Ns.push(currentnode);
					currentnode = currentnode->getLeft();
				}

				else
				{
					if(Ns.top()->getRight() == nullptr)	//if right child of value in top of stack is NULL
					{
						currentnode = Ns.top();	//set node pointer to top of stack
						Ns.pop();	//pop stack
						cout << currentnode->getData() << " ";	//print popped value
						while(currentnode == Ns.top()->getRight())	//traverse up tree through right children
						{
							//pop and print stack values until stack is empty
							cout << Ns.top()->getData() << " ";	
							currentnode = Ns.top();	//set node pointer to top of stack
							Ns.pop();
							if(Ns.empty())
								break;
						}
					}

						if(!(Ns.empty()))
							currentnode = Ns.top()->getRight();	//set node pointer to right child of value on top of stack
						
						else
							currentnode = nullptr;	//set node pointer to NULL
				}
			}
			cout << endl;
		}

		//Doers
		bool isEmpty(){	return Root == nullptr ? true : false;}

		void buildTree(vector<int> vec)
		{
			for(auto i : vec){*this + new Node(i);}
		}

		void operator +(Node* n)
		{
			if(Size == 0)
			{
				Root = n;
			}
			else
			{
				addtoNode(n, Root);
			}

			Size++;
			Height = maxDepth(Root);
			Levels = Height + 1;
		}

		void operator +(vector<int> &vec)
		{
			for(auto i : vec){*this + new Node(i);}
		}

		Node* operator == (int i)	//Search
		{
			if(Size == 0){cout << "Tree is empty!" << endl; return nullptr;}

			return findData(i, Root);
		}

		
	private:
		//Helpers
		void addtoNode(Node* node2add, Node* currentnode)
		{
			if(currentnode == nullptr){return;}
			else if(node2add->getData() < currentnode->getData())
			{
				if(currentnode->getLeft() == nullptr)
				{
					currentnode->setLeft(node2add);
					return;
				}
				addtoNode(node2add, currentnode->getLeft());
			}
			else if(node2add->getData() > currentnode->getData())
			{
				if(currentnode->getRight() == nullptr)
				{
					currentnode->setRight(node2add);
					return;
				}
				addtoNode(node2add, currentnode->getRight());
			}

			return;
		}

		Node* findData(int data2find, Node* currentnode)
		{
			if(data2find == currentnode->getData())
			{
				cout << "Data: " << data2find << " found at Node(" << currentnode << ")" << endl;
				return currentnode;
			}
			else if ( (currentnode->getLeft() == nullptr) && (currentnode->getRight() == nullptr) )
			{
				cout << "Data: " << data2find << " not found." << endl;
				return currentnode;
			}
			else if(data2find < currentnode->getData())
			{
				findData(data2find, currentnode->getLeft());
			}
			else if(data2find > currentnode->getData())
			{
				findData(data2find, currentnode->getRight());
			}

			return nullptr;
		}

		int maxDepth(Node* currentnode)
		{
			if(currentnode == nullptr){return -1;}
			else
			{
				int lst_depth = maxDepth(currentnode->getLeft());
				int rst_depth = maxDepth(currentnode->getRight());

				return lst_depth > rst_depth ? ++lst_depth : ++rst_depth;
			}
		}
};

int main() {
	BinarySearchTree BST;
	vector<int> v = {10, 6, 8, 7, 9, 3, 2, 4, 14, 12, 16, 18, 15, 11, 13};	
	BST + v; 		 				//Create Tree from vector
	Node* newnode = nullptr;

	BST.printInfo();		 		

	cout << "Values 3, 12, 19, & 43 searched for in BST" << endl;

	BST == 3;
	BST == 12;
	BST == 19;
	BST == 43;
	cout << endl;
	
	cout << "Level Order:" << endl;
	BST.printLevelOrder();
	cout << endl << "Preorder:" << endl;
	BST.printPreOrder(); 
	cout << endl << "Inorder:" << endl;
	BST.printInOrder(); 
	cout << endl << "Postorder:" << endl;
	BST.printPostOrder();
	cout << endl; 	

	return 0;
}
