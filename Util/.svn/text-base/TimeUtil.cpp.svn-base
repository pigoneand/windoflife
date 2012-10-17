#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

class TimeUtil
{
  public:
    time_t start;
    time_t stop;

    void startCount()
    {
      start = clock();
    }

    double stopCount()
    {
      stop = clock();
      return (stop - start) / 1000.0;
    }
};

const int daysinmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string weekdays[7] = {string("mon"), string("tue"), string("wed"), string("thu"), string("fri"), string("sat"), string("sun")};

class DateTime
{
public:
	int year, month, day;
  int weekday;
	int daysfrom1600;
  static const int weekdayof16000101 = 5;
  
	static bool isLeapYear(int y)
	{ return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }
  
  static int getDayOfMonth(int year, int month)
  { if (month == 2 && isLeapYear(year)) return 29; return daysinmonth[month]; }

	DateTime(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;

		daysfrom1600 = 0;
		for (int y = 1600; y < year; ++y)
			daysfrom1600 += isLeapYear(y) ? 366 : 365;
		for (int m = 1; m < month; ++m)
			daysfrom1600 += (m == 2 && isLeapYear(year)) ? 29 : daysinmonth[m];
		daysfrom1600 += d;
    daysfrom1600--;
    
    weekday = getWeekDay();
	}

	DateTime(const string & s)
	{
		int d, m, y;
		sscanf(s.data(), "%d.%d.%d", &d, &m, &y);
		*this = DateTime(y, m, d);
	}
  
  int getWeekDay() const { return (weekdayof16000101 + daysfrom1600) % 7; } 
  
  friend ostream & operator << (ostream & out, const DateTime & date)
  {
    out << date.year << "-" << date.month << "-" << date.day << " " << weekdays[date.weekday];
    return out;
  }
};

int N;
void init()
{
	int year, month, day;
  cin >> day >> month >> year;
  
  vector<int> daysofweek[7];
  
  int days = DateTime::getDayOfMonth(year, month);
  int startweek = DateTime(year, month, 1).weekday;
  for (int i = 0; i < startweek; ++i) 
    daysofweek[i].push_back(-1);
  
  for (int i = 1; i <= days; ++i)
  {
    DateTime date(year, month, i);
    daysofweek[date.weekday].push_back(i);
  }
  
  for (int k = 0; k < 7; ++k)
  {
    printf("%s", weekdays[k].data());
    bool spec = false;
    for (int i = 0; i < daysofweek[k].size(); ++i)
    {
      int width = 4; if (i > 0) width = 5;
      int d = daysofweek[k][i];
      
      if (d == day) 
      {
        if (width == 4) printf(" ["); else printf("  [");
        width = 2;
      }
      
      if (d == day + 7)
      {
        printf("]"); 
        width = 4;
      }
      
      if (d == -1) for (int j = 0; j < width; ++j) printf(" ");
      else 
      {
        if (width == 4) printf("%4d", daysofweek[k][i]);
        if (width == 5) printf("%5d", daysofweek[k][i]);
        if (width == 2) printf("%2d", daysofweek[k][i]);
        if (width == 3) printf("%3d", daysofweek[k][i]);
      }
      
      if (d == day && i == daysofweek[k].size() - 1) printf("]");
    }
    printf("\n");
  }
}

void york()
{
}

int main()
{
	init();
	york();

	return 0;
}
