#pragma once
#include <fstream>
#include <string>
#include "UIQK.h"
#include "MayBay.h"
#include "ChuyenBay.h"
#include "HanhKhach.h"
void ReadMBFromFile(ListMayBay &dsmb)
{
	ifstream filein("DSMB.txt", ios_base::in);
	if (!filein.is_open())
	{
		cout << "Khong the mo file DSMB.txt" << endl;
		return;
	}

	int i = 0;
	while (i < MaxAirplane)
	{
		MayBay *A = new MayBay;
		filein >> A->SoHieuMB;

		if (filein.fail()) // Kiểm tra nếu không đọc được dữ liệu
		{
			delete A;
			break;
		}

		if (strcmp(A->SoHieuMB, "") == 0) // Nếu SoHieuMB rỗng, bỏ qua
		{
			delete A;
			continue;
		}

		filein >> A->LoaiMB >> A->SoChoMB;
		filein.ignore();

		dsmb.DSMB[i++] = A;
		dsmb.SoLuong++;
	}

	filein.close();
}

void WriteMBToFile(ListMayBay &dsmb)
{
	ofstream fileout;
	fileout.open("DSMB.txt", ios_base::out); // ios_base::out la de ghi vao file
	if (fileout.is_open())
	{
		for (int i = 0; i < dsmb.SoLuong; i++)
		{
			fileout << dsmb.DSMB[i]->SoHieuMB << " " << dsmb.DSMB[i]->LoaiMB << " " << dsmb.DSMB[i]->SoChoMB << endl;
		}
	}
	else
	{
		cout << " Ket noi file de ghi vao that bai";
	}
	fileout.close();
}
void Introduction()
{
	ShowCur(false);
	string temp;
	ifstream file("DInTro.txt", ios::in);

	if (file.good())
	{
		while (file.eof() == false)
		{
			getline(file, temp);
			cout << temp << endl;
		}
	}
	else
	{
		cout << " \n Liet ket file that bai " << endl;
	}
	gotoxy(60, 35);
	cout << "Nguyen Gia Quan --- N23DCCN117 --- D23CQCN02-N";
	gotoxy(60, 37);
	cout << "Dao Van Khoa ------ N23DCCN098 --- D23CQCN02-N";
}

void ReadTicketListOfOneFlight(ChuyenBay &cb)
{
	ifstream file;
	char filenameve[50] = "DSVe\\";
	strcat(filenameve, cb.MaCB);
	strcat(filenameve, ".txt");
	file.open(filenameve, ios_base::in);
	if (file.is_open())
	{
		file >> cb.TongSoDaBan;
		cb.TicketList = new Ticket[cb.SoVe];
		for (int i = 0; i < cb.TongSoDaBan; i++)
		{
			file.ignore();
			file >> cb.TicketList[i].CCCD;
			file >> cb.TicketList[i].Status;
		}
	}
	file.close();
}

void ReadFlightFileFromFile(ListCB &LCB, ListMayBay &dsmb)
{
	ifstream filein;
	filein.open("DSCB.txt", ios_base::in);
	for (int i = 0; i < dsmb.SoLuong; i++)
	{
		dsmb.DSMB[i]->SoChuyenDaBay = 0;
	}
	string tmp;
	ChuyenBay cb;
	int i;
	if (filein.is_open())
	{
		int nFlight;
		filein >> nFlight;
		getline(filein, tmp);
		for (int j = 0; j < nFlight; j++)
		{
			if (strcmp(cb.MaCB, "") == 0)
				break;
			filein.getline(cb.MaCB, 15, '\n');
			filein.getline(cb.SanBayDen, 20, '\n');
			filein.getline(cb.SoHieuMB, 15, '\n');
			filein >> cb.TimeDi.h;
			filein >> cb.TimeDi.mi;
			filein >> cb.TimeDi.d;
			filein >> cb.TimeDi.m;
			filein >> cb.TimeDi.y;
			filein >> cb.SoVe;
			filein >> cb.TrangThai;
			getline(filein, tmp);
			TuDongCapNhatTrangThai(LCB);
			for (i = 0; i < dsmb.SoLuong; i++)
			{
				if (stricmp(cb.SoHieuMB, dsmb.DSMB[i]->SoHieuMB) == 0 && cb.TrangThai == 3)
				{
					dsmb.DSMB[i]->SoChuyenDaBay++;
				}
			}
			ReadTicketListOfOneFlight(cb);
			InsertEnd(LCB, cb);
		}
	}
	filein.close();
}
/*luu 1 chuyen bay*/
void SaveTicketListOfOneFlight(ChuyenBay &cb)
{
	ofstream file;
	char filenameve[50] = "DSVe\\";
	strcat(filenameve, cb.MaCB);
	strcat(filenameve, ".txt");
	file.open(filenameve, ios_base::out);
	if (file.is_open())
	{
		file << cb.TongSoDaBan << endl;
		for (int i = 0; i < cb.TongSoDaBan; i++)
		{
			file << cb.TicketList[i].CCCD << endl;
			file << cb.TicketList[i].Status << endl;
		}
	}
	file.close();
}

void SaveFlight(ChuyenBay &cb, ofstream &fileout)
{
	fileout << cb.MaCB << endl;
	fileout << cb.SanBayDen << endl;
	fileout << cb.SoHieuMB << endl;
	fileout << cb.TimeDi.h << endl;
	fileout << cb.TimeDi.mi << endl;
	fileout << cb.TimeDi.d << endl;
	fileout << cb.TimeDi.m << endl;
	fileout << cb.TimeDi.y << endl;
	fileout << cb.SoVe << endl;
	fileout << cb.TrangThai << endl;
	SaveTicketListOfOneFlight(cb);
}

void WriteFlightToFile(ListCB &LCB)
{
	ofstream fileout;
	fileout.open("DSCB.txt", ios_base::out);

	if (fileout.is_open())
	{
		fileout << LCB.SoLuongCB << endl;
		for (PTRCB p = LCB.First; p != NULL; p = p->next)
		{
			SaveFlight(p->Data, fileout);
		}
	}
	else
	{
		gotoxy(X_Notification, Y_Notification + 1);
		cout << " Ket noi file de";
		gotoxy(X_Notification, Y_Notification + 2);
		cout << " ghi vao that bai";
	}
	fileout.close();
}
void ReadPassengerFromFile(Tree &root)
{
	ifstream filein("DSHK.txt");

	if (!filein.is_open())
		return;

	filein >> nPassenger;
	filein.ignore();

	for (int i = 0; i < nPassenger; i++)
	{
		HanhKhach P;
		string ho_lot, ten, cccd;
		getline(filein, cccd);
		getline(filein, ho_lot);
		getline(filein, ten);
		filein >> P.Phai;
		filein.ignore();
		strcpy(P.CCCD, cccd.c_str());
		strcpy(P.Ho, ho_lot.c_str());
		strcpy(P.Ten, ten.c_str());
		AddPassenger(root, P);
	}

	filein.close();
}

void SaveOnePassenger(Tree &root, ofstream &fileout)
{
	fileout << root->Data.CCCD << endl;
	fileout << root->Data.Ho << endl;
	fileout << root->Data.Ten << endl;
	fileout << root->Data.Phai << endl;
}

void SavePassengerList(Tree &root, ofstream &fileout)
{
	if (root != NULL)
	{
		SaveOnePassenger(root, fileout);
		SavePassengerList(root->Left, fileout);
		SavePassengerList(root->Right, fileout);
	}
}

void SavePassengerToFile(Tree &root)
{
	ofstream fileout;
	fileout.open("DSHK.txt", ios_base::out);

	if (fileout.is_open())
	{
		fileout << nPassenger << endl;
		SavePassengerList(root, fileout);
	}
	fileout.close();
}