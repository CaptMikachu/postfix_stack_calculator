#include "Extended_stack.h"

Extended_stack::Extended_stack()
/*
Pre:  None.
Post: The stack is initialized to be empty.
*/
{
    memset(this->entry, 0, sizeof(this->entry));
    this->count = 0;
}

Error_code Extended_stack::push(const Stack_entry& item)
/*
Pre:  None.
Post: If the Stack is not full, item is added to the top
      of the Stack.  If the Stack is full,
      an Error_code of overflow is returned and the Stack is left unchanged.
*/
{
    Error_code outcome = success;
    if (this->count >= maxstack)
        outcome = overflow;
    else
        this->entry[this->count++] = item;
    return outcome;
}

Error_code Extended_stack::copy_stack_a(Extended_stack& dest, Extended_stack& source)
{
/*
Pre:  None.
Post: Stack dest has become an exact copy of Stack source; source is unchanged.
        If an error is detected, an appropriate code is returned;
        otherwise, a code of success is returned.
*/
    Error_code outcome = success;
    if (!dest.empty() || source.empty()) {
        outcome = fail;
    } else {
        dest = source;
    }
    return outcome;
}

Error_code Extended_stack::copy_stack_b(Extended_stack& dest, Extended_stack& source)
{
/*
Pre:  None.
Post: Stack dest has become an exact copy of Stack source; source is unchanged.
        If an error is detected, an appropriate code is returned;
        otherwise, a code of success is returned.
*/
    Error_code outcome = success;
    if (!dest.empty() || source.empty()) {
        outcome = fail;
    } else {
        Stack_entry item;
        Extended_stack temp_stack;
        while (!source.empty()) {
            source.top(item);
            temp_stack.push(item);
            source.pop();
        }
        while (!temp_stack.empty()) {
            temp_stack.top(item);
            source.push(item);
            dest.push(item);
            temp_stack.pop();
        }
    }
    return outcome;
}

Error_code copy_stack_c(Extended_stack& dest, Extended_stack& source)
{
/*
Pre:  None.
Post: Stack dest has become an exact copy of Stack source; source is unchanged.
        If an error is detected, an appropriate code is returned;
        otherwise, a code of success is returned.
*/
    Error_code outcome = success;
    if (!dest.empty() || source.empty()) {
        outcome = fail;
    } else {
        for (int i = (source.size() - 1); i >= 0; i--) {
            dest.entry[i] = source.entry[i];
            cout << i << endl;
            dest.count++;
        }
    }
    return outcome;
}

Error_code Extended_stack::pop()
/*
Pre:  None.
Post: If the Stack is not empty, the top of
      the Stack is removed.  If the Stack
      is empty, an Error_code of underflow is returned.
*/

{
    Error_code outcome = success;
    if (this->count == 0)
        outcome = underflow;
    else --this->count;
    return outcome;
}

Error_code Extended_stack::top(Stack_entry& item) const
/*
Pre:  None.
Post: If the Stack is not empty, the top of
      the Stack is returned in item.  If the Stack
      is empty an Error_code of underflow is returned.
*/

{
    Error_code outcome = success;
    if (this->count == 0)
        outcome = underflow;
    else
        item = this->entry[this->count - 1];
    return outcome;
}

bool Extended_stack::empty() const
/*
Pre:  None.
Post: If the Stack is empty, true is returned.
      Otherwise false is returned.
*/

{
    bool outcome = true;
    if (this->count > 0) outcome = false;
    return outcome;
}

void Extended_stack::clear()
/*
Pre:  None.
Post: Reset the stack to be empty.
*/
{
    while (!this->empty()) {
        this->pop();
    }
    cout << "The Extended stack has been cleared" << endl;
}

bool Extended_stack::full() const
/*
Pre:  None.
Post: If the stack is full, return true; else return false
*/
{
    if (this->count >= maxstack) {
        return true;
    }
    return false;
}

int Extended_stack::size() const
/*
Pre:  None.
Post: Return the number of entries in the stack.
*/
{
    return this->count;
}
