#pragma once
#include <ctime>
#include <iostream>
#include "UIQK.h"
#include <string>
#include <cstdlib>
using namespace std;
int nDayOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
struct DayTime
{
	int y;
	int m;
	int d;
	int h;
	int mi;
};
bool LeapYear(int year)
{
	if (year % 400 == 0)
		return true;
	else if (year % 100 != 0 && year % 4 == 0)
		return true;
	return false;
}
// kiem tra so ngay va nam nhuan hay khong, return true nghia la dung
bool DateTimeIsRightFormat(DayTime dt)
{
	nDayOfMonth[2] = 28;
	if (LeapYear(dt.y))
		nDayOfMonth[2] = 29;
	if (dt.d > nDayOfMonth[dt.m]) // kiem tra xem so ngay nhap co lon hon so ngay mac dinh khong
		return false;
	return true;
}

DayTime Time_now()
{
	DayTime a_now;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	a_now.d = ltm->tm_mday;
	a_now.m = 1 + ltm->tm_mon;
	a_now.y = 1900 + ltm->tm_year;
	a_now.h = ltm->tm_hour;
	a_now.mi = ltm->tm_min;

	return a_now;
}
// kiem tra dinh dang gio phu ngay thang nam, return true => nhap dung
bool DateTimeIsValid(DayTime dt)
{
	if (!DateTimeIsRightFormat(dt))
		return false;

	nDayOfMonth[2] = 28;
	DayTime dtNow = Time_now();
	// tra ve false neu nhu
	if (dt.y < dtNow.y)
		return false; // nam nhap vao nho hon nam hien tai
	if ((dt.y == dtNow.y) && (dt.m < dtNow.m))
		return false;	// thang nhap vao nho hon thang hien tai
	if (LeapYear(dt.y)) //(dt.y % 400 == 0) || (dt.y % 4 == 0 && dt.y % 100 != 0)
		nDayOfMonth[2] = 29;
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d < dtNow.d)
		return false; // ngay nhap vao nho hon ngay hien tai
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d == dtNow.d && dt.h < dtNow.h)
		return false; // gio nhap bi sai
	// so phut nhap vao bi sai
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d == dtNow.d && dt.h == dtNow.h && dt.mi <= dtNow.mi)
		return false;
	return true;
}

void OutputDateTime(DayTime &dt)
{
	if (dt.h < 10)
		cout << "0" << dt.h;
	else
		cout << dt.h;
	cout << ":";
	if (dt.mi < 10)
		cout << "0" << dt.mi;
	else
		cout << dt.mi;
	cout << " ";
	if (dt.d < 10)
		cout << "0" << dt.d;
	else
		cout << dt.d;
	cout << "/";
	if (dt.m < 10)
		cout << "0" << dt.m;
	else
		cout << dt.m;
	cout << "/";
	cout << dt.y;
}
void OutputDayTime(DayTime &dt)
{
	if (dt.h < 10)
		cout << dt.h << " ";
	else
		cout << dt.h;
	cout << ":";
	if (dt.mi < 10)
		cout << dt.mi << " ";
	else
		cout << dt.mi;
	cout << " ";
	if (dt.d < 10)
		cout << dt.d << " ";
	else
		cout << dt.d;
	cout << "/";
	if (dt.m < 10)
		cout << dt.m << " ";
	else
		cout << dt.m;
	cout << "/";
	cout << dt.y;
}
bool CompareDate(DayTime dt1, DayTime dt2)
{
	return dt1.d == dt2.d && dt2.m == dt1.m && dt1.y == dt2.y;
}

unsigned long int datetoday(DayTime DT)
{
	unsigned long int dayofyear = 365 * (DT.y - 1) + (DT.y - 1) / 4 - (DT.y - 1) / 100 + (DT.y - 1) / 400;
	unsigned long int dayofmonth = 0;
	for (int i = 0; i < DT.m; i++)
	{
		dayofmonth += nDayOfMonth[i];
	}
	if (LeapYear(DT.y) && DT.m >= 2)
	{
		dayofmonth += 1;
	}
	return dayofyear + dayofmonth + DT.d - 1;
}

bool TrongVongBaGio(DayTime Time1, DayTime Time2)
{
	unsigned long int SoPhut_T1 = datetoday(Time1) * 24 * 60 + Time1.h * 60 + Time1.mi;
	unsigned long int SoPhut_T2 = datetoday(Time2) * 24 * 60 + Time2.h * 60 + Time2.mi;
	if (((SoPhut_T1 - SoPhut_T2) <= 180) || ((SoPhut_T2 - SoPhut_T1) <= 180))
		return true;
	return false;
}

bool TG_30p_TruocBay(DayTime TimeDuKien)
{
	DayTime now = Time_now();
	unsigned long int SoPhut_T1 = datetoday(TimeDuKien) * 24 * 60 + TimeDuKien.h * 60 + TimeDuKien.mi;
	unsigned long int SoPhut_now = datetoday(now) * 24 * 60 + now.h * 60 + now.mi;
	if ((SoPhut_T1 > SoPhut_now) && (SoPhut_T1 - SoPhut_now) < 30)
		return true;
	return false;
}
// string Dao(string s)
// {
// 	int left = 0, right = s.length() - 1;
// 	while (left < right)
// 	{
// 		swap(s[left], s[right]);
// 		left++;
// 		right--;
// 	}
// 	return s;
// }
// string To_string(int a)
// {
// 	string t = "";
// 	while (a != 0)
// 	{
// 		t = t + char(a % 10 + '0');
// 		a /= 10;
// 	}
// 	return Dao(t);
// }

// void OutputDateTime(DayTime &dt)
// {
// 	string thang, ngay, gio, phut;
// 	gio = string(2 - To_string(dt.h).length(), '0') + To_string(dt.h);
// 	phut = string(2 - To_string(dt.mi).length(), '0') + To_string(dt.mi);
// 	thang = string(2 - To_string(dt.m).length(), '0') + To_string(dt.m);
// 	ngay = string(2 - To_string(dt.d).length(), '0') + To_string(dt.d);
// 	cout << gio << ":" << phut << " " << ngay << "/" << thang << "/" << dt.y;
// }