
/****************************************************
 * Create an instance of the Dynamic_range_stack<int> class
 * and call the member function run().
 *
 * The member function run() will interpret the
 * input appropriately and exit when the interpreter
 * receives either the command 'exit' or and
 * end-of-file.
 ****************************************************/

#include <iostream>
#include "Dynamic_range_stack_tester.h"

int main() {
	Dynamic_range_stack_tester tester;

	std::cout << "Starting Test Run" << std::endl;

	tester.run();

	std::cout << "Finishing Test Run" << std::endl;

	return 0;
}
