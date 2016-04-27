//Bryant Nguyen
#include <iostream>
#include "MovieTree.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    MovieTree tree=MovieTree();
    ifstream inFile;
    string data;
    inFile.open("Assignment6Movies.txt");
    if (inFile.good())
    {
        int index=0;
        int number=1;
        while(getline(inFile, data))
        {
            int ranking; string title; int year; int quantity; string data2;
            stringstream text(data);
            while(getline(text, data2, ','))
            {
                if (number==1)
                {
                    istringstream(data2)>>ranking;
                    number++;
                }
                else if (number==2)
                {
                    title=data2;
                    number++;
                }
                else if (number==3)
                {
                    istringstream(data2)>>year;
                    number++;
                }
                else if (number==4)
                {
                    istringstream(data2)>>quantity;
                    number=1;
                }
            }
            tree.addMovieNode(ranking, title, year, quantity);
            index++;
        }
    }

    else
        cout<<"file unsuccessfully opened"<<endl;
    inFile.close();


    int n=0;
    while (n==0)
    {
        int choice;
        cout<<"======Main Menu======\n"
        "1. Find a movie\n"
        "2. Rent a movie\n"
        "3. Print the inventory\n"
        "4. Delete a movie\n"
        "5. Count the movies\n"
        "6. Watch a Movie\n"
        "7. Return a Movie\n"
        "8. Quit"<<endl;
        cin>>choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            {
                string title;
                cout<<"Enter title:"<<endl;
                getline(cin, title);
                tree.findMovie(title);
                break;
            }
        case 2:
            {
                string title;
                cout<<"Enter title:"<<endl;
                getline(cin, title);
                tree.rentMovie(title);
                break;
            }
        case 3:
            {
                tree.printMovieInventory();
                break;
            }
        case 4:
            {
                string title;
                cout<<"Enter title:"<<endl;
                getline(cin, title);
                tree.deleteMovieNode(title);
                break;
            }
        case 5:
            {
                cout<<"Tree contains: "<<tree.countMovieNodes()<<" movies."<<endl;
                break;
            }
        case 6:
            {
                string title;
                cout<<"Pick a movie to watch:"<<endl;
                tree.printYourInventory();
                cout<<"Enter title:"<<endl;
                getline(cin, title);
                tree.watchMovie(title);
                break;
            }
        case 7:
            {
                string title;
                cout<<"Pick a movie to return:"<<endl;
                tree.printYourInventory();
                cout<<"Enter title:"<<endl;
                getline(cin, title);
                tree.returnMovie(title);
                break;
            }
        case 8:
            {
                cout<<"Goodbye!"<<endl;
                n++;
                return 0;
                break;
            }
        }
    }
}








