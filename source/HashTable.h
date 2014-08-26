//
//
//
//   Project : Schrˆdinger's cat
//   File Name : HashTable.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_HASHTABLE_H)
#define _HASHTABLE_H

#include <string>
#include <iostream>
#include "Iw2D.h"

using namespace std;

template <typename T> 
class HashTable
{
public:
	
	HashTable()
	{
		this->table = CIwArray<CIwArray<pair<string,T> > >();
		this->table.push_back(CIwArray<pair<string, T> >());
	}
	
	
	void clear()
	{
      for(int i = 0; i < (int) this->table.size(); ++i)
      {
         for(int j = 0; j < (int) this->table[i].size(); ++ j)
         {
            //this->table[i][j].clear();
         }
         this->table[i].clear_optimised();
      }
		this->table.clear_optimised();
      this->table.push_back(CIwArray<pair<string, T> >());
	}
	
	
	void insert(pair<string,T> values)
	{
		int hashCode = this->generateIndex(values.first);
		this->table[hashCode].push_back(pair<string, T>(values.first, values.second));
	}
	
	
	T get(string key)
	{
		int hashCode = generateIndex(key);
		
		for (int i = 0; i < (int)this->table[hashCode].size(); ++i)
		{
			if (this->table[hashCode][i].first.compare(key) == 0)
			{
				return this->table[hashCode][i].second;
			}
		}
		return NULL;
	}

	void remove(string key)
	{
		int hashCode = generateIndex(key);

		// if there is a crash here it is because of the delete call
		for (int i = 0; i < (int)this->table[hashCode].size(); ++i)
		{
			if (this->table[hashCode][i].first.compare(key) == 0)
			{
				T temp =  this->table[hashCode][i].second;
				this->table[hashCode].find_and_remove_fast ( this->table[hashCode][i] );
				delete temp;
				return;

			}
		}
		 IwAssertMsg(MYAPP, false, ("Tried to remove %s from hashtable but does not exsist", key));
	}
	
private:
	CIwArray <CIwArray<pair<string, T> > > table; 
	
	
	int generateIndex(string key)
	{
		int hashCode = 0;
		for(string::iterator i = key.begin(); i != key.end(); ++i)
		{
			hashCode += *i;
		}
		return (hashCode)%this->table.size();
	}

	void printHash()
	{

		for (int i = 0; i < (int)this->table.size(); ++i)
		{
			for ( int j = 0; j < (int)this->table[i].size(); ++j)
			{
				
				cout << this->table[i][j].first << endl;

			}
		}


	}
	
	
};

#endif