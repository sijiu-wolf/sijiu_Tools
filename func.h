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

namespace fs = std::filesystem;  // 定义命名空间别名


using namespace std;
void inm();
void help();
short cm_judge(string cm);
void start();
bool Adm();
void reg();
void log_er(char log, const string& message);
bool deleteModule(const string& moduleName);
//主要函数声明
string intToString(int value);
string in(string txt);  
string FormatSystemTimeToString(SYSTEMTIME systemTime);
//日志函数声明

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
			cerr << "错误：无法打开文件 " << nametemp << endl;
			return false;
		}

		// 使用 getline 逐行读取
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		// 使用标准算法 find_if
		auto endIt = find_if(lines.begin(), lines.end(), [](const string& s) {
			return s.find("end") != string::npos;
			});

		if (endIt == lines.end()) {
			cerr << "错误：文件中缺少 end 标记" << endl;
			return false;
		}

		// 3. 计算新序号（当前最大序号 +1）
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

		// 4. 构建新条目并插入到 end 前一行
		stringstream newEntry;
		exe = modulePath + exe;
		newEntry << newId << ",[" << moduleName << "]   " << exe;
		lines.insert(endIt, newEntry.str());

		// 5. 写入修改后的内容
		ofstream outFile(nametemp, ios::trunc);
		if (!outFile.is_open()) {
			cerr << "错误：无法写入文件 " << nametemp<< endl;
			return false;
		}

		for (const auto& l : lines) {
			outFile << l << endl;
		}
		outFile.close();

		return true;
	}
	//添加模组

	bool CreateFolderRelative(const wchar_t* relativePath) {
		// 使用宽字符版本 CreateDirectoryW 支持 Unicode
		BOOL result = CreateDirectoryW(relativePath, NULL);

		if (result) {
			return true;  // 创建成功
		}
		else {
			// 获取错误码并输出
			DWORD error = GetLastError();
			if (error == ERROR_ALREADY_EXISTS) {
				wprintf(L"文件夹已存在: %s\n", relativePath);
			}
			else {
				wprintf(L"创建失败 (错误码 %d): %s\n", error, relativePath);
			}
			return false;
		}
	}
	//创建新模组文件夹

	wstring ManualConvert(const char* utf8Str) {
		wstring wideStr;
		while (*utf8Str) {

			wideStr += static_cast<wchar_t>(*utf8Str++);
		}
		return wideStr;
	}
	//字符转换


};
//关于安装模组时的类函数集

#endif