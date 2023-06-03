#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <array>
#include <iomanip>
using namespace std;

// Grouping book details
struct Book
{
	string title;
	string isbn;
	string author;
	string publisher;
	int publish_year;
	int edition;
	int quantity;
	double wholeSaleCost;
	double retailCost;
};

//Grouping cashier details
struct Cashier
{
	int id;
	int bookQuantity;
	float unitPrice;
	string bookIsbn;
	string bookTitle;
	string date;	
};
		
//Array Sizes
const int ARRAY_SIZE = 100;
const int CASHIER_SIZE = 50;

// Book Array
Book bookInfo [ARRAY_SIZE];

//Cashier Array
Cashier cashierInfo [CASHIER_SIZE];

//Available spaces
int bookSpace = 0;

// Function prototypes
void mainMenu ();
void bookDatabase ();
void searchBook ();
void addBook ();
void editBook();
void deleteBook ();
void readFromFile();
void runCashierModule();
void backUpRecords ();

// Main output
int main ()
{
	// Declarations
	int select;
	char quit = 'N';
	
	readFromFile();	

	
	//Start of program
	do
	{
		mainMenu ();
		
	} while (quit == 'N' || quit == 'n'); // Terminate program if quit == n or n
	
	return 0;
}


// Defining functions

void mainMenu ()
{		
	//Delcaration
	int mainSelect = 0 ;
	char quit = 'N';
		

	do
	{
		// Displaying main menu
		cout << "	INTI Smart Book Store" << endl;
		cout << "	     Main Menu       " << endl;
		cout << "1. Cashier              " << endl;
		cout << "2. Book Database        " << endl;
		cout << "3. Export Book Records  " << endl;
		cout << "4. Exit                 " << endl<<endl;
		
		cout << "Enter your choice: ";
		cin >> mainSelect;
		// Menu functions
		switch (mainSelect)
		{
			case 1 :
				runCashierModule();
				break;
			
			case 2 :
				bookDatabase ();
				break;
					
			case 3 :
				backUpRecords ();
				break;
						
			case 4 :		
				cout << "Program terminated..." << endl;
				cout << "Have a nice day!" << endl << endl;
				exit (0);
				break;
					
			default :
				cout << "Please enter number from 1 to 4." << endl << endl;
		}
	} while (mainSelect != 4);
	
}


//Cashier Option
void runCashierModule()
{
	//declaration
	char continueRun = 'Y';
	int currentId = 1000;
	int cashierSpace = 0;
	float accumulateSubTotal = 0;
	float accumulateTax = 0;
	float accumulateTotal = 0;
	
	//Input of data from array
	ofstream bookInfoOutput;
	
	//Output of cashierId
	ifstream cashierIdInput;
	ofstream cashierIdOutput;
	
	cashierIdInput.open ("cashier_ID.txt", ifstream::app);
	cashierIdOutput.open ("cashier_ID.txt", ofstream::app);
				
	cout << endl;
	cout << "     Study Smart Book Store" << endl;
	cout << "        Cashier Module" << endl << endl;
	
	do
	{
		if (cashierSpace == 50 || accumulateTotal >= 2000)
		{
			cout << "Already entered 50 books! Now proceed to the receipt." << endl;	
			break;
		}
		
		else
		{
			cashierIdInput >> currentId; //open cashier id from the file
			
			cashierInfo[cashierSpace].id = currentId;
			++currentId; //counting the current cashier id
					
			//Enter cashier information
			cin.ignore();
			
			cout << "Enter date [MM/DD/YY]: ";
			getline(cin, cashierInfo[cashierSpace].date);
			
			cout << "Enter quantity: ";
			cin >> cashierInfo[cashierSpace].bookQuantity;
			cin.get();
			
			cout << "Enter ISBN: ";
			getline(cin, cashierInfo[cashierSpace].bookIsbn);
			
			cout << "Enter book title: ";
			getline(cin, cashierInfo[cashierSpace].bookTitle);
			
			cout << "Enter unit price: ";
			cin >> cashierInfo[cashierSpace].unitPrice;
			cin.get();
			
			cout << endl << endl;
			
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				
				if (cashierInfo[cashierSpace].bookTitle == bookInfo[i].title || cashierInfo[cashierSpace].bookIsbn == bookInfo[i].isbn)
				{	
					cashierInfo[cashierSpace].bookIsbn = bookInfo[i].isbn;
					cashierInfo[cashierSpace].bookTitle = bookInfo[i].title;
					cashierInfo[cashierSpace].unitPrice = bookInfo[i].retailCost;
					
					//Print cashier information
					cout << "Order ID: " << currentId << endl;
					cout << "Date: " << cashierInfo[cashierSpace].date << endl;
					cout << "ISBN: " << cashierInfo[cashierSpace].bookIsbn << endl;
					cout << "Title: " << cashierInfo[cashierSpace].bookTitle << endl;
					cout << "Quantity of Book: " << cashierInfo[cashierSpace].bookQuantity << endl;
					cout << "Price: $ " << cashierInfo[cashierSpace].unitPrice << endl << endl;
					
					if (cashierInfo[cashierSpace].bookQuantity > bookInfo[i].quantity)
					{
						cout << "Book quantity is not enough." << endl << endl;
					}
					else
					{
						bookInfo[i].quantity = bookInfo[i].quantity - cashierInfo[cashierSpace].bookQuantity;
						// Input and output of the file
						bookInfoOutput.open ("Book_Record.txt");
						bookInfoOutput << endl;
						for (int x = 0; x < bookSpace; x++)
						{
							bookInfoOutput << bookInfo[x].title << "\n"
							<< bookInfo[x].isbn << "\n"
							<< bookInfo[x].author << "\n"
							<< bookInfo[x].publisher << "\n"
							<< bookInfo[x].publish_year << "\n"
							<< bookInfo[x].edition << "\n"
							<< bookInfo[x].quantity << "\n"
							<< bookInfo[x].wholeSaleCost << "\n"
							<< bookInfo[x].retailCost << "\n";
						
						}
						
						bookInfoOutput.close();
					}
					
					//calculate total price for the books
					accumulateSubTotal = accumulateSubTotal + (cashierInfo[cashierSpace].unitPrice * cashierInfo[cashierSpace].bookQuantity);
					accumulateTax = accumulateSubTotal * 0.06;
					accumulateTotal = accumulateTax + accumulateSubTotal;
					cout << "Accumulate total price for the books: $" << fixed << showpoint << setprecision(2) << accumulateTotal << endl << endl;
					
					cashierSpace = cashierSpace + 1;
					break;
				}
			}		
		}
		
		//Calculate and print the prices
		cout << left << setw (22) << " " ;
		cout << left << setw (18) << "Study Smart Book Store" << endl << endl;
		cout << left << setw (6) << "Date: " << left << setw(43) << cashierInfo[cashierSpace - 1].date;
		cout << left << setw (10) << "Order ID: " << left << setw(20) << currentId << endl << endl;
		cout << left << setw (5) << "Qty";
		cout << left << setw (19) << "ISBN";
		cout << left << setw (35) << "Title";
		cout << left << setw (10) << "Price";
		cout << left << setw (10) << "Total" << endl;
			
		for (int j = 0 ; j < cashierSpace; j++)
		{
			cout << left << setw (5) << cashierInfo[j].bookQuantity;
			cout << left << setw (19) << cashierInfo[j].bookIsbn;
			cout << left << setw (35) << cashierInfo[j].bookTitle;
			cout << left << setw (10) << fixed << showpoint << setprecision(2) << cashierInfo[j].unitPrice  ;
			cout << left << setw (10) << fixed << showpoint << setprecision(2) << (cashierInfo[j].unitPrice * cashierInfo[j].bookQuantity) << endl << endl << endl;	
		}
				
		cout << left << setw (45) << " " << left << setw (14) << "Sub Total" << right << setw (8) <<  " $ " << fixed << showpoint << setprecision (2) << accumulateSubTotal << endl;
		cout << left << setw (45) << " " << left << setw (14) << "Tax" << right << setw (8) << " $ " << fixed << showpoint << setprecision (2) << accumulateTax << endl;
		cout << left << setw (45) << " " << left << setw (14) << "Total" << right << setw (8) << " $ " << fixed << showpoint << setprecision (2) << accumulateTotal << endl;
		
		
		cashierIdOutput << currentId; //Record ID for next program use
		cashierIdOutput.close();
		
		//Ask whether to continue on next book or not
		cout << "Continue next book? [Y/N]: ";
		cin >> continueRun;	
		
	} while (continueRun == 'Y'|| continueRun == 'y');
		
}
					
// book database (submenu)
void bookDatabase ()
{	
	// declarations
	int subSelect;
	
	do 
	{
		//Declaration 
		int subSelect = 0 ;
		
		// submenu
		cout << "\n	INTI Smart Book Store " << endl;
		cout << "          Inventory Database   " << endl;
		
		cout << "1. Search Book            " << endl;
		cout << "2. Add Book               " << endl;
		cout << "3. Edit Book              " << endl;
		cout << "4. Delete Book            " << endl;
		cout << "5. Return to the Main Menu" << endl << endl;
		
		//Selection
		cout << "Enter Your Choice: ";
		cin >> subSelect;
		cin.get();
		
		switch (subSelect)
		{
			case 1:
				searchBook();
				break;
				
			case 2:
				addBook();
				break;
				
			case 3:
				editBook();
				break;
				
			case 4:
				deleteBook();
				break;
				
			case 5:
				cout << "Returning to main menu..." << endl << endl;
				mainMenu ();
				
			default :
				cout << "Please enter number from 1 to 4." << endl << endl;
		}
		
	} while (subSelect != 5);
	
}

// Search book
void searchBook ()
{			
	//Delcaration
	string key;
	bool isFound = false;
	
	// Tell user to input search keywords
	cout << "Search the book by typing in the title or ISBN of the book: " << endl;
	getline (cin , key );
	
	//Start search by looping through array
	for (int i=0 ; i < 100 ; i++)
	{
		if (bookInfo[i].title == key || bookInfo[i].isbn == key) //If a search is found
		{
			cout << "The search is success. The book info as below: "<< endl << endl;
			//cout << bookInfoOutput << bookInfo[i] << endl <<endl;
			cout << "1. Book Title: " << bookInfo[i].title << endl;
			cout << "2. ISBN: " << bookInfo[i].isbn << endl;
			cout << "3. Author Name: " << bookInfo[i].author << endl;
			cout << "4. Publisher: " << bookInfo[i].publisher << endl;
			cout << "5. Date of Publish: " << bookInfo[i].publish_year << endl;
			cout << "6. Edition: " << bookInfo[i].edition << endl;
			cout << "7. Quantity: " << bookInfo[i].quantity << endl;
			cout << "8. Wholesale Cost: " << bookInfo[i].wholeSaleCost << endl;
			cout << "9. Retail Cost: " << bookInfo[i].retailCost << endl;
			
			isFound = true;
			break; // Stop the for loop
		}
	}
	
	if (isFound == false){
		cout << "The book you searched for is not in the database." << endl;
	}
	
	
}

// Add book
void addBook ()
{
	//Input and output of data from array
	ofstream bookInfoOutput ;
	
	// Input and output of the file
	bookInfoOutput.open ("Book_Record.txt", ios_base::app);
	
	cout << "****** ADD NEW BOOK ******" << endl << endl;
	if (bookSpace < 100){
		//Enter Book Information
		cout << "Enter Book Title: ";
		getline(cin, bookInfo[bookSpace].title);
	
		cout << "Enter ISBN: ";
		getline(cin, bookInfo[bookSpace].isbn);
		
		cout << "Enter Author Name: ";
		getline(cin, bookInfo[bookSpace].author);
		
		cout << "Enter Publisher: ";
		getline(cin, bookInfo[bookSpace].publisher);
		
		cout << "Enter Date of Publish: ";
		cin >> bookInfo[bookSpace].publish_year;
		cin.get();
		
		cout << "Enter Edition: ";
		cin >> bookInfo[bookSpace].edition;
		cin.get();
		
		cout << "Enter Quantity: ";
		cin >> bookInfo[bookSpace].quantity;
		cin.get();
		
		cout << "Enter Wholesale Cost: ";
		cin >> bookInfo[bookSpace].wholeSaleCost;
		cin.get();
		
		cout << "Enter Retail Cost: ";
		cin >> bookInfo[bookSpace].retailCost;
		cin.get();
		
		bookInfoOutput << bookInfo[bookSpace].title << "\n"
			<< bookInfo[bookSpace].isbn << "\n"
			<< bookInfo[bookSpace].author << "\n"
			<< bookInfo[bookSpace].publisher << "\n"
			<< bookInfo[bookSpace].publish_year << "\n"
			<< bookInfo[bookSpace].edition << "\n"
			<< bookInfo[bookSpace].quantity << "\n"
			<< bookInfo[bookSpace].wholeSaleCost << "\n"
			<< bookInfo[bookSpace].retailCost << "\n";
		
		bookInfoOutput.close();
		
		bookSpace = bookSpace + 1;
	}
	else{
		cout << "No more space available! Delete books to add more space." << endl;
	}
	
	
}

//Edit book
void editBook(){
	
	//Declaration
	int infoNum = 0;
	int indexOfBook = 0;
	bool isFound = false;
	char continueEdit;
	string key;
	
	//Input of data from array
	ofstream bookInfoOutput;

	cout << "****** EDIT BOOK ******" << endl << endl;
	
	// Tell user to input search keywords
	cout << "Please enter the title of the book that you want to edit:  " << endl;
	getline (cin , key );
	
	//Start search by looping through array
	for (int i=0 ; i < ARRAY_SIZE ; i++)
	{

		if (bookInfo[i].title == key || bookInfo[i].isbn == key) //If a search is found
		{
			cout << "The search is success. The book info as below: "<< endl;
			//cout << bookInfoOutput << bookInfo[i] << endl <<endl;
			cout << "1. Book Title: " << bookInfo[i].title << endl;
			cout << "2. ISBN: " << bookInfo[i].isbn << endl;
			cout << "3. Author Name: " << bookInfo[i].author << endl;
			cout << "4. Publisher: " << bookInfo[i].publisher << endl;
			cout << "5. Date of Publish: " << bookInfo[i].publish_year << endl;
			cout << "6. Edition: " << bookInfo[i].edition << endl;
			cout << "7. Quantity: " << bookInfo[i].quantity << endl;
			cout << "8. Wholesale Cost: " << bookInfo[i].wholeSaleCost << endl;
			cout << "9. Retail Cost: " << bookInfo[i].retailCost << endl;
			
			
			indexOfBook = i;
			isFound = true;
			break; // Stop the for loop
		}
	}
	
	if (isFound == false){
		cout << "The book you searched for is not in the database." << endl;
	}
	else{
		//Ask user to choose an information to edit
	
		do {
			cout << "Choose information to edit (e.g. 2): ";
			cin >> infoNum;
			cin.get();
			
			switch(infoNum){
				case 1:
					cout << "Enter new book title: ";
					getline(cin, bookInfo[indexOfBook].title);
					break;
				case 2:
					cout << "Enter new ISBN: ";
					getline(cin, bookInfo[indexOfBook].isbn);
					break;
				case 3:
					cout << "Enter new author name: ";
					getline(cin, bookInfo[indexOfBook].author);
					break;
				case 4:
					cout << "Enter new publisher: ";
					getline(cin, bookInfo[indexOfBook].publisher);
					break;
				case 5:
					cout << "Enter new year of publish: ";
					cin >> bookInfo[indexOfBook].publish_year;
					cin.get();
					break;
				case 6:
					cout << "Enter new edition: ";
					cin >> bookInfo[indexOfBook].edition;
					cin.get();
					break;
				case 7:
					cout << "Enter new quantity: ";
					cin >> bookInfo[indexOfBook].quantity;
					cin.get();
					break;
				case 8:
					cout << "Enter new whole sale cost: ";
					cin >> bookInfo[indexOfBook].wholeSaleCost;
					cin.get();
					break;
				case 9:
					cout << "Enter new retail cost: ";
					cin >> bookInfo[indexOfBook].retailCost;
					cin.get();
					break;
				default:
					cout << "Information not found in the database!" << endl;
			}
			
			//Ask user if they want to continue editing
			cout << "Continue editing? [Y/N]: ";
			cin >> continueEdit;	
		} while(continueEdit !='N');
		
		
		// Input and output of the file
		bookInfoOutput.open ("Book_Record.txt");
		bookInfoOutput << endl;
		for (int x = 0; x < bookSpace; x++)
		{
			bookInfoOutput << bookInfo[x].title << "\n"
			<< bookInfo[x].isbn << "\n"
			<< bookInfo[x].author << "\n"
			<< bookInfo[x].publisher << "\n"
			<< bookInfo[x].publish_year << "\n"
			<< bookInfo[x].edition << "\n"
			<< bookInfo[x].quantity << "\n"
			<< bookInfo[x].wholeSaleCost << "\n"
			<< bookInfo[x].retailCost << "\n";
		
		}
		
		bookInfoOutput.close();
	
	}
	
	
}

// Delete Book
void deleteBook ()
{
	//Declaration
	int infoNum = 0;
	int indexOfBook = 0;
	bool isFound = false;
	char confirmDelete;
	string key;
	
	//Input of data from array
	ofstream bookInfoOutput;
	
	cout << "****** DELETE BOOK ******" << endl << endl;
	
	// Tell user to input search keywords
	cout << "Please enter the title of the book that you want to delete:  " << endl;
	getline (cin , key );
	
	//Start search by looping through array
	for (int i=0 ; i < ARRAY_SIZE ; i++)
	{
		if (bookInfo[i].title == key || bookInfo[i].isbn == key) //If a search is found
		{
			cout << "The search is success. The book info as below: "<< endl;
			//cout << bookInfoOutput << bookInfo[i] << endl <<endl;
			cout << "1. Book Title: " << bookInfo[i].title << endl;
			cout << "2. ISBN: " << bookInfo[i].isbn << endl;
			cout << "3. Author Name: " << bookInfo[i].author << endl;
			cout << "4. Publisher: " << bookInfo[i].publisher << endl;
			cout << "5. Date of Publish: " << bookInfo[i].publish_year << endl;
			cout << "6. Edition: " << bookInfo[i].edition << endl;
			cout << "7. Quantity: " << bookInfo[i].quantity << endl;
			cout << "8. Wholesale Cost: " << bookInfo[i].wholeSaleCost << endl;
			cout << "9. Retail Cost: " << bookInfo[i].retailCost << endl;
			
			indexOfBook = i;
			isFound = true;
			break; // Stop the for loop
		}
	}
	
	if (isFound == false)
	{
		cout << "\n The book you searched for is not in the database." << endl;
	}
	else 
	{
		//Ask user if they want to delete the book information
		cout << "\n Are you sure you want to delete the record? [Y/N]: ";
		cin >> confirmDelete;	
		
		if (confirmDelete == 'Y' || confirmDelete == 'y')
		{
			for (int j = indexOfBook; j < bookSpace-1; ++j)
			{
				bookInfo[j].title = bookInfo[j+1].title;
				bookInfo[j].isbn = bookInfo[j+1].isbn;
				bookInfo[j].author = bookInfo[j+1].author;
				bookInfo[j].publisher = bookInfo[j+1].publisher;
				bookInfo[j].publish_year = bookInfo[j+1].publish_year;
				bookInfo[j].edition = bookInfo[j+1].edition;
				bookInfo[j].quantity = bookInfo[j+1].quantity;
				bookInfo[j].wholeSaleCost = bookInfo[j+1].wholeSaleCost;
				bookInfo[j].retailCost = bookInfo[j+1].retailCost;
			}
			
			bookSpace--;
			
			// Input and output of the file
			bookInfoOutput.open ("Book_Record.txt");
			bookInfoOutput << endl;
			for (int x = 0; x < bookSpace; x++)
			{
				bookInfoOutput << bookInfo[x].title << "\n"
				<< bookInfo[x].isbn << "\n"
				<< bookInfo[x].author << "\n"
				<< bookInfo[x].publisher << "\n"
				<< bookInfo[x].publish_year << "\n"
				<< bookInfo[x].edition << "\n"
				<< bookInfo[x].quantity << "\n"
				<< bookInfo[x].wholeSaleCost << "\n"
				<< bookInfo[x].retailCost << "\n";
			
			}
			
			bookInfoOutput.close();
			
		}
		else if (confirmDelete == 'N' || confirmDelete == 'n')
		{
			cout << "Returning to main menu..." << endl << endl;
			mainMenu ();
		}
	} 	
}

//Open Book_Record.txt
void readFromFile()
{
	//Open file
	ifstream bookInfoInput;
	
	bookInfoInput.open("Book_Record.txt");
	
	//Declare variables
	string line;
	string title, isbn, author, publisher;
	int publish_year, edition, quantity;
	double wholeSaleCost, retailCost;
	
	if (bookInfoInput.fail())
	{
		cout << "Error" << endl;
		exit(1);
	}
	
	//Restore saved book from text file
	int i = 0;
	while(getline(bookInfoInput, line))
	{
		getline(bookInfoInput, title);
		getline(bookInfoInput, isbn);
		getline(bookInfoInput, author);
		getline(bookInfoInput, publisher);
		bookInfoInput >> publish_year >> edition >> quantity >>wholeSaleCost
		>> retailCost;
		
		
		bookInfo[i].title = title;
		bookInfo[i].isbn = isbn;
		bookInfo[i].author = author;
		bookInfo[i].publisher = publisher;
		bookInfo[i].publish_year = publish_year;
		bookInfo[i].edition = edition;
		bookInfo[i].quantity = quantity;
		bookInfo[i].wholeSaleCost = wholeSaleCost;
		bookInfo[i].retailCost = retailCost;
		
		i++;
	}
	
	//Update used array space
	bookSpace = i - 1;
	
}

void backUpRecords ()
{
	//Input and Output of folders
	ofstream bookBackupOutput;
	
	cin.ignore() ;
	
	bookBackupOutput.open ("Book_Record_Backup.html", ios::out);
	
	//give notification if fail to back up the record
	if (!bookBackupOutput)
	{
		cout << "Unable to create back-up file! :(" << endl << endl; 
		return;
	}
	
	//Html header
	bookBackupOutput << "<!DOCTYPE html>\n";
	bookBackupOutput << "<html>\n";
	bookBackupOutput << "<head><title> INTI Smart Book Store Book Record Backup</title></head>\n";
	bookBackupOutput << "<body>\n \n";
	
	//Table for recording the records
	bookBackupOutput << "<table border=\"1\" align = \"center\">\n";
  	bookBackupOutput << "<tr> \n"
	  			   "<th>Title</th>\n"
				   "<th>ISBN</th> \n"
				   "<th>Author</th> \n"
				   "<th>Publisher</th> \n"
				   "<th>Publish Year</th> \n"
				   "<th>Edition</th> \n"
				   "<th>Quantity</th> \n"
				   "<th>Whole Sale Cost</th> \n"
				   "<th>Retail Cost</th> \n"
				   "</tr>\n \n";
	
	for (int i = 0 ; i < bookSpace; i++) 
	{
            //Create rows
            bookBackupOutput << "<tr>\n";
            bookBackupOutput << "<td> " << bookInfo[i].title << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].isbn << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].author << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].publisher << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].publish_year << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].edition << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].quantity << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].wholeSaleCost << "</td>\n";
            bookBackupOutput << "<td> " << bookInfo[i].retailCost << "</td>\n";
            bookBackupOutput << "</tr>\n";
   }
	
	bookBackupOutput << "</table>\n \n";
	//End the html
	bookBackupOutput << "</body>\n";
	bookBackupOutput << "</html>\n";
	
	bookBackupOutput.close(); //Close the file stream
	
	//Prompt message to show that backup has been finished
	cout << "All data have been backed up to Book_Record_Backup.html file." << endl << endl;

}


