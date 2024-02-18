#pragma once
#include "Utility.h"
typedef double Stack_entry;
const int maxstack = 100;

class Extended_stack {
public:
	Extended_stack();
	Error_code pop();
	Error_code top(Stack_entry& item) const;
	Error_code push(const Stack_entry& item);
	Error_code copy_stack_a(Extended_stack& dest, Extended_stack& source);
	Error_code copy_stack_b(Extended_stack& dest, Extended_stack& source);
	friend Error_code copy_stack_c(Extended_stack& dest, Extended_stack& source);
	bool empty() const;
	void clear(); // Reset the stack to be empty
	bool full() const; // If the stack is full, return true; else return false
	int size() const; // Return the number of entries in the stack

private:
	int count;
	Stack_entry entry[maxstack];
};