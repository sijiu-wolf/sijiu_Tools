#include <iostream>
#include "func.h"
using namespace std;

string Module_status = " ", command = " ";
//全局变量

int main() {
	HWND hwnd = GetConsoleWindow();
	SetWindowText(hwnd, L"肆玖工具箱");
	//设定窗口标题栏
	short judge_return = 0;
	//初始化

	cout << "[肆玖工具箱] 版本1.00.0" << endl;

	bool jrj = true;
	while (jrj) {
		cout << in("cin");  
		cin >> command;

		judge_return = cm_judge(command);
		//输入内容判断
		switch (judge_return) {
		case 0:
			jrj = true;
			break;
		case 1:
			jrj = false;
			break;
		default:
			cerr << "错误：未知的返回值。" << endl;
			log_er('e', "未知错误");  // 记录错误日志
			break;
		}
		//判断是否要退出
	}
#ifdef _WIN32
	system("pause");
#else
	cout << "按回车键继续...";
	cin.ignore();
#endif
	//或者system("pause");

	return 0;
}
