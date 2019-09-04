/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bmalapat @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>
#include <string.h>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;
		
		//own private member function
		bool illegal_arg(std::string const &) const;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	//if tree is not empty, call clear until it is
	if(root_node != nullptr)
		clear();
	
	//deallocating mem
	delete root_node;
	root_node = nullptr;
	
	//resetting variables
	trie_size = 0;
}

bool Trie::illegal_arg(std::string const &str) const{
	
	bool output = false;
	int size = str.length();
	
	//exception handling
	for(int i=0; i < size; ++i){
		if( !isalpha(str[i]) )
			output= true;	
	}

return output;

}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if(trie_size == 0)
		return true;
	
	return false;
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {

	if(illegal_arg(str))
		throw illegal_argument();
	
	//tree is empty
	if(root_node == nullptr)
		return false;
	
	//calling member from node.h file recursively
	bool success = root_node -> member(str,0);
	
	return success;
		
	}

bool Trie::insert( std::string const &str ) {
	
	//exception handling
	if(illegal_arg(str))
		throw illegal_argument();
	
	//if Tree is empty we create a new instance of Trie_node class
	if(root_node == nullptr)
		root_node = new Trie_node();
	
	bool success{};
	//if insertion is successful then we increase the size of the tree and return true
	success = root_node -> insert(str,0);
	
	if(success)
	{
		trie_size+=1;
		return true;
	}
	
	//insertion was unsuccessful
	else
		return false;
}

bool Trie::erase( std::string const &str ) {
	
	//exception handling
	if(illegal_arg(str))
		throw illegal_argument();
	
	//if str in not in the tree or the tree doesn't have any strings
	if((trie_size == 0) || (!member(str)) )
		return false;
	
	bool success{};
	//call to the erase func() in the trie_node class
	success = root_node -> erase(str,0,root_node);
	
	//deleting the node if the last element of the tree is erased
	if(trie_size == 1)
	{
		root_node -> clear();
		delete root_node;
		root_node = nullptr;
		
	}
	
	if(success)
	{
		--trie_size;
		return true;
	}
	 
	//erase was unsuccessful
	else
	return false;
	
}

void Trie::clear() {
	
	//recursively call clear on all the nodes
	if(root_node != nullptr)
		root_node -> clear();

	//memory deallocation
	delete root_node;
	root_node = nullptr;
	
	//resetting variables
	trie_size = 0;
	
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
