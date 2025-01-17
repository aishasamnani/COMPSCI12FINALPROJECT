#include <iostream>
// #include <stdio.h> 
#include <iomanip> // library to use setw() for word formatting
#include <string>
using namespace std;

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

class Journal {

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
    cout << "\n\nWhat would you like to do?:\n1 - Create new login \n2 - Open calendar\n5 - Quit\nEnter a number: ";
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

    else if (userAction == 5) { // Quit
        break;
    }

  }

  return 0;
}
