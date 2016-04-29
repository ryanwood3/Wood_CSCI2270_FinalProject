#define HASHTABLE_H
#include <string>
#include <vector>

struct HashElem{
	std::string title;
	int year;
	int quantity;
	int price;
	HashElem *next;
    HashElem *previous;

	HashElem(){};
	HashElem(std::string in_title, int in_year)
	{
		title = in_title;
		year = in_year;
		next = NULL;
		previous = NULL;
	}

};

class HashTable
{
	public:
		HashTable();
		~HashTable();
		void printTableContents();
		void insertMovie(std::string name, int year,int quantity,int price);
		void deleteMovie(std::string name);
		void findMovie(std::string name);
		void alphabetizeList();
		void quickFillStock(const char* fileName);
		void rentMovie(std::string name);
		void viewCart();
		void returnMovie(std::string name);
		void buyMovie(std::string name);
		void initialize();
	private:
		int hashSum(std::string x, int s);
		int tableSize = 10;
		int alphaTableSize=27;
		HashElem* alphaHashTable[27];
		HashElem* hashTable[10];
		std::vector<HashElem*> cart;
		std::vector<HashElem*> buyCart;
		bool alphabetized=false;

};
