#include <iostream> // input/output stream
using namespace std; //use names for objects and variables from standard library (for us no std::)
#include <fstream> //input/output stream to manage files
#include <string> //need for when variable type is string as not standard in C++
#include <chrono> // time manipulation
#include <iomanip> // for put_time, library to use setw() for word formatting
#include <sstream> // for stringstream
// #include <stdio.h>

class Calendar {
  private:
    int year;

    // Checks for a leap year by checking the following criteria is true:
    // The year must be evenly divisible by 4;
    // If the year can also be evenly divided by 100, it is not a leap year;
    // unless...
    // The year is also evenly divisible by 400. Then it is a leap year.
    bool leapYear(int year) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return true;
        } else {
            return false;
        }
    }

    // Returns the number of days in a given month
    int getNumDaysInMonth(int month, int year) {
      if (month == 2) {
        if (leapYear(year)) {
            return 29;
        } else {
            return 28;
        }
      }

      if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
      } else {
        return 31;
      }
    }

    int getFirstDayOfYear(int year) {
      int d = (year - 1) * 365;
      d += (year - 1) / 4;
      d -= (year - 1) / 100;
      d += (year - 1) / 400;
      return d % 7;
    }

    // Prints formatted calendar
    void outputMonth(int month, int year) {
      string monthsArray[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
      cout << "\n\n  " << monthsArray[month - 1] << " " << year << "\n";
      cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

      int startDay = getFirstDayOfYear(year);
      for (int i = 1; i < month; i++) {
        startDay = (startDay + getNumDaysInMonth(i, year)) % 7;
      }

      int numDaysInMonth = getNumDaysInMonth(month, year);

      for (int i = 0; i < startDay; i++) {
        cout << "     ";
      }

      for (int day = 1; day <= numDaysInMonth; day++) {
        cout << setw(5) << day; // setw() for indentation
        if ((startDay + day) % 7 == 0) {
          cout << endl; 
        }
      }

      cout << endl;
    }

public:
    Calendar(int y) : year(y) {}

    // Displays the calendar for a specific month
    void displayMonth(int month) {
        outputMonth(month, year);
    }
};

class Journal { // create class 
public: // public members
    Journal() : filename("journal.txt") {} //initalize filename as journal -> this is a constructor, they  are a special class of members that are called by the compiler every time an object of that class is instantiated.

//---------------------------------------------------------------------------------------------------

    void journalEntry(const string& entry) { //writing journal
        ofstream file(filename, ios::app); // open the file in append mode (ios is for input output stream, app is for append))
        if (file) { // if the file is opened
            file << entry << " [" << currentDateTime() << "]" << endl; //write inputted text and add the current date and time to the end of the file
        } else { //otherwise
            cerr << "Error, file was not opened." << endl; //print error message
        }
    }

//---------------------------------------------------------------------------------------------------

    void readJournalEntry() const { //reading journal
        ifstream file(filename); // open file for reading
        if (file) { 
            string line;
            while (getline(file, line)) { //read each line of the file
                cout << line << endl; // output each line to the console
            }
        } else {
            cerr << "Error, file was not opened." << endl;
        }
    }

//---------------------------------------------------------------------------------------------------

private: // private members
    string filename; // store file name

    string currentDateTime() const { //get the current date and time as a string
        chrono::time_point<chrono::system_clock> now = chrono::system_clock::now(); //chrono time point is a point in time, system clock is a system wide real time clock, system clock now returns current time point in clock and assigns value to now
        time_t time_now = chrono::system_clock::to_time_t(now); // timet represents time in seconds since Jan 1, 1970, it is a formatting tool for the chrono library, this line takes a timepoint object and converts it to a time_t object
        time_now -= 5 * 3600; // problem with time zone, subtract 5 hours from time_now
        tm local_tm = *localtime(&time_now); //basically converts time value to a local time

        stringstream ss; //input/output for strings
        ss << put_time(&local_tm, "%Y-%m-%d %X"); //put_time used to format time, contains local time, %digits represent year, month, day, (hours, minutes and seconds)
        return ss.str(); //converts into string
    }
};

class Todo {
};

class Pass {
};

int main() {
  // Intro Lines
  string userName;
  string userPass;
  string name;

  cout << "Welcome to <app name>!\n\nHere, you can journal your thoughts, stay on top of your assignments using to-do lists, and manage your weekly goals and schedule! \nTo get you started, lets set up an account for you.";
  cout << "\n\nCreate Username (NOTE: all usernames/passwords/names must not include spaces): ";
  cin >> userName;
  cout << "\nCreate Password: ";
  cin >> userPass;
  cout << "\nEnter Your Name: ";
  cin >> name;

  cout << ("\n⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅⋆*✩‧₊⋆꙳❅");
  cout << "\n\nWelcome, " << name;

  int userAction;

  while (true) {
    cout << "\n\nWhat would you like to do?:\n1 - Create new login \n2 - Open calendar\n3 - Add to Personal Journal\n5 - Quit\nEnter a number: ";
    cin >> userAction;

    if (userAction == 2) {
        // Calendar - user input, prints monthly calendar
        int currentYear, month;

        cout << "\n\nEnter the year: ";
        cin >> currentYear;

        cout << "Enter which month you would like to view in the calendar (1-12): ";
        cin >> month;

        if (month < 1 || month > 12) {
          cout << "Invalid month. Please enter a number between 1 and 12." << endl;
          return 1;
        } else {
          Calendar calendar(currentYear);
          calendar.displayMonth(month);
        }
    } 
    
    else if (userAction == 3) {
      Journal myJournal; //call instance of class
      string entry; //creates string variable named entry to hold journal entries

      cout << "\n\nFeel free to write your journal entries, and type '0' to stop." << endl; //prints message
      while (true) { //starts loop
          cout << "\nJournal entry: "; //prints prompt for the user to type their entry
          getline(cin, entry); //takes input and stores it in entry
          if (entry == "0") break; //condition to break
          myJournal.journalEntry(entry); //pass user input to file
      }

      cout << "\nJournal Entries:" << endl; //prints message saying here are the journal entries
      myJournal.readJournalEntry(); //method to display all entries from file
    }
    
    else if (userAction == 5) { // Quit
        break;
    }

  }

  return 0;
}