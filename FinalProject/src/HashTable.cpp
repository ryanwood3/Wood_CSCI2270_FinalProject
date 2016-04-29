#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

HashTable::HashTable()
{
    for(int i=0;i<tableSize;i++)
    {
        hashTable[i]=NULL;  //initialize table elements to be NULL
    }
    for(int t=0;t<alphaTableSize;t++)
        alphaHashTable[t]=NULL;
}

HashTable::~HashTable()
{
    //dtor
}

void HashTable::initialize()
{
    for(int i=0;i<tableSize;i++)
    {
        hashTable[i]=NULL;  //initialize table elements to be NULL
    }
    for(int t=0;t<alphaTableSize;t++)
        alphaHashTable[t]=NULL;
}

int HashTable::hashSum(string x,int s)
{
    int sum=0;
    for(int i=0;i<x.size();i++)
    {
        sum=sum+x[i];  //find hash index
    }
    sum=sum%s;
    return sum;
}

void HashTable::insertMovie(std::string name, int year,int quantity,int price)
{
    HashElem *current=new HashElem;
    current->title=name;
    current->year=year;  //create new instant of hashelement
    current->quantity=quantity;
    current->price=price;
    current->next=NULL;
    current->previous=NULL;
    int index=hashSum(name,10);
    if(hashTable[index]==NULL)
    {
        hashTable[index]=current;  //if no elements in that index
    }
    else
    {
        HashElem *temp=hashTable[index];  //else make a chain
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=current;
        current->previous=temp;
    }
    if(alphabetized==true)
        cout << "Note: Contents are no longer alphabetized" << endl;
    alphabetized=false;
}

void HashTable::deleteMovie(std::string name)
{
    int index=hashSum(name,10);
    HashElem *temp=hashTable[index];
    while(temp!=NULL && temp->title!=name)
    {
        temp=temp->next;
    }
    if(temp==NULL)
        cout << "Not found" << endl;
    else
    {
        if(temp->next==NULL && temp->previous==NULL)  //only thing in chain
        {
            delete temp;
            hashTable[index]=NULL;
        }
        else if(temp->next==NULL)
        {
            temp->previous->next=NULL;  //end of chain
            delete temp;
        }
        else if(temp->previous==NULL)
        {
            temp->next->previous=NULL;  //head of chain
            hashTable[index]=temp->next;
            delete temp;
        }
        else
        {
            temp->next->previous=temp->previous;
            temp->previous->next=temp->next;  //others
            delete temp;
        }
    }
    if(alphabetized==true)
        cout << "Note: Contents are no longer alphabetized" << endl;
    alphabetized=false;
}

void HashTable::findMovie(std::string name)
{
    int index=hashSum(name,10);
    HashElem *temp=hashTable[index];
        while(temp!=NULL && temp->title!=name)
        {
            temp=temp->next; //same search algorithm then output results
        }
        if(temp==NULL)
            cout << "Not found" << endl;
        else
        {
            cout << "Title: " << temp->title << endl;
            cout << "Year: " << temp->year << endl;
            cout << "Quantity: " << temp->quantity << endl;
            cout << "Price: " << temp->price << endl;
        }
}

void HashTable::printTableContents()
{
    bool empty=true;
    if(alphabetized==true)
    {
        for(int i=0;i<27;i++)
        {
            HashElem *temp=alphaHashTable[i];  //loop through and print out all movies
            while(temp!=NULL)
            {

                cout << temp->title << " , " << temp->year << " , " << temp->quantity << " , " << temp->price << endl;
                empty=false;
                temp=temp->next;
            }
        }
        if(empty==true)
        {
            cout << "Empty" << endl;  //unless its empty
        }
    }
    else
    {
        for(int i=0;i<10;i++)
        {
            HashElem *temp=hashTable[i];  //loop through and print out all movies
            while(temp!=NULL)
            {
                cout << temp->title << " , " << temp->year << " , " << temp->quantity << " , " << temp->price << endl;
                empty=false;
                temp=temp->next;
            }
        }
        if(empty==true)
        {
            cout << "Empty" << endl;  //unless its empty
        }
    }
}

void HashTable::alphabetizeList()
{
    if(alphabetized==true)
        cout << "Already alphabetized" << endl;
    else
    {
    alphabetized=true;
    for(int t=0;t<alphaTableSize;t++)
        alphaHashTable[t]=NULL;
    for(int i=0;i<10;i++)
    {
        HashElem *temp=hashTable[i];
        while(temp!=NULL)
        {
            for(int i=0;i<27;i++)
            {
                int alphaIndex=(temp->title[0])-65;
                if(alphaIndex<0)
                    alphaIndex=26;
                if(alphaIndex==i)
                {
                    HashElem *current=new HashElem;
                    current->title=temp->title;
                    current->year=temp->year;  //create new instant of hashelement
                    current->quantity=temp->quantity;
                    current->price=temp->price;
                    current->next=NULL;
                    current->previous=NULL;
                    if(alphaHashTable[alphaIndex]==NULL)
                    {
                        alphaHashTable[alphaIndex]=current;  //if no elements in that index
                        i=26;
                        temp=temp->next;
                    }
                    else
                    {
                        HashElem *temp1=alphaHashTable[alphaIndex];  //else make a chain
                        HashElem *head=temp1;
                        while(temp1!=NULL)
                        {
                            if(head->title.compare(current->title)>0)
                            {
                                alphaHashTable[alphaIndex]=current;
                                current->next=head;
                                head->previous=current;
                                temp=temp->next;
                                temp1=NULL;
                                i=26;
                            }
                            else if(temp1->title.compare(current->title)>0)
                            {
                                temp1->previous->next=current;
                                current->previous=temp1->previous;
                                current->next=temp1;
                                temp1->previous=current;
                                temp=temp->next;
                                temp1=NULL;
                                i=26;
                            }
                            else if(temp1->title.compare(current->title)<0)
                            {
                                if(temp1->next!=NULL)
                                    temp1=temp1->next;
                                else
                                {
                                    temp1->next=current;
                                    current->next=NULL;
                                    current->previous=temp1;
                                    temp=temp->next;
                                    temp1=current->next;
                                    i=26;

                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
}

void HashTable::quickFillStock(const char* fileName)
{
    ifstream inFile;
    string data;
    string title;
    string syear;
    string squantity;
    string sprice;
    int price;
    int year;
    int quantity;
    inFile.open(fileName);
    if(inFile.good())
    {
        while(getline(inFile,data))
        {
            stringstream ss(data);
            getline(ss,title,',');
            getline(ss,syear,',');
            getline(ss,squantity,',');
            getline(ss,sprice,',');
            const char* cprice=sprice.c_str();
            const char* cyear=syear.c_str();
            const char* cquantity=squantity.c_str();
            price=atoi(cprice);
            year=atoi(cyear);
            quantity=atoi(cquantity);
            insertMovie(title,year,quantity,price);
        }
    }
    else
        cout << "File failed to open" << endl;
}

void HashTable::rentMovie(string name)
{
    bool rented=false;
    if(alphabetized==false)
    {
    int index=hashSum(name,10);
    HashElem *temp=hashTable[index];
    while(temp!=NULL && temp->title!=name)
    {
        temp=temp->next; //same search algorithm then output results
    }
    if(temp==NULL)
        cout << "Not found" << endl;
    else
    {
        if(temp->quantity>=1)
        {
            for(int i=0;i<cart.size();i++)
            {
                if(temp->title==cart[i]->title)
                    rented=true;
            }
            if(rented==true)
                cout << "Movie already rented" << endl;
            else
            {
                temp->quantity--;
                cout << "Price: $1 , " <<temp->title << " added to cart" << endl;
                cart.push_back(temp);
            }
        }
        else
            cout << "Movie out of stock" << endl;
    }
    }
    else if(alphabetized==true)
    {
        int alphaIndex=(name[0])-65;
        if(alphaIndex<0)
            alphaIndex=26;
        HashElem *temp=alphaHashTable[alphaIndex];
        while(temp!=NULL && temp->title!=name)
        {
            temp=temp->next; //same search algorithm then output results
        }
        if(temp==NULL)
            cout << "Not found" << endl;
        else
        {
            if(temp->quantity>=1)
            {
                for(int i=0;i<cart.size();i++)
                {
                    if(temp->title==cart[i]->title)
                        rented=true;
                }
                if(rented==true)
                    cout << "Movie already rented" << endl;
                else
                {
                    temp->quantity--;
                    cout << "Price: $1 , " <<temp->title << " added to cart" << endl;
                    cart.push_back(temp);
                }
            }
            else
                cout << "Movie out of stock" << endl;
        }
    }
}

void HashTable::viewCart()
{
    int sum=0;
    if(cart.size()==0)
        cout << "Cart is empty" << endl;
    else
    {
        cout << "====Shopping Cart====" << endl;
        cout <<"To rent:" << endl;
        for(int i=0;i<cart.size();i++)
        {
            cout << cart[i]->title << endl;
        }
        cout << "Total: $" << cart.size() << endl;
        cout << "Due: 1 week from today" << endl;
        cout <<"To buy:" << endl;
        for(int t=0;t<buyCart.size();t++)
        {
            sum=sum+buyCart[t]->price;
            cout << buyCart[t]->title << endl;
        }
        cout << "Total: $" << sum << endl;
        cout << "Grand Total: $" <<(sum+cart.size()) << endl;
    }
}

void HashTable::returnMovie(string name)
{
    bool rented=false;
    if(alphabetized==false)
    {
    int index=hashSum(name,10);
    HashElem *temp=hashTable[index];
    while(temp!=NULL && temp->title!=name)
    {
        temp=temp->next; //same search algorithm then output results
    }
    if(temp==NULL)
        cout << "Not found" << endl;
    else
    {
        temp->quantity++;
        cout << temp->title << " has been returned" << endl;
    }
    }
    else if(alphabetized==true)
    {
        int alphaIndex=(name[0])-65;
        if(alphaIndex<0)
            alphaIndex=26;
        HashElem *temp=alphaHashTable[alphaIndex];
        while(temp!=NULL && temp->title!=name)
        {
            temp=temp->next; //same search algorithm then output results
        }
        if(temp==NULL)
            cout << "Not found" << endl;
        else
        {
            temp->quantity--;
            cout << temp->title << " has been returned" << endl;
        }
    }
}

void HashTable::buyMovie(string name)
{
    bool buy=false;
    int index=hashSum(name,10);
    HashElem *temp=hashTable[index];
    while(temp!=NULL && temp->title!=name)
    {
        temp=temp->next; //same search algorithm then output results
    }
    if(temp==NULL)
        cout << "Not found" << endl;
    else
    {
        if(temp->quantity>1)
        {
            for(int i=0;i<cart.size();i++)
            {
                if(temp->title==cart[i]->title)
                    buy=true;
            }
            if(buy==true)
                cout << "Movie already in cart" << endl;
            else
            {
                temp->quantity--;
                cout << "Price: $" << temp->price << " , " <<temp->title << " added to cart" << endl;
                buyCart.push_back(temp);
            }
        }
        else if(temp->quantity==1)
            deleteMovie(name);
        else if(temp->quantity==0)
            cout << "Movie out of stock" << endl;
    }
    alphabetized=false;
    cout << "Note: Contents are no longer alphabetized" << endl;
}
