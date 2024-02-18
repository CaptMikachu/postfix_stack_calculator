#include <iostream>
#include "Extended_stack.h"
#include <string>
#include <sstream>
#include <cmath>

Extended_stack init_stack();
void printerStack(Extended_stack& s);
void stackReverse(Extended_stack& s1);
bool validateInput(string& input);
void populateNumbers(Extended_stack& numbers, string& input);
bool isNumber(const string& s);
bool isOperator(const string& s);
void doOperation(Extended_stack& numbers, string& input);
void exchangeFixer(Extended_stack& numbers, int position);
void sqrtFixer(Extended_stack& numbers, int position);
string argParser(int argc, char* argv[]);
void instructions();

int main(int argc, char* argv[]) {
	Extended_stack numbers;
	string input = "";
	if (argc > 1 && (string)argv[1] != "-p") {
		input = argParser(argc, argv);
	} else if (argc == 2 && (string)argv[1] == "-p") {
		instructions();
		getline(cin, input);
	} else {
		getline(cin, input);
	}

	if (!validateInput(input)) {
		cout << "Invalid input" << endl;
	} else {
		populateNumbers(numbers, input);
		/* PRINTING FOR DEBUGGING */
		//cout << "-------------INPUT-------------" << endl << input << endl;
		//printer_stack(numbers);
		doOperation(numbers, input);
		cout << endl << "-------------RESULT-------------" << endl;
		printerStack(numbers);
	}
	/* PRINTING FOR DEBUGGING */
	/*
	cout << endl << "-------------ARGUMENTS-------------" << endl;
	cout << "argc: " << argc << endl;
	cout << "argv: " << endl;
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << endl;
	}
	*/
	return EXIT_SUCCESS;
}

void instructions() {
	cout << "This program calculates PostFix expressions." << endl <<
		"All the operators must be separated by a space." << endl;
	cout << "Valid operators are:" << endl <<
		"<+> <-> <*> </> <^>" << endl <<
		"<%> (modulo)" << endl <<
		"<v> (square root)" << endl <<
		"<a> (average)" << endl <<
		"<s> (sum all)" << endl <<
		"<x> (flip latest two)" << endl;
	cout << endl << "Enter the PostFix calculation:" << endl;
}


string argParser(int argc, char* argv[]) {
	string input = "";
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			input += argv[i];
			input += " ";
		}
	}
	return input;
}


bool validateInput(string& input) {
	string temp_str;
	stringstream ss(input); //convert string into string stream
	
	if (input.length() <= 0) {
		return false;
	}
	
	while (getline(ss, temp_str, ' ')) { //use space as delim for cutting string
		if (!isNumber(temp_str)) {
			if (!isOperator(temp_str)) {
				return false;
			}
		}
	}
	return true;
}

void populateNumbers(Extended_stack& numbers, string& input) {
	string temp_str;
	Stack_entry item_s;
	stringstream ss(input); //convert string into string stream

	while (getline(ss, temp_str, ' ')) { //use space as delim for cutting string
		if (isNumber(temp_str)) {
			item_s = stod(temp_str);
			numbers.push(item_s); //convert string to double and push to stack)
		}
	}
	stackReverse(numbers);
}

bool isOperator(const string& s) {
	if (s == "+" || \
		s == "-" || \
		s == "*" || \
		s == "/" || \
		s == "%" || \
		s == "^" || \
		s == "v" || \
		s == "a" || \
		s == "s" || \
		s == "x") {
		return true;
	}
	return false;
}

bool isNumber(const string& s) {
	try {
		double d = stod(s);
		return true;
	}
	catch (const std::invalid_argument&) {
		return false;
	}
	catch (const std::out_of_range&) {
		return false;
	}
}

void doOperation(Extended_stack& numbers, string& input) {
	Stack_entry result = 0, num1 = 0, num2 = 0, count = 0, total = 0;
	int position = 0;
	string temp_str = "";
	Extended_stack temp;
	stringstream ss(input); //convert string into string stream

	while (getline(ss, temp_str, ' ')) { //use space as delim for cutting string
		if (!isOperator(temp_str)) {
			++position;
		} else {
			if (temp_str[0] == 'x') {
				// if there are less than 2 numbers, there is no need to exchange
				if (numbers.size() > 1 && position > 1) {
				exchangeFixer(numbers, position); // logic for exchange here
				/* PRINTING FOR DEBUGGING */
				//cout << endl << "-------------EXCHANGED-------------" << endl;
				//printer_stack(numbers); // print the stack after exchanges
				}
			} else if (temp_str[0] == 'a') {
				while (position > 0) {
					numbers.top(num1);
					numbers.pop();
					total += num1;
					++count;
					--position; 
				}
				result = total / count;
				numbers.push(result);
				++position; // reset the position to 1
			} else {
				while (position > 1 && !temp_str.empty()) { // if there are more than 1 number in the stack
					numbers.top(num1);
					numbers.pop();
					numbers.top(num2);
					numbers.pop();

					switch (temp_str[0]) {
						case '+':
							result = num1 + num2;
							numbers.push(result);
							break;
						case '-':
							result = num1 - num2;
							numbers.push(result);
							break;
						case '*':
							result = num1 * num2;
							numbers.push(result);
							break;
						case '/':
							if (num2 == 0) {
								cout << "Cannot divide by 0" << endl;
								++position; // counter the --position below
								temp_str = ""; // to prevent infinite looping this case
								numbers.push(num2);
								numbers.push(num1);
							} else {
								result = num1 / num2;
								numbers.push(result);
							}
							break;
						case '%':
							result = fmod(num1, num2); // fmod for doubles, % for ints
							numbers.push(result);
							break;
						case '^':
							result = pow(num1, num2);
							numbers.push(result);
							break;
						case 'v':
							numbers.push(num2);
							numbers.push(num1);
							// calculate the square root of previous number
							sqrtFixer(numbers, position);
							/* PRINTING FOR DEBUGGING */
							//cout << endl << "-------------SQRT'd-------------" << endl;
							//printer_stack(numbers); // print the stack after exchanges
							temp_str = ""; // prevent from infinite looping this case
							++position; // counter the --position below
							break;
						case 's':
							result = num1 + num2;
							numbers.push(result);
							break;
						case 'a':
							result = num1 + num2;
							numbers.push(result);
							++count;
							break;
					}
					--position;
					
				}
				if (position == 1 && temp_str[0] == 'v') {
					sqrtFixer(numbers, position);
				}
			}
		}
	}
}

void exchangeFixer(Extended_stack& numbers, int position) {
	Extended_stack temp;
	Stack_entry num1 = 0, num2 = 0;
		int x_position = numbers.size() - position; // get the position of the x
		while (!numbers.empty()) { // move all the numbers to a temp stack
			numbers.top(num1);
			numbers.pop();
			temp.push(num1);
		}
		// move the numbers back to the original stack until the x-position
		for (int i = 0; i < x_position; ++i) {
			temp.top(num1);
			temp.pop();
			numbers.push(num1);
		}
		temp.top(num1);
		temp.pop();
		temp.top(num2);
		temp.pop();
		// exchange the numbers with each other
		numbers.push(num2);
		numbers.push(num1);
		while (!temp.empty()) { // move the rest of the numbers back to the original stack
			temp.top(num1);
			temp.pop();
			numbers.push(num1);
		}
}

void sqrtFixer(Extended_stack& numbers, int position) {
	Extended_stack temp;
	Stack_entry num1 = 0;
	int v_position = numbers.size() - position; // get the position of the x
	while (!numbers.empty()) { // move all the numbers to a temp stack
		numbers.top(num1);
		numbers.pop();
		temp.push(num1);
	}
	// move the numbers back to the original stack until the v-position
	for (int i = 0; i < v_position; ++i) {
		temp.top(num1);
		temp.pop();
		numbers.push(num1);
	}
	temp.top(num1);
	temp.pop();
	if (num1 < 0) {
		cout << "Cannot square root a negative number" << endl;
		numbers.push(num1);
	}
	else {
		num1 = sqrt(num1);
	}
	numbers.push(num1);
	while (!temp.empty()) { // move the rest of the numbers back to the original stack
		temp.top(num1);
		temp.pop();
		numbers.push(num1);
	}
}


Extended_stack init_stack()
{
	Extended_stack s;
	for (int i = 1; i <= 10; ++i) {
		s.push(i);
	}
	return s;
}


void printerStack(Extended_stack& s) {
	Extended_stack s_temp = s;
	Stack_entry item_s;

	//cout << endl << "-------------STACK-------------" << endl;
	while (!s_temp.empty()) {
		s_temp.top(item_s);
		s_temp.pop();
		std::cout << item_s << " ";
	}
	cout << endl;
}

void stackReverse(Extended_stack& s1) {
	Extended_stack temp_s1, temp_s2;
	Stack_entry item_s;

	while (!s1.empty()) {
		s1.top(item_s);
		s1.pop();
		temp_s1.push(item_s);
	}
	while (!temp_s1.empty()) {
		temp_s1.top(item_s);
		temp_s1.pop();
		temp_s2.push(item_s);
	}
	while (!temp_s2.empty()) {
		temp_s2.top(item_s);
		temp_s2.pop();
		s1.push(item_s);
	}
}