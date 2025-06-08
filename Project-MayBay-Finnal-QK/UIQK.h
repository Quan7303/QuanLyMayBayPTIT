#pragma once
#include <iostream>
#include <conio.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <iomanip>
#include "BienToanCuc.h"
#include "Mylibrary.h"
#include "IO.h"
using namespace std;

char TenHocVien[100] = {" HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO THANH PHO HO CHI MINH"};

char ThucDon[SoItem][70] = {
    "Quan Li May Bay   ",
    "Quan Li Chuyen Bay",
    "Dang Ky Ve May Bay",
    "Thong Ke          ",
    "Thoat Chuong Trinh"};

char ThucDonMB[4][50] = {
    "Them May Bay     ",
    "Xoa May Bay      ",
    "Xua Thong Tin    ",
    "Thoat            "};

char ThucDonCB[4][50] = {
    "Tao Chuyen Bay Moi  ",
    "Huy Chuyen Bay      ",
    "Hieu Chinh Thoi Gian",
    "Thoat               "};

char ThucDonVe[6][50] = {
    "Dat Ve Chuyen Bay   ",
    "Huy Ve Chuyen Bay   ",
    "DSCB Theo Noi Den   ",
    "DSV Trong Va CST.tin",
    "DS Hanh Khach       ",
    "Thoat               "};

string ContentAirplane[3] = {"SoHieu", "HangMayBay", "SoChoNgoi"};
string ContentFlight[6] = {"MaChuyenBay", "SanBayDen", "SoHieuMayBay", "ThoiGianDi", "TongSoVe", "TrangThai"};
string ContentPassenger[6] = {"STT", "SoVe", "CCCD", "Ho", "Ten", "GioiTinh"};
string StaticsTable[2] = {"SoHieuMayBay", "SoLuotTHChuyenBay"};
string SpecifedFlight[6] = {"MaChuyenBay", "SoHieuMayBay", "ThoiGianDi", "TongSoVe", "DaBan", "ConTrong"};

int HoanhDoHienThiMB[7] = {53, 72, 97, 115, 135, 147, 159};
int HoanhDoHienThiCB[7] = {35, 54, 76, 97, 117, 129, 141};
int HoanhDoHienThiHK[7] = {43, 53, 63, 80, 100, 113, 126};
void NormalLine()
{
    SetColor(11);
    SetBGColor(0);
}

void HighlightLine()
{
    SetColor(11);
    SetBGColor(1);
}

int RemoveConfirm()
{
    // return 0 la yes - dong y, return 1 la no - tu choi
    ShowCur(false);
    NormalLine();

    gotoxy(X_RemoveConfirm - 3, Y_RemoveConfirm);
    cout << " Ban co chac chan";
    gotoxy(X_RemoveConfirm - 3, Y_RemoveConfirm + 1);
    cout << "  muon thay doi?";
    char Option[2][4] = {"Yes", "No "};
    for (int i = 0; i < 2; i++)
    {
        gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + i * 2 + 2);
        cout << Option[i];
    }
    int pointer = 0;

    gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + pointer * 2 + 2);
    HighlightLine();
    cout << Option[pointer];
    char signal;

    while (true)
    {
        signal = getch();
        if (signal == 224)
            signal = getch();
        switch (signal)
        {
        case KEY_UP:
            if (pointer > 0)
            {
                NormalLine();
                gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
                pointer--;
                HighlightLine();
                gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer < 1)
            {
                NormalLine();
                gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
                pointer++;
                HighlightLine();
                gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
            }
            break;
        case ENTER:
            ShowCur(true);
            return pointer;
        }
    }
}
int RemoveConfirmVe()
{
    // return 0 la yes - dong y, return 1 la no - tu choi
    ShowCur(false);
    NormalLine();

    gotoxy(X_RemoveConfirm - 3, Y_RemoveConfirm);
    cout << "Moi ban nhap lua chon";

    char Option[2][14] = {"DIEM DEN     ",
                          "MA CHUYEN BAY"};
    for (int i = 0; i < 2; i++)
    {
        gotoxy(X_RemoveConfirm, Y_RemoveConfirm + i * 2 + 2);
        cout << Option[i];
    }
    int pointer = 0;

    gotoxy(X_RemoveConfirm, Y_RemoveConfirm + pointer * 2 + 2);
    HighlightLine();
    cout << Option[pointer];
    char signal;

    while (true)
    {
        signal = getch();
        if (signal == 224)
            signal = getch();
        switch (signal)
        {
        case KEY_UP:
            if (pointer > 0)
            {
                NormalLine();
                gotoxy(X_RemoveConfirm, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
                pointer--;
                HighlightLine();
                gotoxy(X_RemoveConfirm, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer < 1)
            {
                NormalLine();
                gotoxy(X_RemoveConfirm, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
                pointer++;
                HighlightLine();
                gotoxy(X_RemoveConfirm, Y_RemoveConfirm + pointer * 2 + 2);
                cout << Option[pointer];
            }
            break;
        case ENTER:
            ShowCur(true);
            return pointer;
        case ESC:
            return -1;
        }
    }
}

void DrawTable()
{
    Introduction();
    gotoxy(2, 2);
    cout << "\t   MENU";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
        gotoxy(i, 13);
        cout << char(205);
    }
    for (int j = 1; j < 14; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 1);
    cout << char(201);
    gotoxy(1, 3);
    cout << char(204);
    gotoxy(1, 13);
    cout << char(200);
    gotoxy(24, 1);
    cout << char(187);
    gotoxy(24, 3);
    cout << char(185);
    gotoxy(24, 13);
    cout << char(188);
    gotoxy(50, 2);
    cout << TenHocVien;
    gotoxy(49, 1);
    cout << char(201);
    gotoxy(119, 1);
    cout << char(187);
    gotoxy(49, 3);
    cout << char(200);
    gotoxy(119, 3);
    cout << char(188);
    for (int i = 50; i < 119; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
    }

    for (int j = 2; j < 3; j++)
    {
        gotoxy(49, j);
        cout << char(186);
        gotoxy(119, j);
        cout << char(186);
    }
}

void DrawTableMB()
{
    gotoxy(2, 2);
    cout << "\t   MENU";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
        gotoxy(i, 13);
        cout << char(205);
    }
    for (int j = 1; j < 14; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 1);
    cout << char(201);
    gotoxy(1, 3);
    cout << char(204);
    gotoxy(1, 13);
    cout << char(200);
    gotoxy(24, 1);
    cout << char(187);
    gotoxy(24, 3);
    cout << char(185);
    gotoxy(24, 13);
    cout << char(188);
    gotoxy(50, 2);
    cout << TenHocVien;
    gotoxy(49, 1);
    cout << char(201);
    gotoxy(119, 1);
    cout << char(187);
    gotoxy(49, 3);
    cout << char(200);
    gotoxy(119, 3);
    cout << char(188);
    for (int i = 50; i < 119; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
    }

    for (int j = 2; j < 3; j++)
    {
        gotoxy(49, j);
        cout << char(186);
        gotoxy(119, j);
        cout << char(186);
    }
    for (int i = 0; i < SoItem; i++)
    {
        gotoxy(3, 4 + i * 2);
        cout << ThucDon[i];
    }
    // CHUC NANG
    gotoxy(2, 15);
    cout << "\tCHUC NANG";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 14);
        cout << char(205);
        gotoxy(i, 16);
        cout << char(205);
        gotoxy(i, 24);
        cout << char(205);
    }
    for (int j = 14; j < 25; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 14);
    cout << char(201);
    gotoxy(1, 16);
    cout << char(204);
    gotoxy(1, 24);
    cout << char(200);
    gotoxy(24, 14);
    cout << char(187);
    gotoxy(24, 16);
    cout << char(185);
    gotoxy(24, 24);
    cout << char(188);
    gotoxy(50, 2);
    // THONG BAO
    gotoxy(2, 26);
    cout << "\tTHONG BAO";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 25);
        cout << char(205);
        gotoxy(i, 27);
        cout << char(205);
        gotoxy(i, 40);
        cout << char(205);
        gotoxy(i, 45);
        cout << char(205);
    }
    for (int j = 25; j < 45; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 25);
    cout << char(201);
    gotoxy(1, 27);
    cout << char(204);
    gotoxy(1, 40);
    cout << char(204);
    gotoxy(1, 45);
    cout << char(200);
    gotoxy(24, 25);
    cout << char(187);
    gotoxy(24, 27);
    cout << char(185);
    gotoxy(24, 40);
    cout << char(185);
    gotoxy(24, 45);
    cout << char(188);
    gotoxy(3, 41);
    cout << "ESC : Thoat";
    gotoxy(3, 42);
    cout << "KEY_RIGHT : NEXT";
    gotoxy(3, 43);
    cout << "KEY_LEFT : BACK";
}
void DrawTableVe()
{
    gotoxy(2, 2);
    cout << "\t   MENU";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
        gotoxy(i, 13);
        cout << char(205);
    }
    for (int j = 1; j < 14; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 1);
    cout << char(201);
    gotoxy(1, 3);
    cout << char(204);
    gotoxy(1, 13);
    cout << char(200);
    gotoxy(24, 1);
    cout << char(187);
    gotoxy(24, 3);
    cout << char(185);
    gotoxy(24, 13);
    cout << char(188);
    gotoxy(50, 2);
    cout << TenHocVien;
    gotoxy(49, 1);
    cout << char(201);
    gotoxy(119, 1);
    cout << char(187);
    gotoxy(49, 3);
    cout << char(200);
    gotoxy(119, 3);
    cout << char(188);
    for (int i = 50; i < 119; i++)
    {
        gotoxy(i, 1);
        cout << char(205);
        gotoxy(i, 3);
        cout << char(205);
    }

    for (int j = 2; j < 3; j++)
    {
        gotoxy(49, j);
        cout << char(186);
        gotoxy(119, j);
        cout << char(186);
    }

    for (int i = 0; i < SoItem; i++)
    {
        gotoxy(3, 4 + i * 2);
        cout << ThucDon[i];
    }
    // CHUC NANG
    gotoxy(2, 15);
    cout << "\tCHUC NANG";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 14);
        cout << char(205);
        gotoxy(i, 16);
        cout << char(205);
        gotoxy(i, 28);
        cout << char(205);
    }
    for (int j = 14; j < 28; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 14);
    cout << char(201);
    gotoxy(1, 16);
    cout << char(204);
    gotoxy(1, 28);
    cout << char(200);
    gotoxy(24, 14);
    cout << char(187);
    gotoxy(24, 16);
    cout << char(185);
    gotoxy(24, 28);
    cout << char(188);
    // THONG BAO
    gotoxy(2, 30);
    cout << "\tTHONG BAO";
    for (int i = 1; i < 25; i++)
    {
        gotoxy(i, 29);
        cout << char(205);
        gotoxy(i, 31);
        cout << char(205);
        gotoxy(i, 41);
        cout << char(205);
        gotoxy(i, 45);
        cout << char(205);
    }
    for (int j = 29; j < 46; j++)
    {
        gotoxy(1, j);
        cout << char(186);
        gotoxy(24, j);
        cout << char(186);
    }
    gotoxy(1, 29);
    cout << char(201);
    gotoxy(1, 31);
    cout << char(204);
    gotoxy(1, 41);
    cout << char(204);
    gotoxy(1, 45);
    cout << char(200);
    gotoxy(24, 29);
    cout << char(187);
    gotoxy(24, 31);
    cout << char(185);
    gotoxy(24, 41);
    cout << char(185);
    gotoxy(24, 45);
    cout << char(188);
    gotoxy(3, 42);
    cout << "ESC : Thoat";
    gotoxy(3, 43);
    cout << "KEY_RIGHT : NEXT";
    gotoxy(3, 44);
    cout << "KEY_LEFT : BACK";
}

int MenuDong(char ThucDon[SoItem][70])
{
    ShowCur(false);
    NormalLine();
    system("cls");
    DrawTable();
    for (int i = 0; i < SoItem; i++)
    {
        gotoxy(3, 4 + i * 2);
        cout << ThucDon[i];
    }
    int pointer = 0;
    gotoxy(3, 4 + pointer * 2);
    HighlightLine();
    cout << ThucDon[pointer];
    char signal;
    while (true)
    {
        signal = getch();
        if (signal == -32)
        {
            signal = getch();
        }
        switch (signal)
        {
        case KEY_UP:
            if (pointer + 1 > 1)
            {
                NormalLine();
                gotoxy(3, 4 + pointer * 2);
                cout << ThucDon[pointer];
                pointer--;
                HighlightLine();
                gotoxy(3, 4 + pointer * 2);
                cout << ThucDon[pointer];
            }
            break;
        case KEY_DOWN:
            if (pointer + 1 < SoItem)
            {
                NormalLine();
                gotoxy(3, 4 + pointer * 2);
                cout << ThucDon[pointer];
                pointer++;
                HighlightLine();
                gotoxy(3, 4 + pointer * 2);
                cout << ThucDon[pointer];
            }
            break;
        case ENTER:
            return pointer + 1;
        }
    }
}

void KhungHienThi(string content[], int nContent, int HoanhDoHienThi[])
{
    system("color 0B");
    SetColor(11);
    SetBGColor(0);
    for (int i = 0; i < nContent; i++)
    {
        gotoxy(HoanhDoHienThi[i] + 3, Y_HienThi + 1);
        cout << content[i];
    }
    for (int j = Y_HienThi - 2; j <= Y_HienThi + 19; j++)
    {
        for (int i = 0; i < nContent + 1; i++)
        {
            gotoxy(HoanhDoHienThi[i], j);
            cout << char(186);
        }
    }
    for (int i = HoanhDoHienThi[0]; i < HoanhDoHienThi[nContent]; i++)
    {
        gotoxy(i, Y_HienThi - 2);
        cout << char(205);

        gotoxy(i, Y_HienThi);
        cout << char(205);

        gotoxy(i, Y_HienThi + 2);
        cout << char(205);

        gotoxy(i, Y_HienThi + 20);
        cout << char(205);
    }
    for (int i = 0; i <= nContent; i++)
    {
        if (i == 0)
        {
            gotoxy(HoanhDoHienThi[i], Y_HienThi - 2);
            cout << char(201);
            gotoxy(HoanhDoHienThi[i], Y_HienThi);
            cout << char(204);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 2);
            cout << char(204);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 20);
            cout << char(200);
        }
        else if (i == nContent)
        {
            gotoxy(HoanhDoHienThi[i], Y_HienThi - 2);
            cout << char(187);
            gotoxy(HoanhDoHienThi[i], Y_HienThi);
            cout << char(185);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 2);
            cout << char(185);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 20);
            cout << char(188);
        }
        else
        {
            gotoxy(HoanhDoHienThi[i], Y_HienThi - 2);
            cout << char(203);
            gotoxy(HoanhDoHienThi[i], Y_HienThi);
            cout << char(206);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 2);
            cout << char(206);
            gotoxy(HoanhDoHienThi[i], Y_HienThi + 20);
            cout << char(202);
        }
    }
}

void CreateRow(int x, int y, string content, int length)
{
    gotoxy(x - 2, y - 1);
    cout << char(201) << setw(length) << setfill(char(205)) << char(205) << char(187);

    gotoxy(x - 2, y);
    cout << char(186) << content << setw(length - content.length() + 1) << setfill(' ') << char(186);

    gotoxy(x - 2, y + 1);
    cout << char(200) << setw(length) << setfill(char(205)) << char(205) << char(188);
}

void CreateForm(string content[], int StartIndex, int nContent, int length)
{
    ShowCur(false);
    int yThem = Y_Them;
    for (int i = StartIndex; i < nContent; i++)
    {
        CreateRow(X_Them, yThem, content[i], length);
        yThem += 3;
    }
    ShowCur(true);
}

void RemoveForm()
{
    ShowCur(false);
    for (int i = 0; i < 6; i++)
    {
        gotoxy(X_Them + 12, i * 3 + Y_Them);
        printf("%-20s", " ");
    }
    ShowCur(true);
}

void RemoveFormComplete()
{
    ShowCur(false);
    for (int i = 0; i < 17; i++)
    {
        gotoxy(X_Them - 10, Y_Them - 1 + i);
        printf("%-50s", " ");
    }
    ShowCur(true);
}

void RemoveFlight()
{
    ShowCur(false);
    for (int i = 4; i < 40; i++)
    {
        gotoxy(35, i);
        printf("%-120s", " ");
    }
    ShowCur(true);
}

void RemoveNotification()
{
    ShowCur(false);
    for (int i = 2; i < 9; i++)
    {
        gotoxy(X_Notification - 1, Y_Notification + i);
        printf("%-22s", " ");
    }
    ShowCur(true);
}

void XoaDuLieuDuThua(int count, int nContent, int HoanhDoHienThi[])
{
    if (count < NumberPerPage)
    {
        for (int i = count; i < NumberPerPage; i++)
        {
            for (int y = 0; y < nContent; y++)
            {
                gotoxy(HoanhDoHienThi[y] + 2, Y_HienThi + 3 + i * 2);
                if (y < 4)
                    printf("%-16s", " ");
                else if (y == 4)
                    printf("%-8s", " ");
                else
                    printf("%-9s", " ");
            }
        }
    }
}
void XoaDuLieuDuThuaHK(int count, int nContent, int HoanhDoHienThi[])
{
    if (count < NumberPerPage)
    {
        for (int i = count; i < NumberPerPage; i++)
        {
            for (int y = 0; y < nContent; y++)
            {
                gotoxy(HoanhDoHienThi[y] + 2, Y_HienThi + 3 + i * 2);
                if (y == 3)
                    printf("%-15s", " ");
                else if (y == 4)
                    printf("%-10s", " ");
                else if (y == 2)
                    printf("%-13s", " ");
                else
                    printf("%-7s", " ");
            }
        }
    }
}
