#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <math.h>
#include "BienToanCuc.h"
#include "UIQK.h"

using namespace std;
// SHMB MCB
void ConstraintForLetterAndNumber(string &result, bool &MoveOrNot, int &ordinal, bool &SaveOrNot, int distance)
{
    int lenght = (int)result.length();
    gotoxy(X_Them + distance, ordinal * 3 + Y_Them);
    cout << result;
    int count = lenght;

    while (true)
    {
        while (kbhit())
        {
            int signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch();     // Lấy mã phím tiếp theo
                if (signal == KEY_UP) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == KEY_DOWN) // KEY_DOWN
                {
                    ordinal++;
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != BACKSPACE && signal != 0)
            {
                if ((65 <= signal && signal <= 90) || (97 <= signal && signal <= 122) || (48 <= signal && signal <= 57))
                {
                    if (count < Limit_ID_Length)
                    {
                        count++;
                        cout << (char)toupper(signal);
                        result += (char)toupper(signal);
                    }
                }
                else if (signal == ENTER)
                {
                    return;
                }
                else if (signal == ESC)
                {
                    SaveOrNot = false;
                    return;
                }
            }
            else if (signal == BACKSPACE && count > 0)
            {
                cout << "\b \b";
                result.erase(result.length() - 1, 1);
                count--;
            }
        }
    }
}
void ConstraintForNumber(string &result, bool &MoveOrNot, int &ordinal, bool &SaveOrNot, int distance)
{
    int lenght = (int)result.length();
    gotoxy(X_Them + distance, ordinal * 3 + Y_Them);
    cout << result;
    int count = lenght;

    while (true)
    {
        while (kbhit())
        {
            int signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch();     // Lấy mã phím tiếp theo
                if (signal == KEY_UP) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == KEY_DOWN) // KEY_DOWN
                {
                    ordinal++;
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != BACKSPACE && signal != 0)
            {
                if (48 <= signal && signal <= 57)
                {
                    if (count < Limit_ID_Length - 3)
                    {
                        count++;
                        cout << (char)signal;
                        result += (char)signal;
                    }
                }
                else if (signal == ENTER)
                {
                    return;
                }
                else if (signal == ESC)
                {
                    SaveOrNot = false;
                    return;
                }
            }
            else if (signal == BACKSPACE && count > 0)
            {
                cout << "\b \b";
                result.erase(result.length() - 1, 1);
                count--;
            }
        }
    }
}

void ConstraintsForLetterAndSpace(string &result, bool &MoveOrNot, int &ordinal, bool &SaveOrNot, int distance)
{
    int count = result.length();
    gotoxy(X_Them + distance, ordinal * 3 + Y_Them);
    cout << result;
    bool Spaced = false; // false nghĩa là chưa nhập khoảng trắng
    int signal;

    while (true)
    {
        while (kbhit())
        {
            signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch(); // Lấy mã phím tiếp theo
                if (signal == 72) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == 80) // KEY_DOWN
                {
                    ordinal++; // Di chuyển xuống
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != 0)
            {
                if ((65 <= signal && signal <= 90) || (97 <= signal && signal <= 122) || signal == SPACE)
                {
                    // Giới hạn độ dài chuỗi là 20
                    if (count < 20)
                    {
                        // Kiểm tra điều kiện để không nhập SPACE liên tiếp
                        if (signal == SPACE)
                        {
                            if (!Spaced && count > 0) // Không cho phép SPACE ở đầu hoặc liên tiếp
                            {
                                cout << (char)signal;
                                result += (char)signal;
                                Spaced = true;
                                count++;
                            }
                        }
                        else
                        {
                            // In hoa chữ cái đầu tiên hoặc sau khoảng trắng
                            if (count == 0 || result[result.length() - 1] == ' ')
                            {
                                cout << (char)toupper(signal);
                                result += (char)toupper(signal);
                            }
                            else
                            {
                                cout << (char)tolower(signal);
                                result += (char)tolower(signal);
                            }
                            Spaced = false;
                            count++;
                        }
                    }
                }
                else if (signal == ENTER)
                {
                    // Xóa khoảng trắng ở cuối nếu có
                    while (!result.empty() && result[result.length() - 1] == ' ')
                    {
                        cout << "\b \b";
                        result.erase(result.length() - 1, 1);
                        count--;
                    }
                    // SaveOrNot = true;
                    return;
                }
                else if (signal == BACKSPACE && count > 0)
                {
                    // Xóa ký tự cuối cùng mà không dùng back() và pop_back()
                    if (result[result.length() - 1] == ' ')
                        Spaced = false; // Reset trạng thái SPACE nếu ký tự bị xóa là SPACE

                    cout << "\b \b";
                    result.erase(result.length() - 1, 1); // Xóa ký tự cuối cùng
                    count--;
                }
                else if (signal == ESC)
                {
                    SaveOrNot = false;
                    return;
                }
            }
        }
    }
}

/*space la khoang thut dau dong
Limit Reach la gia tri gioi han cua no*/

void ConstraintForDateAndTime(int &result, int &ordinal, int &DTordinal, bool &SaveOrCancel, bool &MoveOrNot, bool &DTMoveOrNot, int space, int LimitReach)
{
    int count = 0;
    gotoxy(X_Them + space + DTordinal * 3, 9 + Y_Them);
    // if (result != 0)
    cout << result;

    int num = result;
    /*Lay do dai day so dang nhap*/
    do
    {
        count++;
        num /= 10;
    } while (num != 0);

    int signal;
    while (true)
    {
        while (kbhit())
        {
            signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch();
                if (signal == KEY_LEFT)
                {
                    if (DTordinal > 0)
                    {
                        DTordinal--;
                        DTMoveOrNot = true;
                        return;
                    }
                }
                else if (signal == KEY_RIGHT)
                {
                    DTordinal++;
                    DTMoveOrNot = true;
                    return;
                }
                else if (signal == KEY_UP) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == KEY_DOWN) // KEY_DOWN
                {
                    ordinal++; // Di chuyển xuống
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != SPACE && signal != 0) /*thao tac nhap so*/
            {
                if (48 <= signal && signal <= 57)
                {
                    int numb = signal - 48;
                    /*vi nhu nhap 13 la gio thi khong hop le*/
                    if (result > LimitReach)
                        continue;

                    if ((result * 10 + numb) < LimitReach)
                    {
                        cout << numb;
                        result = result * 10 + (numb);
                        count++;
                    }
                }
                else if (signal == 8 && count > 0)
                {
                    cout << (char)BACKSPACE << " " << (char)BACKSPACE;
                    count--;
                    result /= 10;
                }
                else if (signal == ENTER)
                {

                    if (result > LimitReach || (DTordinal > 1 && result == 0))
                        continue;
                    return;
                }
                else if (signal == ESC)
                {
                    SaveOrCancel = false;
                    return;
                }
            } // if( signal != 224 && signal != SPACE && signal != 0 )

        } // while( _kbhit() )
    } // while(true)
}

void ConstraintForOnlyNumber(int &result, bool &MoveOrNot, int &ordinal, bool &SaveOrNot, int distance, int LimitNumber)
{
    gotoxy(X_Them + distance, ordinal * 3 + Y_Them);
    if (result != 0)
    {
        cout << result;
    }
    int count = 0; // mac dinh
    int num = result;
    /*Lay di dai cua day so dang nhap vao*/
    while (num != 0)
    {
        count++;
        num /= 10;
    }
    while (true)
    {
        while (kbhit())
        {
            int signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch();     // Lấy mã phím tiếp theo
                if (signal == KEY_UP) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == KEY_DOWN) // KEY_DOWN
                {
                    ordinal++; // Di chuyển xuống
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != SPACE && signal != 0)
            {
                /*  ---tu 0 den 9--- va count nho hon 3*/
                if (48 <= signal && signal <= 57)
                {
                    /* signal = 56 -> numb = 56 - 48 = 8 -> ung dung voi so 8*/
                    int Numb = signal - 48;
                    if (signal == 48 && count == 0)
                    {
                        continue;
                    }
                    /* vi du LimitNumber = 100 co nghia may bay chi cho
                    nhap toi da 100 cho ngoi */
                    else if ((result * 10 + Numb) <= LimitNumber)
                    {
                        cout << Numb;
                        result = result * 10 + Numb;
                        count++;
                    }
                }
                else if (signal == ESC)
                {
                    SaveOrNot = false;
                    return;
                }

                else if (signal == BACKSPACE && count > 0)
                {
                    cout << (char)BACKSPACE << " " << (char)BACKSPACE;
                    count--;
                    result /= 10;
                }

                else if (signal == ENTER)
                {
                    if (result > LimitNumber)
                        continue;
                    // MoveOrNot = true;
                    return;
                }
            } // ( signal != 224 && signal != BACKSPACE && signal != 0)

        } // while( _kbhit() )
    } // while(true)
}
void ConstraintForOnlyGender(int &result, bool &MoveOrNot, int &ordinal, bool &SaveOrNot, int distance)
{
    gotoxy(X_Them + distance, ordinal * 3 + Y_Them);
    if (result != 0)
    {
        cout << result;
    }
    int count = 0;
    while (true)
    {
        while (kbhit())
        {
            int signal = getch();
            if (signal == 224) // Xử lý phím mũi tên
            {
                signal = getch(); // Lấy mã phím tiếp theo
                if (signal == 72) // KEY_UP
                {
                    if (ordinal > 0)
                    {
                        ordinal--; // Di chuyển lên
                        MoveOrNot = true;
                        return;
                    }
                }
                else if (signal == 80) // KEY_DOWN
                {
                    ordinal++; // Di chuyển xuống
                    MoveOrNot = true;
                    return;
                }
            }
            else if (signal != 224 && signal != SPACE && signal != 0)
            {
                /*  ---tu 0 den 1--- va count nho hon 3*/
                if (49 <= signal && signal <= 50)
                {
                    /* signal = 56 -> numb = 56 - 48 = 8 -> ung dung voi so 8*/
                    int Numb = signal - 48;

                    /* vi du LimitNumber = 100 co nghia may bay chi cho
                    nhap toi da 100 cho ngoi */
                    if (0 < result * 10 + Numb && result * 10 + Numb < 3)
                    {
                        cout << Numb;
                        result = result * 10 + Numb;
                        count++;
                    }
                }
                else if (signal == ESC)
                {
                    SaveOrNot = false;
                    return;
                }
                else if (signal == 8 && count >= 0)
                {
                    cout << (char)BACKSPACE << " " << (char)BACKSPACE;
                    count--;
                    result /= 10;
                }

                else if (signal == ENTER)
                {
                    if (result < 1 || result > 2)
                        continue;
                    return;
                }
            } // ( signal != 224 && signal != BACKSPACE && signal != 0)
        } // while( _kbhit() )
    } // while(true)
}
