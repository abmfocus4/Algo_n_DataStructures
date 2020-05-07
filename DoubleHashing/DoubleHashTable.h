#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  bmalapat
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;
		
		
		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {

//dealocating both the arrays
	delete[] array;
	array = nullptr;
	
	delete[] array_state;
	array_state = nullptr;
	
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	
	if(count <= 0)
		return true;
	else
		return false;
	
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	
	int h1_result = static_cast<int>(obj);
	h1_result = (int)(h1_result % array_size);

//adding M to ensure that h1_result is positive
	if(h1_result < 0)
		return (h1_result + array_size);
	else
		return h1_result;
	
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	
	int h2_result = static_cast<int>(obj);
	// typecasting after div or mod unsure(syntax)?
	h2_result = (int)( (h2_result/array_size) % array_size);
	
	if(h2_result<0)
		h2_result += array_size;
	
	//add 1 to make result odd if even when nessesary
	//trying to remain closest to SUH
	//h2(k) should be relative prime to array_size
	
	//if array size is a power of 2 then returning h2 odd
	//if array_size and h2 are even adding 1
	if(!(array_size%2) && !(h2_result%2) )
		h2_result+=1;

	return h2_result;
}

// double hashing does not use linked list but the sequence of probes can be thought of as one
// Deleting an element of that sequence is equivalent to breaking the chain
// So here we are continuing our search even if the actual bin does not have a value stored by it's status is DELETED

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	
	if(empty())
		return false;

	int probe = h1(obj);
	int offset = h2(obj);

	int ref = h1(obj);
	int max_iter = 0;
	
	while((array[probe] != obj && array_state[probe] ==OCCUPIED)|| array_state[probe] == DELETED){
		
	if(array[probe] == obj)
	return true;

	probe = (probe + offset)%array_size;
	
	if(	probe == ref )
		max_iter++;
	
	if(max_iter >= 2)
		break;
	
}

if(array[probe] == obj)
	return true;
else if(array[probe] != obj && (array_state[probe] == EMPTY))
	return false;
else
	return false;


}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	//element not found - empty table
	if(empty())
		std::cerr << n << " is empty and so is the hash table!" << std::endl;
	
	if(array_state[n] == OCCUPIED)
		return array[n];
	//bin_status is empty or deleted
	else if(array_state[n] == DELETED || array_state[n] == EMPTY)
		std::cerr << n << " is empty!" << std::endl;
	else
		std::cerr << n << " is not occupied!" << std::endl;

}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {

if(count == array_size)
	throw overflow();

int probe = h1(obj);
int offset = h2(obj);

while(array_state[probe] == OCCUPIED)
	probe = (probe + offset)%array_size;

array[probe] = obj;
array_state[probe] = OCCUPIED;
count++;

}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	
int probe = h1(obj);
int offset = h2(obj);

	// IF TABLE IS EMPTY OR ELEMENT IS NOT IN THE TABLE
	if( empty() || !(member(obj)) ) {
		return false;
	}
	//NOW THAT ELEMENT IS IN THE TABLE...
	else
	{
		while((array[probe] != obj) && (array_state[probe] == OCCUPIED)|| array_state[probe] == DELETED)
		{
			probe = (probe + offset)%array_size;
		}
		
		if(array[probe] == obj && array_state[probe] == OCCUPIED)
		{
			array[probe] = 0;
			array_state[probe] = DELETED;
			--count;
			
			return true;

		}
		
		else
			return false;
		
	}
	
	return false;
	
}

template<typename T >
void DoubleHashTable<T >::clear() {

for(int i=0; i<array_size; ++i)
{
	array[i] = 0;
	array_state[i] = DELETED;
}

count = 0;

}

//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
	for(int i=0; i<array_size; ++i)
		std::cout << array[i] << std::endl;
}

#endif
