#ifndef FUNC_H
#define FUNC_H
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include<filesystem>
#include <stdexcept>  
#include <limits>     
#include <sstream>    
#include <vector>       
#include <algorithm>   
#include <filesystem>  

namespace fs = std::filesystem;  // ���������ռ����


using namespace std;
void inm();
void help();
short cm_judge(string cm);
void start();
bool Adm();
void reg();
void log_er(char log, const string& message);
bool deleteModule(const string& moduleName);
//��Ҫ��������
string intToString(int value);
string in(string txt);  
string FormatSystemTimeToString(SYSTEMTIME systemTime);
//��־��������

class outfile {
private:
	string nametemp;

public:
	bool insertModule(const string& moduleName, const string& modulePath,string& exe) {
		const string filename = "mod_list.ini";
		nametemp = "./.ass/" + filename;
		vector<string> lines;  
		string line;

		ifstream inFile(nametemp);
		if (!inFile.is_open()) {
			cerr << "�����޷����ļ� " << nametemp << endl;
			return false;
		}

		// ʹ�� getline ���ж�ȡ
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		// ʹ�ñ�׼�㷨 find_if
		auto endIt = find_if(lines.begin(), lines.end(), [](const string& s) {
			return s.find("end") != string::npos;
			});

		if (endIt == lines.end()) {
			cerr << "�����ļ���ȱ�� end ���" << endl;
			return false;
		}

		// 3. ��������ţ���ǰ������ +1��
		int maxId = 0;
		for (const auto& l : lines) {
			if (l.empty() || l.find("end") != string::npos) continue;
			size_t commaPos = l.find(',');
			if (commaPos != string::npos) {
				int id = stoi(l.substr(0, commaPos));
				if (id > maxId) maxId = id;
			}
		}
		int newId = maxId + 1;

		// 4. ��������Ŀ�����뵽 end ǰһ��
		stringstream newEntry;
		exe = modulePath + exe;
		newEntry << newId << ",[" << moduleName << "]   " << exe;
		lines.insert(endIt, newEntry.str());

		// 5. д���޸ĺ������
		ofstream outFile(nametemp, ios::trunc);
		if (!outFile.is_open()) {
			cerr << "�����޷�д���ļ� " << nametemp<< endl;
			return false;
		}

		for (const auto& l : lines) {
			outFile << l << endl;
		}
		outFile.close();

		return true;
	}
	//���ģ��

	bool CreateFolderRelative(const wchar_t* relativePath) {
		// ʹ�ÿ��ַ��汾 CreateDirectoryW ֧�� Unicode
		BOOL result = CreateDirectoryW(relativePath, NULL);

		if (result) {
			return true;  // �����ɹ�
		}
		else {
			// ��ȡ�����벢���
			DWORD error = GetLastError();
			if (error == ERROR_ALREADY_EXISTS) {
				wprintf(L"�ļ����Ѵ���: %s\n", relativePath);
			}
			else {
				wprintf(L"����ʧ�� (������ %d): %s\n", error, relativePath);
			}
			return false;
		}
	}
	//������ģ���ļ���

	wstring ManualConvert(const char* utf8Str) {
		wstring wideStr;
		while (*utf8Str) {

			wideStr += static_cast<wchar_t>(*utf8Str++);
		}
		return wideStr;
	}
	//�ַ�ת��


};
//���ڰ�װģ��ʱ���ຯ����

#endif