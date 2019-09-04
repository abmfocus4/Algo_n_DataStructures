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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"
#include <string.h>

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;
		
		
		//own private member function
		
		int index(char letter) const;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

int Trie_node::index(char letter) const{
	int output{};
	
	//if char is upper-case then convert to lower-case
	if(letter >= 'A' && letter <='Z')
		letter += 32;
	
	//then return alpha to num mapping for char
	output = (letter - 'a');
	
	return output;
}

bool Trie_node::member( std::string const &str, int depth ) const {
	
	//Base Case - output depends on the value of is_terminal
	int size = str.length();
	
	if(size == depth){
		return is_terminal;
	}

	// If current character slot is not empty then call member on it	
	bool success{};
	int new_depth = depth+1;
	unsigned int target = index(str[depth]) ;
		
	if( child(target) == nullptr)
		return false;
	else
	{
		success = child(target) -> member(str, new_depth);
	}
	
	return success;
	
}



bool Trie_node::insert( std::string const &str, int depth ) {
	//when the pointer of pointers to children is null, creating a new array of 26 pointers to Trie nodes to children
	if(!(this->children))
	{
		children = new Trie_node*[CHARACTERS];
		
		for(int i=0; i< CHARACTERS; ++i)
			children[i] = nullptr;
	}
	
	//when pointer to the child is null, creating a new instance of node to the sub-tree
	int target = index(str[depth]);
	
	if( child(target) == nullptr)
		children[target] = new Trie_node();
	
	//new depth and is_terminal's value
	int new_depth = depth+1;
	bool end_status = children[target] -> is_terminal;
	int size = str.length();
	bool success{};
	
	//is_terminal determines the return value
	if(size == new_depth && end_status)
		return false;
	//is_terminal value updated
	else if(size == new_depth && !end_status)
		{
			children[target] -> is_terminal = true;
			return true;
		}
	else
		success = children[target] -> insert(str, new_depth);
	
	//return value depends on the success of insert
	return success;

}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {

unsigned int size = str.length();
    
	//is_terminal is updated and children pointers are deallocated
    if (depth == size) {
		is_terminal = false;
        if (children == nullptr) {
			
			delete[] this->children;
			this->children = nullptr;
			ptr_to_this = nullptr;
            delete this;
        }
		
		return true;
    }
 	
int target = index(str[depth]);
int new_depth = depth+1;
bool success{};
   
   //recursively call erase on sub-string with new depth and target
    success = children[target]->erase(str, new_depth , children[target]);
	
	//Means erase was successful
	if(success == true)
		return true;
	
	return false;

}



void Trie_node::clear() {
	
	//deleting all the children of the target node
	if(!(children == nullptr))
	{
		//calling clear on all sub-trees
		for(int i =0; i < CHARACTERS;++i)
		{
			if(this->child(i)){
				this->child(i)->clear();
				delete children[i];
				children[i] = nullptr;
			}
		}
		
		//memory deallocation for this->children
		delete[] this->children;
		this->children = nullptr;
	}
	
	delete [] children;
	children = nullptr;

}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
