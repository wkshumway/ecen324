/***********************************************************************
 * Program:
 *    Lab CalendarOptimize, Optimizing a Calendar Program
 *    Brother Jones, ECEN 324
 * Author:
 *    Wellesley Shumway
 * Summary:
 *    I took all the asserts out. I changed the long if chains to
 *    arrays referenced with the variable that would be in the if.
 *    I optimized the leap year function. I took out the function
 *    calls to isLeapYear where they could be replaced with the
 *    algorithm from the isLeapYear function. I combined some printf
 *    calls.
 *    A summary of the optimizations that you did goes here.
 *    A portion of your grade is based on this summary.
 *
 * Notes:
 *    - Your goal is to optimize this program to minimize the run time.
 *
 *    - Copy this file to a directory you wish to work in:
 *        cd ~/someDirectoryYouCreated
 *        cp /home/ecen324/calendarOptimize/starter.cpp .
 *
 *    - You can do pretty much anything with the code you want, as
 *      long as it is contained within this file and obeys the following
 *      rules:.
 *      - Have:  #include "/home/ecen324/calendarOptimize/lab_consts.h"
 *      - Use "pos += sprintf(calendar + pos, ..., ...)" for outputting the
 *        calendars. You can change how and when your code writes to the
 *        output, but you MUST use something of this form in order for the
 *        lab to compile with the testing program provided (testCalOpt).
 *      - You MUST have "void make_calendars(int[], int[], char*);" defined
 *        in this file for your code to compile for the lab.
 *      - If you want your program to be compiled with any special compiler
 *        options when tested, you must include the line found below this
 *        header that says:
 *           This code is to be compiled with: CAL_COMPILE_OPT=" ... "
 *        You will change what is between the " " to have your desired options.
 *
 *    - Month numbers are 1-12
 *    - Years numbers are >= 1753
 *
 *    - You test your optimizations by doing:
 *         /home/ecen324/calendarOptimize/testCalOpt
 *      This tests all of the *.cpp files in current directory.
 *      or if you want to add options to the g++ compile of your code:
 *         CAL_COMPILE_OPT="-Opt1 -Opt2 ..." /home/ecen324/calendarOptimize/testCalOpt -o
 *      To see more options for the test program execute:
 *         /home/ecen324/calendarOptimize/testCalOpt -h
 *
 *    - Submit your fastest code using the "submit" command.  The code will
 *      fail to compile, but that is OK.
 *
 ************************************************************************/

/***********************************************************************
 * This code is to be compiled with: CAL_COMPILE_OPT=" ... "
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <iomanip>

// Get lab specific variables --You must include this #include--
#include "/home/ecen324/calendarOptimize/lab_consts.h"

using namespace std;

// The year the current calendar began to be valid
#define yearSeed 1753
// Just for kicks and giggles
#define buckRogers 2200

/**********************************************************************
 * Returns true if a given year is a leap year
 ***********************************************************************/
bool isLeapYear(int year)
{
  // Not a leap year if not evenly divisible by 4
  if (year % 4 != 0)
    return false;

  // Is a leap yar if not divisible by 100
  else if (year % 100 != 0 )
    return true;

  // Is a leap year if on the quad century
  else if (year % 400 != 0 )
    return false;
  else
    return false;
}


/**********************************************************************
 * Returns the number of days in a month
 ***********************************************************************/
int numDaysInMonth(int month, int year)
{
  int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Not a leap year if not evenly divisible by 4
  if (year % 4 != 0)
    return monthDays[month-1];

  // Is a leap yar if not divisible by 100
  else if (year % 100  != 0 )
    return monthDays[month-1] + 1;

  // Is a leap year if on the quad century
  else if (year % 400 != 0 )
    return monthDays[month-1];
  else
    return monthDays[month-1] + 1;

}

/**********************************************************************
 * Computes the day of the week a month starts on
 * Offset is from Monday because Jan 1, 1753 was a Monday.
 ***********************************************************************/
int computeOffset(int month, int year)
{
  int days = 0;

  // Add up the days associated with each year
  for (int cYear = yearSeed; cYear < year; cYear++)
    {
      days += (isLeapYear(year) ? 366 : 365);
    }

  // Add up the days associated with each month
  for (int cMonth = 1; cMonth < month; cMonth++)
    {
      days += numDaysInMonth(cMonth, year);
    }

  return days % 7;
}

/**********************************************************************
 * Displays the header for the calendar
 ***********************************************************************/
int displayHeader(int month, int year, char *calendar, int pos)
{
  // make a an array to display the correct day
  const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

  return pos += sprintf(calendar + pos, "\n%s, %i\n", months[month], year );
}

/********************************************************************
 * Display the Calendar
 *******************************************************************/
int displayTable(int numDays, int offset, char *calendar, int pos)
{

  // Special case offset==6. We don't want a blank first line
  if (offset == 6)
    offset = -1;
  // Display the header
  pos += sprintf(calendar + pos, "%s", "Su");
  pos += sprintf(calendar + pos, "%s", "Mo");
  pos += sprintf(calendar + pos, "%s", "Tu");
  pos += sprintf(calendar + pos, "%s", "We");
  pos += sprintf(calendar + pos, "%s", "Th");
  pos += sprintf(calendar + pos, "%s", "Fr");
  pos += sprintf(calendar + pos, "%s", "Sa");
  pos += sprintf(calendar + pos, "\n");

  // Display the individual locations on the calendar grid
  int dow = 0; // day of week
  int dom;
  for (dom = -offset; dom <= numDays; dom++, dow++)
    {
      // Display the number or not
      if (dom > 0)
        pos += sprintf(calendar + pos, "% 4i", dom);
      if (dom <= 0)
        pos += sprintf(calendar + pos, "    ");

      // Display the end-of-row marker
      if (dow % 7 == 6)
        pos += sprintf(calendar + pos, "\n");
    }

  // Extra ENDL as necessary
  if (dow % 7 != 0)
    pos += sprintf(calendar + pos, "\n");

  return pos;
}


/**********************************************************************
 * Calls the display functions
 ***********************************************************************/
void display(int month, int year, char *calendar)
{
  int pos = 0;
  int offset = computeOffset(month, year);

  // Header
  pos += displayHeader(month, year, calendar, pos);

  // Body of the table
  pos += displayTable(numDaysInMonth(month, year), offset, calendar, pos);

  // Output calendars shouldn't overlap each other in calendar array buffer

  return;
}


/**********************************************************************
 * YOU MUST HAVE THIS FUNCTION SIGNATURE DEFINED TO COMPILE YOUR CODE
 * This is used by the driver to test your optimizations
 ***********************************************************************/
void make_calendars(int months[], int years[], char *calendars)
{
  for (int i = 0; i < NUM_CALS; i++)
    display(months[i], years[i], calendars + i * CAL_LENGTH);
}
