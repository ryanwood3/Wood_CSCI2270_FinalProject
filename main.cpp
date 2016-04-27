#include <iostream>
#include "HashTable.h"

using namespace std;

int main()
{
    int input=0;
    HashTable(table);
    table.initialize();
    cout << "Quick fill stock? (1. Yes, 2.No)" << endl;
    cin >>input;
    cin.ignore();
    if(input==1)
    {
        string fileName;
        cout << "Enter text file name:" << endl;
        getline(cin,fileName);
        const char* cfileName=fileName.c_str();
        table.quickFillStock(cfileName);
    }
    while (input!=11)
    {
        cout << "======Main Menu======" <<	endl;
        cout << "1. Quick fill stock" << endl;
        cout <<	"2. Insert movie" << endl;
        cout <<	"3. Delete movie" << endl;
        cout <<	"4. Find movie" << endl;  //print out the menu
        cout << "5. Rent movie" << endl;
        cout << "6. Return movie" << endl;
        cout << "7. Buy movie" << endl;
        cout << "8. Print table contents" << endl;
        cout << "9. Alphabetize contents" << endl;
        cout << "10. View Cart" << endl;
        cout << "11. Quit" << endl;
        cin >>input;
        cin.ignore();
        if(input==1)
        {
            string fileName;
            cout << "Enter text file name:" << endl;
            getline(cin,fileName);
        }
        if(input==2)
        {
            string movieinput;
            int movieyear;
            int moviequantity;
            int movieprice;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            cout << "Enter year:" << endl;
            cin >> movieyear;
            cin.ignore();
            cout << "Enter quantity:" << endl;
            cin>> moviequantity;
            cin.ignore();
            cout << "Enter price:" << endl;
            cin >> movieprice;
            cin.ignore();
            table.insertMovie(movieinput,movieyear,moviequantity,movieprice);
        }
        else if(input==3)
        {
            string movieinput;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            table.deleteMovie(movieinput);
        }
        else if(input==4)
        {
            string movieinput;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            table.findMovie(movieinput);
        }
        else if(input==5)
        {
            string movieinput;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            table.rentMovie(movieinput);
        }
        else if(input==6)
        {
            string movieinput;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            table.returnMovie(movieinput);
        }
        else if(input==7)
        {
            string movieinput;
            cout << "Enter title:" << endl;
            getline(cin,movieinput);
            table.buyMovie(movieinput);
        }
        else if(input==8)
        {
            table.printTableContents();
        }
        else if(input==9)
        {
            table.alphabetizeList();
        }
        else if(input==10)
        {
            table.viewCart();
        }
        else if(input==11)
        {
            cout << "Goodbye!" << endl;
        }
    }
    return 0;
}
