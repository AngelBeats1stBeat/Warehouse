#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

int main()
{
	int Continue = 'a';
	ifstream inFile, inFile1, inFile2, inFile3, inFile4, inFile5;
	ofstream outFile, outFile1, outFile2, outFile3;
	bool valid1 = false, valid2 = false, valid3 = false, valid4 = false, valid5 = false, valid6 = false;
	int x, pi = 0, e = 0, g = 0, f = 0;
	string StringVec[10000], StringVec1[10000];
	string s, a, b, q, y, File1, File2, Name1, Name2, Name3, Name4;
	string line, line1, line2, line3, line4;
	string search = "#res<", search1 = "<", search2 = "khoangtrong", search3 = ", #res<", search4 = "ô";
	cout << "Chao mung ban da den voi RLTool 1.0!" << endl;
		while (!valid3)
		{
			while (!valid1)
			{
				valid1 = false;
				cout << "Hay nhap duong dan cua file .ke: " << endl;
				getline(cin, s);
				inFile.open(s);
				
				if (inFile.good())
				{
					cout << endl;
					cout << "Ban da nhap dung dia chi file .ke! " << endl;
					valid1 = true;
				}
				else
				{
					cout << endl;
					cout << "Dia chi file nay khong ton tai!" << endl;
				}
			}

			while (!valid2)
			{
				valid2 = false;
				cout << "Hay nhap duong dan cua file .sjs: " << endl;
				getline(cin, b);
				inFile1.open(b);
				
				if (inFile1.good())
				{
					cout << endl;
					cout << "Ban da nhap dung dia chi file .sjs! " << endl;
					valid2 = true;
				}
				else
				{
					cout << endl;
					cout << "Dia chi file nay khong ton tai!" << endl;
				}
			}

			q = s.substr(s.find(".") - 4, 4);
			y = b.substr(b.find(".") - 4, 4);
			if (q == y)
			{
				cout << endl;
				cout << "2 file ban mo da tuong thich voi nhau! " << endl;
				valid3 = true;
			}
			else
			{
				cout << endl;
				cout << "2 file ban mo khong tuong thich voi nhau! " << endl;
				cout << "So thu tu file .ke: " << q << endl;
				cout << "So thu tu file .sjs: " << y << endl;
				cout << "Hay mo 2 file co so thu tu giong nhau! " << endl;
				valid1 = false;
				valid2 = false;
			}
		}

		cout << "Da hoan tat khau chon file can mo! " << endl;
		cout << "He thong se khoi tao 2 file, lan luot la File1 va File2 " << endl;
		cout << "File2 la file ban mong muon, vay nen hay chu y nhap dung file path cho tung file! " << endl;
		cout << endl;
		cout << "Nhap dia chi thu muc ban muon dung de chua File1: " << endl;
		cout << "File co dinh dang la txt, vi du ve file path: D://File1.txt" << endl;
		getline(cin, File1);
		cout << "Nhap dia chi thu muc ban muon dung de chua File2: " << endl;
		cout << "File co dinh dang la txt, vi du ve file path: D://File2.txt" << endl;
		getline(cin, File2);
		outFile.open(File1);
		outFile2.open(File2);
		inFile2.open(File1);
		for (unsigned int curLine = 0; getline(inFile, line); curLine++)
		{
			if (line.find(search) != string::npos)
			{
				cout << "Dong co chua chuoi #res: " << curLine << endl;
				cout << line << endl;
				a = line.substr(4, 6);
				cout << a << endl;
				line.replace(line.find(search), 0, "\n khoangtrong \n//");
				if (line.find(search3) != string::npos)
				{
					line.replace(line.find(search3), 2, "\n\n khoangtrong \n//");
				}
				cout << line << endl;

			}

			outFile << line << endl;
		}
		cout << endl;
		cout << "Dang doc file .sjs... " << endl;
		for (unsigned int curLine = 0; getline(inFile1, line1); curLine++)
		{
			if (line1.find(search1) != string::npos)
			{
				cout << "Cac dong co loi thoai: " << curLine << endl;
				line1.erase(0, 7);
				cout << line1 << endl;
				StringVec[g] = line1;
				++g;
			}
		}
		cout << endl;
		cout << g << endl;
		wcout << "Bat dau tien trinh sao chep loi thoai sang file .ke...: " << endl;

		for (unsigned int curLine = 0; getline(inFile2, line3); curLine++)
		{
			if (line3.find(search2) != string::npos)
			{
				cout << "Dong co chua chuoi doan hoi thoai: " << curLine << endl;
				cout << line3 << endl;
				StringVec1[e] = line3;
				++e;
			}
		}
		cout << endl;
		cout << e << endl;
		for (int inx = 0; inx < g; ++inx)
		{
			StringVec1[inx] = StringVec[inx];

			cout << StringVec1[inx] << endl;
		}
		inFile3.open(File1);
		for (unsigned int curLine = 0; getline(inFile3, line); curLine++)
		{
			if (line.find(search2) != string::npos)
			{
				cout << "Dong co chua chuoi doan hoi thoai: " << curLine << endl;
				cout << line << endl;
				line = "'" + StringVec1[f] + "'";
				++f;
			}
			outFile2 << line << endl;
		}
		outFile2.close();
		outFile.close();
		outFile1.close();
		cout << endl;
		valid1 = false;
		valid2 = false;
		cout << "Qua trinh sao chep du lieu da hoan tat!" << endl;
		cout << "Cam on ban da su dung phan mem RLTool 1.0 duoc phat trien boi Dang! Hen gap lai! " << endl;
		return 0;
}
