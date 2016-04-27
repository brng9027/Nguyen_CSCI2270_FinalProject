#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree()
{
    //ctor
    root=NULL;
    for (int i=0; i<10; i++)
        inventory[i]="none";
}

void MovieTree::DeleteAll(MovieNode* node)
{
    if (node->leftChild!=NULL)
		DeleteAll(node->leftChild);
	if (node->rightChild!=NULL)
		DeleteAll(node->rightChild);
	cout<<"Deleting: "<<node->title<<endl;
	delete node;
}

MovieTree::~MovieTree()
{
    //dtor
    DeleteAll(root);
}

void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity)
{
    MovieNode* tmp=root;
    MovieNode* parent=NULL;
    MovieNode* node=new MovieNode(ranking, title, year, quantity);
    node->title=title;
    node->leftChild=NULL;
    node->rightChild=NULL;
    while (tmp!=NULL)
    {
        parent=tmp;
        if (node->title.compare(tmp->title)>0)
            tmp=tmp->rightChild;
        else if (node->title.compare(tmp->title)<0)
            tmp=tmp->leftChild;
    }
    if (root==NULL)
        root=node;
    else if (node->title.compare(parent->title)<0)
    {
        parent->leftChild=node;
        node->parent=parent;
    }
    else
    {
        parent->rightChild=node;
        node->parent=parent;
    }
}

void MovieTree::findMovie(std::string title)
{
    MovieNode* node=root;
    bool found;
	while (node!=NULL)
	{
		if (node->title.compare(title)>0)
			node=node->leftChild;
		else if (node->title.compare(title)<0)
			node=node->rightChild;
		else if (node->title==title)
        {
            found=true;
            break;
        }
        else
        {
            found=false;
            break;
        }
	}
	if (found==true)
    {
        cout<<"Movie Info:"<<endl;
        cout<<"==========="<<endl;
        cout<<"Ranking:"<<node->ranking<<endl;
        cout<<"Title:"<<node->title<<endl;
        cout<<"Year:"<<node->year<<endl;
        cout<<"Quantity:"<<node->quantity<<endl;
    }
    if (found==false)
        cout<<"Movie not found."<<endl;
}

void MovieTree::deleteMovieNode(std::string title)
{
    MovieNode* node=root;
    bool found;
	while (node!=NULL)
	{
		if (node->title.compare(title)>0)
			node=node->leftChild;
		else if (node->title.compare(title)<0)
			node=node->rightChild;
		else if (node->title==title)
        {
            found=true;
            break;
        }
        else
        {
            found=false;
            break;
        }
	}
	if (found==true)
    {
        if (node->leftChild==NULL && node->rightChild==NULL)  //no children
        {
            if (node->parent->leftChild==node)
                node->parent->leftChild=NULL;
            else
                node->parent->rightChild=NULL;
            delete node;
        }
        else if (node->leftChild!=NULL && node->rightChild==NULL)  //has a left child
        {
            MovieNode* x=node->leftChild;
            if (node->parent->leftChild==node)
                node->parent->leftChild=x;
            else
                node->parent->rightChild=x;
            x->parent=node->parent;
            delete node;
        }
        else if (node->leftChild==NULL && node->rightChild!=NULL)  //has a right child
        {
            MovieNode* x=node->rightChild;
            if (node->parent->leftChild==node)
                node->parent->leftChild=x;
            else
                node->parent->rightChild=x;
            x->parent=node->parent;
            delete node;
        }
        else  //has two children
        {
            if (node->rightChild->leftChild==NULL)  //replaced by right child
            {
                MovieNode* min=node->rightChild;
                if (node->parent->leftChild==node)
                    node->parent->leftChild=min;
                else
                    node->parent->rightChild=min;
                node->leftChild->parent=min;
                min->parent=node->parent;
                min->leftChild=node->leftChild;
                delete node;
            }
            else  //not right child
            {
                MovieNode* min=treeMinimum(node->rightChild);
                min->parent->leftChild=min->rightChild;
                min->rightChild->parent=min->parent;
                min->parent=node->parent;
                if (node->parent->leftChild==node)
                    node->parent->leftChild=min;
                else
                    node->parent->rightChild=min;
                min->leftChild=node->leftChild;
                min->rightChild=node->rightChild;
                node->rightChild->parent=min;
                node->leftChild->parent=min;
                delete node;
            }
        }
    }
    if (found==false)
        cout<<"Movie not found."<<endl;
}

void MovieTree::rentMovie(std::string title)
{
    MovieNode* node=root;
    bool found;
	while (node!=NULL)
	{
		if (node->title.compare(title)>0)
			node=node->leftChild;
		else if (node->title.compare(title)<0)
			node=node->rightChild;
		else if (node->title==title)
        {
            found=true;
            break;
        }
        else
        {
            found=false;
            break;
        }
	}
	if (found==true && node->quantity!=0)
    {
        cout<<"Movie has been rented."<<endl;
        node->quantity--;
        int q=0;
        for (int i=0; i<10; i++)
        {
            if (inventory[i]=="none")
            {
                inventory[i]=node->title;
                break;
            }
            if (inventory[i]!="none")
                q++;
            if (q==10)
                cout<<"But cannot be watched."<<endl;
        }
        cout<<"Movie Info:"<<endl;
        cout<<"==========="<<endl;
        cout<<"Ranking:"<<node->ranking<<endl;
        cout<<"Title:"<<node->title<<endl;
        cout<<"Year:"<<node->year<<endl;
        cout<<"Quantity:"<<node->quantity<<endl;
        if (node->quantity==0)
        {
            deleteMovieNode(node->title);
        }
    }
    else if (found==true && node->quantity==0)
        cout<<"Movie out of stock."<<endl;
    else if (found==false)
        cout<<"Movie not found."<<endl;
}

void MovieTree::printMovieInventory()
{
    printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode* node)
{
    if (node->leftChild!=NULL)
        printMovieInventory(node->leftChild);
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if (node->rightChild!=NULL)
        printMovieInventory(node->rightChild);
}

MovieNode* MovieTree::treeMinimum(MovieNode* node)
{
    while (node->leftChild!=NULL)
        node=node->leftChild;
    return node;
}

int MovieTree::countMovieNodes()
{
    int val=0;
    int* number=&val;
    countMovieNodes(root, number);
    int c=*number;
    return c;
}

void MovieTree::countMovieNodes(MovieNode* node, int* number)
{
    if (node->leftChild!=NULL)
        countMovieNodes(node->leftChild, number);
    *number = *number+1;
    if (node->rightChild!=NULL)
        countMovieNodes(node->rightChild, number);
}

void MovieTree::printYourInventory()
{
    for (int i=0; i<10; i++)
        cout<<inventory[i]<<endl;
}

void MovieTree::watchMovie(std::string title)
{
    int q=0;
    for (int i=0; i<10; i++)
    {
        if (inventory[i]==title)
        {
            cout<<title<<" has been watched."<<endl;
            inventory[i]="none";
            break;
        }
        if (inventory[i]!="none")
            q++;
        if (q==10)
            cout<<"Movie not found."<<endl;
    }
}

void MovieTree::returnMovie(std::string title)
{
    MovieNode* node=root;
    bool found;
	while (node!=NULL)
	{
		if (node->title.compare(title)>0)
			node=node->leftChild;
		else if (node->title.compare(title)<0)
			node=node->rightChild;
		else if (node->title==title)
        {
            found=true;
            break;
        }
        else
        {
            found=false;
            break;
        }
	}
	bool a=false;
	for (int i=0; i<10; i++)
    {
        if (inventory[i]==title)
            a=true;
    }
	if (found==true && a==true)
    {
        cout<<"Movie has been returned."<<endl;
        node->quantity++;
        for (int i=0; i<10; i++)
        {
            if (inventory[i]==title)
            {
                inventory[i]="none";
                break;
            }
        }
    }
    else if (found==false || a==false)
        cout<<"Movie not found."<<endl;
}

