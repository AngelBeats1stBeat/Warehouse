#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <locale>
using namespace std;

int main()
{
	_setmode(_fileno(stdin), _O_U8TEXT);
	_setmode(_fileno(stdout), _O_U8TEXT);
	vector<int> IntVec;
	vector<wstring>  StringVec2, Fake1, Fake2, File1, File2;
	vector<wstring>  StringVec1;
	vector<wifstream> inFile;
	vector<wofstream> outFile;
	wofstream outFile1;
	wifstream inFile1, inFile2;
	vector<bool> right;
	wchar_t buffer[256];
	wstring Name1, Name2, line1,  line4, Fake3, Name3, File3, line3, Replace1, Replace2, AnotherOne, FileName;
	static wstring line2;
	int count = 0;
	bool acr = false, valid = false, valid1 = false;
	int a,b,z = 0;
	wcout << L" Chào mừng bạn đã đến với RLTool 2.0 " << endl;
	while (!valid)
	{
		wcout << L" Hãy nhập số file mà bạn muốn gắn ruleset vào: ";
		wcin >> b;
		if ((int)b > 10000)
			cout << L" Số liệu mà bạn nhập không phù hợp. Xin vui lòng nhập lại! " << endl;
		else
			valid = true;
	}
	wcin.ignore();
	inFile.resize(b);
	outFile.resize(b);
	right.resize(b);
	Fake1.resize(b);
	Fake2.resize(b);
	File1.resize(b);
	File2.resize(b);
	wcout << L"Hãy nhập đường dẫn của thư mục mà bạn muốn dùng để chứa file batch: ";
	wcin >> FileName;
	wcout << FileName << endl;
	wcin.ignore();
	for (int i = 0;i < b; ++i)
	{
		right[i] = false;
		while (!right[i])
		{
			wcout << endl;
			wcout << L" Hãy nhập đường dẫn của file thứ " << i + 1 << L" mà bạn muốn chỉnh sửa ";
			getline(wcin, Fake1[i]);
			wcout << endl;
			Name1 = Fake1[i].substr(0, Fake1[i].length() - 2);
			File1[i] = Name1;
			if (inFile[i].good())
			{
				right[i] = true;
				wcout << L" Địa chỉ file mà bạn nhập đã chính xác! " << endl;
			}
			else
			{
				wcout << L" Địa chỉ file mà bạn nhập không chính xác!Vui lòng nhập lại " << endl;
			}
		}
		swprintf_s(buffer, L"%sSEEN%i.sjs", FileName.c_str(), i + 1);
		AnotherOne = buffer;
		Name2 = AnotherOne.substr(1, AnotherOne.length() - 2);
		File2[i] = buffer;
		wcout << L" Đường dẫn của file thứ " << i + 1 << L" mà bạn đã tạo: " << File2[i] << endl;
	}
	
	wcout << L" Hãy nhập số kí tự mà bạn muốn gắn ruleset: ";
	wcin >> a;
	wcin.ignore();
	StringVec1.resize(a);
	StringVec2.resize(a);
	IntVec.resize(a);
	wcout << endl;
	wstring ch1;
	while (!valid1)
	{
		wcout << endl;
		wcout << L" Hãy nhập đường dẫn của file có chứa bảng ruleset: ";
		getline(wcin, Fake3);
		wcout << endl;
		Name3 = Fake3.substr(1, Fake3.length() - 2);
		File3 = Name3;
		if (inFile1.good())
		{
			valid1 = true;
			wcout << L" Địa chỉ file mà bạn nhập đã chính xác! " << endl;
		}
		else
		{
			wcout << L" Địa chỉ file mà bạn nhập không chính xác!Vui lòng nhập lại " << endl;
		}
	}
	inFile1.open(Fake3);
	inFile1.imbue(locale("en_us.UTF-8"));
	
	int m = 0, n = 0, g = 0;
	
	for (unsigned int curLine = 0; getline(inFile1, line3); curLine++)
	{
		if (curLine == 0 || curLine % 2 == 0)
		{
			StringVec1[n] = line3;
			wcout << L"Kí tự được thay thế: " << StringVec1[n] << endl;
			if (n < 5)
				++n;
		}
		if (curLine % 2 == 1)
		{
			StringVec2[m] = line3;
			IntVec[m] = StringVec1[m].length();
			if (m < 5)
				++m;
		}
	}
	
	for (int i = 0;i < a; ++i)
	{
		wcout << L" Ruleset được dùng để thay thế cho kí tự này:" << StringVec2[i] << endl;
		wcout << endl;
	}
	
	for (int i = 0; i < b; ++i)
	{
		
		inFile[i].open(Fake1[i]);
		inFile[i].imbue(locale("en_us.UTF-8"));
		outFile[i].imbue(locale("en_us.UTF-8"));
		outFile[i].open(File2[i]);
		int x = 0;
		
		inFile2.open(Fake3);
		inFile2.imbue(locale("en_us.UTF-8"));


		for (unsigned int curLine = 0; getline(inFile[i], line2); curLine++)
		{
			for (int b = 0; b < a; ++b)
			{
				if (line2.find(StringVec1[b]) > 0 && line2.find(StringVec1[b]) < 100)
				{
					wcout << "Chuoi ki tu da duoc tim thay: " << b << endl;
					wcout << line2 << StringVec1[b] << endl;
					line2.replace(line2.find(StringVec1[b]), IntVec[b], StringVec2[b]);
				}
			}
			outFile[i] << line2 << endl;
		}
		inFile[i].close();
		outFile[i].close();
	}	
	outFile1.close();

return 0;
}