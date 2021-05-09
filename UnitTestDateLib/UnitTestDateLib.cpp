#include "../DateLib/DateLib.h"
#include "../DateLib/DateLib.cpp"
#include "CppUnitTest.h"
#include <stdexcept>
#include <string>
#include <tuple>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDateLib
{
	TEST_CLASS(UnitTestDateLib)
	{
	public:
		TEST_METHOD(TestCorrectData)
		{
			Date one(28, 2, 1912);

			Assert::AreEqual(28, (one).getDay());
			Assert::AreEqual(2, (one).getMonth());
			Assert::AreEqual(1912, (one).getYear());
		}

		TEST_METHOD(TestWrongData)
		{
			try {
				int day = 28;
				int month = -2; // month is set to negative number
				int year = 1912;
				Date one(day, month, year);
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << '\n';
			}
		}

		TEST_METHOD(TestLeapYearPast)
		{
			Date one(28, 2, 1836);

			Assert::AreEqual(28, (one).getDay());
			Assert::AreEqual(2, (one).getMonth());
			Assert::AreEqual(1836, (one).getYear());
		}

		TEST_METHOD(TestLeapYearFuture)
		{
			Date one(29, 2, 2080);

			Assert::AreEqual(29, (one).getDay());
			Assert::AreEqual(2, (one).getMonth());
			Assert::AreEqual(2080, (one).getYear());
		}


               /*****************************************************
               *                      Sets                          *
               *****************************************************/

		TEST_METHOD(TestSetCorrectData)
		{
			Date one(28, 2, 1912);

			one.setDay(10);
			one.setMonth(11);
			one.setYear(12);

			Assert::AreEqual(10, (one).getDay());
			Assert::AreEqual(11, (one).getMonth());
			Assert::AreEqual(12, (one).getYear());
		}

		TEST_METHOD(TestSetNotLeapData)
		{
			try {
				Date one(20, 2, 1917);

				Assert::AreEqual(20, (one).getDay());
				Assert::AreEqual(2, (one).getMonth());
				Assert::AreEqual(1917, (one).getYear());

				one.setDay(29); // 1917 not a leap year
				one.setMonth(2);
				one.setYear(1917);
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << '\n';
			}
		}

		TEST_METHOD(TestSetNegativeData)
		{
			try {
				Date one(20, 2, 1917);

				Assert::AreEqual(20, (one).getDay());
				Assert::AreEqual(2, (one).getMonth());
				Assert::AreEqual(1917, (one).getYear());

				one.setDay(20);
				one.setMonth(2);
				one.setYear(-1917); // negative value
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << '\n';
			}
		}
			   /*****************************************************
			   *                 Logic Functions                    *
			   *****************************************************/

		TEST_METHOD(DateToDays)
		{
			// confirmed by wolfram alpha 
			// https://www.wolframalpha.com/input/?i=1+january+1+days+since+11+july+2017

			Date one(11, 7, 2017);

			int result = dateToDays(11, 7, 2017);

			Assert::AreEqual(736520, result);
		}

		TEST_METHOD(DaysToDate)
		{
			int number_of_days = 736520;
			int day;
			int month;
			int year;

			tie(day, month, year) = daysToDate(number_of_days);
			Assert::AreEqual(11, day);
			Assert::AreEqual(7, month);
			Assert::AreEqual(2017, year);
			// the same year as inputed in test before
		}

		TEST_METHOD(datetoDaysNormal)
		{
			Date one(10, 1, 1);

			int expected = dateToDays(10, 1, 1);

			Assert::AreEqual(expected, 10);
		}

		TEST_METHOD(checkLeapYearTrue)
		{
			bool result = isLeapYear(1004);

			Assert::AreEqual(result, true);
		}

		TEST_METHOD(checkLeapYearFalse)
		{
			bool result = isLeapYear(1917);

			Assert::AreEqual(result, false);
		}

			   /*****************************************************
			   *                    Operators                       *
			   *****************************************************/
		TEST_METHOD(TestEqualDates)
		{
			Date one(20, 2, 1917);
			Date two(20, 2, 1917);

			bool result = (one == two);
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestNotEqualDates)
		{
			Date one(20, 2, 1917);
			Date two(22, 2, 1917);

			bool result = (one != two);
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestSubtractDates)
		{
			Date one(10, 7, 2017);
			Date two(5, 2, 1917);

			Assert::AreEqual(8, (one-two).getDay());
			Assert::AreEqual(6, (one-two).getMonth());
			Assert::AreEqual(101, (one-two).getYear());
		}

		TEST_METHOD(TestSubtractEqualDates)
		{
			try {
				Date one(10, 7, 2017);
				Date two(10, 7, 2017);

				Assert::AreEqual(0, (one - two).getDay());
				// when substracting identicial dates, it creates an object of Date type with 0 values
				// 0 values do not meet conditions, thus expection is raised
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << '\n';
			}
		}

		TEST_METHOD(TestSubtractDates1DayGreater)
		{
				Date one(11, 7, 2017);
				Date two(10, 7, 2017);

				Assert::AreEqual(1, (one - two).getDay()); 
		}

		TEST_METHOD(TestAddDates)
		{
			Date one(10, 7, 2017);
			Date two(5, 2, 1917);

			Assert::AreEqual(11, (one + two).getDay());
			Assert::AreEqual(8, (one + two).getMonth());
			Assert::AreEqual(3933, (one + two).getYear());
		}

		TEST_METHOD(TestStreamOperator)
		{
			Date one(10, 7, 2017); // create object
			stringstream ss; 
			ss << one;
			string expected = "10/07/2017";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(TestStreamOperatorAfterNewSetValue)
		{
			Date one(10, 7, 2017); // create object

			one.setDay(20);
			one.setMonth(12);
			one.setYear(1995);

			stringstream ss;
			ss << one;
			string expected = "20/12/1995";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(SubtractAndViewStreamData)
		{
			Date one(11, 7, 2017); // one day difference
			Date two(10, 7, 2017);

			Date subtraction = one - two;

			stringstream ss;
			ss << subtraction; // stream out result
			string expected = "01/01/1"; // expected result
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(Incrementation)
		{
			Date one(11, 7, 2017);
			++one;

			Assert::AreEqual(one.getDay(), 12);
			Assert::AreEqual(one.getMonth(), 7);
			Assert::AreEqual(one.getYear(), 2017);
		}

		TEST_METHOD(Decrementation)
		{
			Date one(11, 7, 2017);
			--one;

			Assert::AreEqual(one.getDay(), 10);
			Assert::AreEqual(one.getMonth(), 7);
			Assert::AreEqual(one.getYear(), 2017);
		}

			   /*****************************************************
			   *                     History                        *
			   *****************************************************/
		TEST_METHOD(EmptyHistory)
		{
			Date one(11, 7, 2017);
			
			stringstream ss;
			ss << one.print_history(); // print history
			string expected = "History of operations is empty\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(EmptyHistorySubtraction)
		{
			Date one(11, 7, 2017);
			Date two(11, 7, 17);
			Date three = (one - two);

			stringstream ss;
			ss << three.print_history(); // print history
			string expected = "History of operations is empty\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(PrintHistoryMinued)
		{
			Date one(11, 7, 2017);
			Date two(12, 1, 4);
			(one - two); // perform the subtraction

			stringstream ss;
			ss << one.print_history(); // print history of date ONE
			string expected = "11/07/2017 | 12/01/4 date subtracted\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(PrintHistorySubtrahend)
		{
			Date one(11, 7, 2017);
			Date two(12, 1, 4);
			(one - two); // perform the subtraction

			stringstream ss;
			ss << two.print_history(); // print history of date TWO
			string expected = "12/01/4 | Subtraction from date 11/07/2017\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(PrintHistoryComponentOne)
		{
			Date one(11, 7, 2017);
			Date two(12, 1, 4);
			(one + two); // perform the addition

			stringstream ss;
			ss << one.print_history(); // print history of date ONE
			string expected = "11/07/2017 | Add date 12/01/4\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(PrintHistoryComponentTwo)
		{
			Date one(11, 7, 2017);
			Date two(12, 1, 4);
			(one + two); // perform the addition

			stringstream ss;
			ss << two.print_history(); // print history of date TWO
			string expected = "12/01/4 | Add date 11/07/2017\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(HistoryIncrementation)
		{
			Date one(11, 7, 2017);
			++one;

			stringstream ss;
			ss << (one).print_history(); // print history
			string expected = "11/07/2017 | Incrementation\n";
			Assert::AreEqual(expected, ss.str());
		}

		TEST_METHOD(HistoryTwoOperations)
		{
			Date one(11, 7, 2017);
			++one;
			--one;

			stringstream ss;
			ss << (one).print_history(); // print history
			// history saves value before operation and name of the operation used
			string expected = "11/07/2017 | Incrementation\n12/07/2017 | Decrementation\n";
			Assert::AreEqual(expected, ss.str());
		}

			   /*****************************************************
			   *                      Print                         *
			   *****************************************************/

		TEST_METHOD(PrintDate)
		{
			Date one(11, 7, 2017);
			++one;

			stringstream ss;
			ss << (one).print_date(); // print history
			// history saves value before operation and name of the operation used
			string expected = "12/07/2017";
			Assert::AreEqual(expected, ss.str());
		}
	};
}
