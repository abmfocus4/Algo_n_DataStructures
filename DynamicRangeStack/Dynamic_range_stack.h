#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations
		
		void enlarge(int *&old_array, int old_size);

	public:
		Dynamic_range_stack( int = 10 );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;
		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	
// Dealocating the memory of the dynamic arrays used
	delete[] stack_array;
	stack_array = nullptr;
	
	delete[] maximum_array;
	maximum_array = nullptr;
	
	delete[] minimum_array;
	minimum_array = nullptr;

}

int Dynamic_range_stack::top() const {
	
	//exception handling:
	//If the stack is empty and top() is called, throw an error
	if(entry_count <= 0)
		throw underflow();
	//Since entry_count is the size of the stack, the topmost element's index would be entry_count-1
	else
		return stack_array[entry_count-1];
}

int Dynamic_range_stack::maximum() const {
	
	//exception handling:
	//If the stack is empty and maximum() is called, throw an error
	if(max_count <= 0)
		throw underflow();
	//Since max count is the num_elements in the max-stack, the topmost element's index would be max_count-1
	else
		return maximum_array[max_count-1];
}

int Dynamic_range_stack::minimum() const {
//exception handling:
	
	//If the stack is empty and minimum() is called, throw an error
	if(min_count <= 0)
		throw underflow();
	//Since min count is the num_elements in the min-stack, the topmost elements index would be min_count-1
	else
		return minimum_array[min_count-1];
}

int Dynamic_range_stack::size() const {
	//returning the size of the stack
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	
	//num_elements in the stack are zero
	if(entry_count == 0)
		return true;
	
	//if the num_elements in the stack is out of the usual range
	else if( (entry_count < 0 )|| (entry_count > current_capacity) )
		throw out_of_bounds();
	
	else
		return false;
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}

//resizing the old_array with double size
void Dynamic_range_stack::enlarge(int *&old_array, int old_size){
	
	//temporary array to store the old arrays values
	int *new_array = new int[old_size*2];
	
	//copying the smaller arrays objects to the new tmp array
	for(int i=0; i<old_size; ++i)
		new_array[i] = old_array[i];
	
	delete[] old_array;
	
	//the old_array is now replaced by the tmp new array
	old_array = new_array;
	
}



void Dynamic_range_stack::push( int const &obj ) {
		
	//When the stack is completely filled to the arrays max capacity
	if(entry_count >= current_capacity)
	{
		enlarge(stack_array, current_capacity);
		enlarge(maximum_array, current_capacity);
		enlarge(minimum_array, current_capacity);
		current_capacity = current_capacity*2;
	}
	
	if(empty()){
		
		// Adding the first object of the stacks
		stack_array[0] = obj;
		
		// Since this is the only object in the stack, it's is both the max and the min object
		maximum_array[0] = obj;
		minimum_array[0] = obj;
		
		//updating the num_elements in the stack
		entry_count++;
		max_count++;
		min_count++;
	}
	
	// if(entry_count+1 <= current_capacity)
	else{
		
		//adding the obj to the top of the stack
		stack_array[entry_count] = obj;
		entry_count++;
		
		//checking for any underflow with max_count
		//comparing maximum element in the max stack with the obj to see if it's the new max element
		if( (max_count != 0) && (obj > maximum_array[max_count-1]) )
		{
			maximum_array[max_count] = obj;
			max_count++;
		}
		
		//checking for any underflow with min_count
		//comparing min element in the min stack with the obj to see if it's the new min element
		if( (min_count != 0) && (obj < minimum_array[min_count-1]) )
		{
			minimum_array[min_count] = obj;
			min_count++;
		}
		
	}
		
		
}

int Dynamic_range_stack::pop() {
	
	//The element on top of the stack
	int popee{0};
	
	//no elements in the stack
	if(entry_count <= 0)
		throw underflow();
	
	//there is atleast 1 element in the stack
	else{
			popee = stack_array[entry_count-1];
			
			//removing the topmost element from the stack
			//updating the num_elements in the stack after pop
			stack_array[entry_count-1] = 0;
			--entry_count;
			
			//checking if the top element of the stack is also the max element
			if( (max_count > 0) && (popee == maximum_array[max_count-1]) )
			{
				maximum_array[max_count-1] = 0;
				--max_count;
			}
			
			//checking if the top element of the stack is also the min element
			if( (min_count > 0) && (popee == minimum_array[min_count-1]) )
			{
				minimum_array[min_count-1] = 0;
				--min_count;
			}
			
	}
	
	return popee;
}

void Dynamic_range_stack::clear() {
	
	//initialising member variables
	entry_count = 0;
	min_count = 0;
	max_count = 0;
	
	//clearing all the stacks and restoring them to their original condition
	if(current_capacity != initial_capacity)
	{
		delete[] stack_array;
		stack_array = nullptr;
	
		delete[] maximum_array;
		maximum_array = nullptr;
	
		delete[] minimum_array;
		minimum_array = nullptr;
		
		current_capacity = initial_capacity;
		
		stack_array = new int[current_capacity];
		maximum_array = new int[current_capacity];
		minimum_array = new int[current_capacity];	
	
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
