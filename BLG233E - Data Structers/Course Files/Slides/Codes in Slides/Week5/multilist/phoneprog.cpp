// phoneprog.cpp 
// Defining the operations that we can perform on the phone book

#include <iostream> // allows program to perform input and output
#include <stdlib.h> // contains function prototypes for memory allocation 
#include <iomanip> // function prototypes for stream manipulators that format streams of data, setw() needs this 

#include "list.h" // include implementation of struct List (multilist)

using namespace std; // enables the program to use all the names in any included standard C++ header 

typedef Phone_node Phone_Record; // declares Phone_record as a synonym (alias) for data type Phone_node
typedef List Datastructure; // declares Datastructure as a synonym (alias) for data type List

Datastructure book; // create a DataStructure object named book

// function prototypes
void print_menu();  // prototype for function print_menu
bool perform_operation(char); // prototype for function perform_operation
void search_record(); // prototype for function search_record
void add_record(); // prototype for function add_record
void delete_record(); // prototype for function delete_record
void update_record(); // prototype for function update_record
void clear_list(); // prototype for function clear_list

// function main begins program execution
int main()
{	
	book.create();	
	bool end = false; 
	char choice; 	
	while (!end)
	{ 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
	} 	
	book.close();
	return EXIT_SUCCESS;  // C++ macro that indicates program was executed successfully

}

// print_menu prints the choices to the screen
void print_menu()
{
//	system("clear"); 
	cout << endl << endl;
	cout << "Phone Book Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Record Search" << endl;
	cout << "A: Record Add" << endl;
	cout << "U: Record Update" << endl;
	cout << "D: Record Delete" << endl;	
	cout << "C: Delete All" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {S, A, U, D, C, E} : ";	
}

// perform_operation performs the selected operation and returns terminate
bool perform_operation(char choice)
{
	bool terminate = false;
	switch (choice) { 
		case 'S': case 's': 
			search_record();
			break; 
		case 'A': case 'a': 
			add_record();
			break; 
		case 'U': case 'u': 
			update_record();
			break;
		case 'D': case 'd': 
			delete_record();
			break;
		case 'C': case 'c':
			clear_list();
			break;
		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if ( choice == 'Y' || choice == 'y' )
				terminate = true; 
				break; 
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {S, A, U, D, C, E} :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}

// search_record searches for a record based on the name entered by the user
void search_record()
{
	char name[NAME_LENGTH];
	cout << "Please enter the name of the person you want to search for (press '*' for full list):" << endl;
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
	cin.getline(name, NAME_LENGTH);	// input an entire line of text into character array name	
	if ( book.search(name) == 0 ) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar(); // makes the terminal window wait so that user can see the last output
};

// add_record adds a new record using the name, phone number, and phone type entered by the user
void add_record()
{
	char newname[NAME_LENGTH], newphone[PHONENUM_LENGTH], type[TNAME_LENGTH];
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name : " ;	
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
	cin.getline(newname, NAME_LENGTH); // input an entire line of text into character array name 
	cout << "Phone number :";
	
	// specify that cin should read a maximum of PHONENUM_LENGTH-1 characters into array phonenum
	// and save the last location in the array to store the terminating null character for the string
	// setw stream manipulator applies only to the next value being input
	cin >> setw(PHONENUM_LENGTH) >> newphone; 
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
	
	cout << "Phone type : ";
	cin >> setw(TNAME_LENGTH) >> type;
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream

	book.insert(newname, newphone, type);
	cout << "Record added" << endl;
	getchar();
};

// delete_record deletes a record based on the name entered by the user
void delete_record()
{
	char name[NAME_LENGTH];
	int choice;	
	cout << "Please enter the name of the person whose record you want to delete (press '*' for full list):" << endl;
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
	cin.getline(name, NAME_LENGTH); // input an entire line of text into character array name
	int personcount = book.search(name);
	if (personcount == 0) {
		cout << "Could not find a record matching your search criteria" << endl;		
	}
	else {
		if (personcount == 1) {		
			cout << "Record found." << endl;
			cout << "If you want to delete this record, please enter its number (Enter -1 to exit without performing any operations): " ;
		}
		else {
			cout << "Enter the number of the record you want to delete (Enter -1 to exit without performing any operations): " ;
		}	
		cin >> choice;
		if (choice == -1) return;
		book.remove(choice);	
		cout << "Record deleted" <<endl;	
	}
	getchar();
};

// update_record searches for a record based on the name entered by the user, prompts for new name, and updates the record
void update_record()
{
	char name[NAME_LENGTH];
	int choice;	
	cout << "Please enter the name of the person whose record you want to update (press'*'for full list):" << endl;
	cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
	cin.getline(name, NAME_LENGTH); // input an entire line of text into character array name	
	int personcount = book.search(name); 
	if( personcount == 0 ){
		cout << "Could not find a record matching your search criteria" << endl;		
	}
	else {
		if ( personcount == 1 ){		
			cout << "Record found." << endl;
			cout << "If you want to update this record please enter its number (Enter -1 to exit without performing any operations): " ;
		}
		else {
			cout << "Enter the number of the record you want to update (Enter -1 to exit without performing any operations): " ;
		}

		cin >> choice;
		if ( choice == -1 ) return;

		char newname[NAME_LENGTH]; 
		cout << "Please enter current contact information" << endl;
		cout << "Name : " ;
		cin.ignore(1000, '\n'); // remove the delimiter character from the input stream
		cin.getline(newname, NAME_LENGTH); // input entire line of text into char array name
		book.update(choice, newname);	
		cout << "Record successfully updated" <<endl;		
	}
	getchar();
};

// clear_list empties out the phone book
void clear_list(){
	book.makeEmpty();
}