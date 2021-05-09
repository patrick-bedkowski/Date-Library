# ifdef DateLib
#define DateLib
#include <string>
#include <tuple>
#include <vector>
using namespace std;

bool isLeapYear(int year);

class Date
{
private:
    vector<tuple<int, int, int, string>> history; // vectors that holds history of operations 
    int day;
    int month;
    int year;
public:
        Date(int day, int month, int year); // create a constructor
        
        int getDay();
        int getMonth();
        int getYear();
        void setDay(int new_day);
        void setMonth(int new_month);
        void setYear(int new_year);
        string print_date();
        string print_history();

        friend ostream& operator <<(ostream& output, Date &d);
        bool operator ==(Date& d);
        bool operator !=(Date& d);
        Date operator -(Date& d);
        Date operator +(Date& d);
        Date operator ++();
        Date operator --();

        ~Date();
private:
    void update_history(string operation_name);
    bool checkValue(int day, int month, int year);
        
};

ostream& operator <<(ostream& output, Date const& d);

int dateToDays(int day, int month, int year);
tuple <int, int, int> daysToDate(int days);
int checkDaysInMonth(int i, int year);
int leapDaysBefore(int year);
bool isLeapYear(int year);
int MonthDayStart(int month, bool leap);

# endif