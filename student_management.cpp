#include <iostream> //standard input/output libaray
#include <fstream> //input/output stream to manage files
#include <string> //need for when variable type is string as not standard in C++
#include <chrono> // time manipulation
#include <iomanip> // for put_time 
#include <sstream> // for stringstream

using namespace std; //use names for objects and variables from standard library (for us no std::)

//---------------------------------------------------------------------------------------------------

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
        tm local_tm = *localtime(&time_now); //basically converts time value to a local time

        stringstream ss; //input/output for strings
        ss << put_time(&local_tm, "%Y-%m-%d %X"); //put_time used to format time, contains local time, %digits represent year, month, day, (hours, minutes and seconds)
        return ss.str(); //converts into string
    }
};

//-------------------------------------------------------------------------------------------------

int main() {
    Journal myJournal; //call instance of class
    string entry; //creates string variable named entry to hold journal entries

    cout << "Feel free to write your journal entries, or type '0' to stop." << endl; //prints message
    while (true) { //starts loop
        cout << "Journal entry: "; //prints prompt for the user to type their entry
        getline(cin, entry); //takes input and stores it in entry
        if (entry == "0") break; //condition to break
        myJournal.journalEntry(entry); //pass user input to file
    }

    cout << "Journal Entries:" << endl; //prints message saying here are the journal entries
    myJournal.readJournalEntry(); //method to display all entries from file

    return 0; // regular programming practice, j means program ended succesfully
}
