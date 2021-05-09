#include "DateLib.h"
#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept>      // std::invalid_argument
#include <vector>
#include <sstream>
using namespace std;


   /*****************************************************
   *                  LOGIC FUNCTIONS                   *
   *****************************************************/

// How many days in year will we have from specific year
int daysInMonths[] = { 0, 31, 59, 90, 120, 151, 181, 212,
    243, 273, 304, 334, 365 };

int MonthDayStart(int month, bool leap){
    /* Return days in month */
    if (leap && month >= 2) return daysInMonths[month] + 1;
    return daysInMonths[month];
}

bool isLeapYear(int year) {
    if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    else {
        return false;
    }
}

int leapDaysBefore(int year)
{
    /* Returns number of leap years before inserted year */
    // Years divisible by 4, not divisible by 100, but divisible by 400
    return ((year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400);
}

tuple <int, int, int> daysToDate(int days) {
    /* Returns day, month, year converted from number of days*/

    int year_days;

    int year = (days / 365) + 1; // number of years without leap years

    // to find actual number of year, count leap years
    do{
        year--; // decrement year

        // Calculate the actual number of days
        year_days = year * 365 + leapDaysBefore(year);

    } while (year_days > days);

    year++; // increment year by one

    /* Calculate Month */
    int day_of_year = days - year_days; // days left to calculate month
    bool leap = isLeapYear(year);  // Is current year a leap year?

    // Use table to find month
    int month = 0;
    while (MonthDayStart(month, leap) <= day_of_year && month <= 12) // while number of days left for months is greater than days in month
        month++;

    // Calculate day
    int day = day_of_year - MonthDayStart(month - 1, leap);

    return { day, month, year };

}

int checkDaysInMonth(int month, int year)
{
    /* Returns number of days in specific month during specific year */
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else
        if (month == 2)
        {
            if (isLeapYear(year)) // check leap year
                return 29;
            else
                return 28;
        }
        else
            return 30;
}

int dateToDays(int day, int month, int year) {
    /* Returns number of days from date 01.01.01 of the Gregorian Calendar */

    // Calculations confirmed by wolfram

    int daysInMonth[12] = { 0, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // MONTHS to DAYS
    int monthToDay = 0;
    for (int i = 0; i < month; i++) {
        monthToDay += daysInMonth[i];
    }

    int year_days;
    // Find the actual year, counting leap days
    do {
        year--;
        // Calculate the actual number of days until the
        // approximate year
        year_days = year * 365 + leapDaysBefore(year);

    } while (year == 0);

    if (year_days < 0) year_days += 365; // fixed bug for year 1

    int number_of_days = year_days + day + monthToDay;

    return number_of_days;
}


            /*******************************************
            *             Date Class                   *
            *******************************************/


class Date {
private:
    vector<tuple<int, int, int, string>> history; // vectors that holds history of operations
    int day;
    int month;
    int year;

public: 
    Date(int day, int month, int year) { // create a constructor
        if(checkValue(day, month, year)) { // set data when all values are true
            this->day = day;
            this->month = month;
            this->year = year;
        }
    };

            /*****************************************************
            *                  Gets and Sets                     *
            *****************************************************/

    int getDay() { return this->day; }
    int getMonth() { return this->month; }
    int getYear() { return this->year; }

    void setDay(int new_day) {
        if (checkValue(new_day, this->month, this->year)) {
            this->day = new_day; // set new value
        }
    }

    void setMonth(int new_month) {
        if (checkValue(this->day, new_month, this->year)) {
            this->month = new_month; // set new value
        }   
    }

    void setYear(int new_year) {
        if (checkValue(this->day, this->month, new_year)) {
            this->year = new_year; // set new value
        }
    }

            /*****************************************************
            *                     Print                          *
            *****************************************************/

    string print_date() {
        // if DAY or MONTH is less than 9, it adds 0 so it looks better
        // MONTH
        string temp_day;
        string temp_month;
        tie(temp_day, temp_month) = format_date(this->day, this->month);
        string result = temp_day + "/" + temp_month + "/" + to_string(this->year);
        return result;
    };

    tuple <string, string> format_date(int day, int month) {
        /* Returns formatted day and month in a tuple as strings 
        if DAY or MONTH is less than 9, it adds 0 so it looks better */

        string temp_month = to_string(month);
        if (month <= 9) {
            temp_month = "0" + to_string(month);
        }
        
        string temp_day = to_string(day);
        if (day <= 9) {
            temp_day = "0" + to_string(day);
        }
        return { temp_day, temp_month }; // return tuple with formatted data
    }

    string print_history() {
        std::stringstream ss;

        string new_day;
        string new_month;

        if ((this->history).size()) { // if history vector is not empty
            for (const auto& i : this->history) {
                tie(new_day, new_month) = format_date(get<0>(i), get<1>(i));
                ss << new_day << "/" << new_month << "/" << (get<2>(i)) << " | " << (get<3>(i)) + "\n";
            }
        }
        else {
            ss << "History of operations is empty\n"; // return message
        }
        //convert stream to string and return string
        return ss.str();
    }

    /*****************************************************
    *              Operator Overloading                  *
    *****************************************************/


    bool operator ==(Date& d) { //overloading + operator 
        int temp_day = this->day + d.day; // convert to int
        int temp_month = this->month + d.month;
        int temp_year = this->year + d.year;
        if ((this->day == d.day) && (this->month == d.month) && (this->year == d.year)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator !=(Date& d) { //overloading + operator 
        if ((this->day == d.day) && (this->month == d.month) && (this->year == d.year)) {
            return false;
        }
        else {
            return true;
        }
    }

    Date operator -(Date& d) { // overloading -

        int minued = dateToDays(this->day, this->month, this->year); // odjemna
        int subtrahend = dateToDays(d.day, d.month, d.year); // odjemnik

        // update minued date
        string temp_message = d.print_date() + " date subtracted";
        update_history(temp_message);

        // update subtrahend date
        temp_message = "Subtraction from date " + print_date();
        d.update_history(temp_message); // update subtrahend vector


        int number_of_days = minued - subtrahend;
        if (number_of_days <= 0) {
            return Date(0, 0, 0);
        }

        int new_day;
        int new_month;
        int new_year;

        // convert to date
        tie(new_day, new_month, new_year) = daysToDate(number_of_days);

        return Date(new_day, new_month, new_year);
    }

    Date operator +(Date& d) { // overloading + 

        // update components date
        string temp_message = "Add date " + d.print_date();
        update_history(temp_message);

        temp_message = "Add date " + print_date();
        d.update_history(temp_message); // update subtrahend vector

        int component1 = dateToDays(this->day, this->month, this->year); // sk³adnik sumy
        int component2 = dateToDays(d.day, d.month, d.year); // sk³adnik sumy

        int number_of_days = component1 + component2;

        if (number_of_days <= 0) {
            return Date(0, 0, 0);
        }

        int new_day;
        int new_month;
        int new_year;

        // convert to date
        tie(new_day, new_month, new_year) = daysToDate(number_of_days);

        return Date(new_day, new_month, new_year);
    }

    Date operator ++() {
        /* This method increments Date by one day */

        // update history vector with values before and operation name
        update_history("Incrementation");

        // convert date to number of days
        int number_of_days = dateToDays(this->day, this->month, this->year);

        // increment day by one
        ++number_of_days;

        int new_day;
        int new_month;
        int new_year;

        // convert to date
        tie(new_day, new_month, new_year) = daysToDate(number_of_days);

        // overwrite atributes
        this->day = new_day;
        this->month = new_month;
        this->year = new_year;

        return Date(new_day, new_month, new_year);
    }

    Date operator --() {
        /* This method increments Date by one day */

        // update history vector with values before and operation name
        update_history("Decrementation");

        // convert date to number of days
        int number_of_days = dateToDays(this->day, this->month, this->year);

        // increment day by one
        --number_of_days;

        int new_day;
        int new_month;
        int new_year;

        // convert to date
        tie(new_day, new_month, new_year) = daysToDate(number_of_days);

        // overwrite atributes
        this->day = new_day;
        this->month = new_month;
        this->year = new_year;

        return Date(new_day, new_month, new_year);
    }

    // Destructor 
    ~Date() {
        cout << endl << "Data " << print_date() << " zostala zniszczona" << endl;
    }

private:
    bool checkValue(int day, int month, int year) {
        if ((month <= 12) && (month >= 1)) { // month number cannot be greater than 12
            int number_of_days = checkDaysInMonth(month, year); // find how many days are in selected month
            if ((day <= number_of_days) && (day >= 1)) {
                return true;
            }
            else {
                // WRONG DATA WAS INSERTED
                cout << "Day cannot be greater than in month or less than 1" << endl;
                throw invalid_argument("Day cannot be greater than in month or less than 1");
            }
        }
        else {
            // WRONG DATA WAS INSERTED
            cout << "Month cannot be geater than 12 or less than 1" << endl;
            throw invalid_argument("Month cannot be geater than 12 or less than 1");
        }
    }

    void update_history(string operation_name) {
        // Method updates history vector with name of the operation and value before
        // this method must be public as it sometimes is called from different object
        history.push_back(make_tuple(this->day, this->month, this->year, operation_name));
    }
};

ostream& operator <<(ostream& output, Date &d) {
    /* Returns stream with formatted date */
    if (d.getDay() <= 9) output << "0" << d.getDay();
    else output << d.getDay();
    if (d.getMonth() <= 9) output << "/" << "0" << d.getMonth();
    else output << "/" << d.getMonth();
    output << "/" << d.getYear();
    return output;
}

int main()
{
    return 0;
}