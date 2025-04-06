#include "func.h"

// 实现 FormatSystemTimeToString 函数
string FormatSystemTimeToString(SYSTEMTIME systemTime) {
	FILETIME fileTime, localFileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);
	FileTimeToLocalFileTime(&fileTime, &localFileTime); // 转换为本地时间

	SYSTEMTIME localSystemTime;
	FileTimeToSystemTime(&localFileTime, &localSystemTime); // 使用本地时间

	tm localTime = {};
	localTime.tm_year = localSystemTime.wYear - 1900;
	localTime.tm_mon = localSystemTime.wMonth - 1;
	localTime.tm_mday = localSystemTime.wDay;
	localTime.tm_hour = localSystemTime.wHour;
	localTime.tm_min = localSystemTime.wMinute;
	localTime.tm_sec = localSystemTime.wSecond;

	char buffer[100];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
	return string(buffer);
}

// 将整数转换为字符串
string intToString(int value) {
	stringstream ss;
	ss << value;
	return ss.str();
}

// 实现 cm_judge 函数
short cm_judge(string cm) {
	log_er('j', "逻辑判断: 命令 = " + cm);
	bool adm;
	if (cm == "inm") {
		inm();
		return 0;
	}
	else if (cm == "help") {
		help();
		return 0;
	}
	else if (cm == "exit") {
		return 1;
	}
	else if (cm == "reg") {
		adm = Adm();
		log_er('r', "安装模组访问");
		if (adm == true) {
			reg();
			return 0;
		}
		else {
			cout << "\a";
			cerr << "无权限，请检查是否以管理员模式启动";
			log_er('r', "访问失败，无权限");
			return 0;
		}
	}
	else if (cm == "start") {
		start();
		return 0;
	}
	else if (cm == "modout") {
		return 0;
	}
	else if (cm == "del") {
		cout << "请输入要删除的模组名>";
		string moduleName;
		cin >> moduleName;
		if (deleteModule(moduleName)) {
			cout << "模组删除成功！" << endl;
			log_er('d', "删除模组: " + moduleName);
		}
		else {
			cout << "模组删除失败！" << endl;
			log_er('e', "删除模组失败: " + moduleName);
		}
		return 0;
	}
	else {
		cout << endl << "\"\a" << cm << "\"" << "不是一个有效的指令" << endl << "\n";
		log_er('e', "无效命令: " + cm);
		return 0;
	}
}
//逻辑判断

void inm() {
	log_er('i', "读取模块列表");
	string Module_temp;
	fstream infile;
	infile.open("./.ass/mod_list.ini", ios::in);  

	if (!infile.is_open()) {
		cerr << "错误：无法打开模块列表文件 './.ass/mod_list.ini'，请检查文件是否存在或权限是否足够。" << endl;
		log_er('e', "文件打开失败: ./ass/mod_list.ini");
		return;
	}

	cout << "--------------可用模块-------------------" << endl;

	while (infile >> Module_temp) {
		if (Module_temp == "end") {
			break;
		}
		cout << Module_temp << endl;
	}

	if (infile.bad()) {
		cerr << "错误：读取模块列表时发生错误。" << endl;
		log_er('e', "读取模块列表时发生错误");
	}

	infile.close();
	cout << "------------------------------------------" << endl;
}
//读入模组列表

void help() {
	log_er('h', "读取帮助列表");
	string ct;
	fstream infile;
	infile.open("./.ass/config.ini", ios::in);  // 明确指定以读取模式打开文件

	if (!infile.is_open()) {
		cerr << "错误：无法打开配置文件 './.ass/config.ini'，请检查文件是否存在或权限是否足够。" << endl;
		log_er('e', "文件打开失败: ./ass/config.ini");
		return;
	}

	cout << "--------------帮助列表-------------------" << endl;
	infile >> ct;
	if (ct == "helpl") {
		while (infile >> ct) {
			if (ct == "end") {
				break;
			}
			cout << ct << endl;
		}
	}

	if (infile.bad()) {
		cerr << "错误：读取帮助列表时发生错误。" << endl;
		log_er('e', "读取帮助列表时发生错误");
	}

	infile.close();
	cout << "------------------------------------------" << endl;
}
//读入帮助列表

bool Adm() {
	log_er('a', "权限检查");
	string Administrator;
	fstream infile;
	infile.open("./.ass/config.ini", ios::in);  // 明确指定以读取模式打开文件

	if (!infile.is_open()) {
		cerr << "错误：无法打开配置文件 './.ass/config.ini'，请检查文件是否存在或权限是否足够。" << endl;
		log_er('e', "文件打开失败: ./ass/config.ini");
		return false;
	}

	while (infile >> Administrator) {
		if (Administrator == "Administrator=") {
			infile >> Administrator;
			if (Administrator == "1") {
				infile.close();
				return true;
			}
			log_er('a', "无权限");
			infile.close();

			return false;
		}
	}

	if (infile.bad()) {
		cerr << "错误：读取管理员权限配置时发生错误。" << endl;
		log_er('e', "读取管理员权限配置时发生错误");
	}

	infile.close();
	return false;
}
//权限检查

void start() {
	log_er('s', "启动模块");
	cout << "请选择需要启动的模块>";
	string Module_temp, s("start ");
	short sm;

	cin >> sm;
	if (cin.fail()) {
		cin.clear();  // 清除错误状态
		cerr << "错误：输入无效，请输入一个数字。" << endl;
		log_er('e', "输入无效: 非数字输入");
		return;
	}

	sm = sm * 2;
	fstream infile;
	infile.open("./.ass/mod_list.ini", ios::in);  // 明确指定以读取模式打开文件

	if (!infile.is_open()) {
		cerr << "错误：无法打开模块列表文件 './.ass/mod_list.ini'，请检查文件是否存在或权限是否足够。" << endl;
		log_er('e', "文件打开失败: ./ass/mod_list.ini");
		return;
	}

	while (sm--) {
		infile >> Module_temp;
		if (infile.eof()) {
			cerr << "错误：模块编号超出范围。" << endl;
			log_er('e', "模块编号超出范围");
			infile.close();
			return;
		}
	}

	infile.close();

	s.append(Module_temp);
	const char* p = s.data();
	int result = system(p);

	if (result != 0) {
		cerr << "错误：启动模块时发生错误，返回代码: " << result << endl;

		// 使用 stringstream 将 int 转换为 string
		stringstream ss;
		ss << result;
		string resultStr = ss.str();

		log_er('e', "启动模块失败: 返回代码 = " + resultStr);
	}
	else {
		cout << "已启动指定模块" << endl;
	}
}
//启动

// 重载 log_er 函数
void log_er(char log) {
	log_er(log, "");  // 调用 log_er(char, const string&) 并传递空字符串
}

void log_er(char log, const string& message) {
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	string Time = FormatSystemTimeToString(systemTime);
	fstream file;
	file.open("log.txt", ios::app);  // 以追加模式打开日志文件

	if (!file.is_open()) {
		cerr << "错误：无法打开日志文件 'log.txt'，请检查文件是否存在或权限是否足够。" << endl;
		return;
	}

	file << "[" << Time << "] ";
	switch (log) {
	case 's':
		file << "[启动模组] ";
		break;
	case 'i':
		file << "[读取模组列表] ";
		break;
	case 'h':
		file << "[读取帮助列表] ";
		break;
	case 'j':
		file << "[逻辑判断] ";
		break;
	case 'a':
		file << "[权限检查] ";
		break;
	case 'e':
		file << "[错误] ";
		break;
	case 'p':
		file << "[程序启动]";
		break;
	case 'r':
		file << "[安装模组]";
		break;
	case 'd':  // 新增删除操作类型
		file << "[删除模组] ";
		break;
	default:
		file << "[未知操作] ";
		break;
	}
	file << message << endl;  // 记录具体的错误信息
	file.close();
}
//写入日志

string in(string txt) {
	log_er('i', "读取语言文件: " + txt);
	string txt_temp, a;
	fstream infile;
	infile.open("./languages/zh-ch.txt", ios::in);  // 明确指定以读取模式打开文件

	if (!infile.is_open()) {
		cerr << "错误：无法打开语言文件 './languages/zh-ch.txt'，请检查文件是否存在或权限是否足够。" << endl;
		log_er('e', "文件打开失败: ./languages/zh-ch.txt");
		return "";  // 返回空字符串
	}

	while (infile >> txt_temp) {
		if (txt_temp == txt) {
			infile >> txt_temp;
			if (txt_temp == "end") {
				break;
			}
			a = txt_temp;
			infile.close();
			return a;  // 返回读取到的字符串
		}
	}

	infile.close();
	return "";  // 如果没有找到匹配的文本，返回空字符串
}
//读取函数

void reg() {
	namespace fs = std::filesystem;
	outfile o;
	string path, name,temp,exe;
	cout << "请输入需要安装模块的名字>";
	log_er('r', "输入模块名"); 
	cin >> name;
	log_er('r', name);
	temp = "./mods/" + name;
	const char* p = temp.c_str();
	std::wstring widePath = o.ManualConvert(p);
	const wchar_t* folderPath = widePath.c_str();

	
	cout << "请输入需要安装的模组的绝对路径>";
	cin >> path;
	log_er('r', path);
	cout << "请输入模组的可执行程序(.exe/.bat等)>";
	cin >> exe;
	log_er('r', exe);


	if (o.insertModule(name, path,exe)) {
		cout << "模组添加成功！" << endl;
	}
	else {
		cout << "模组添加失败！" << endl;
	}


	try {
		fs::copy(
			path,                          // 源路径
			temp,                     // 目标路径
			fs::copy_options::recursive |  // 递归复制
			fs::copy_options::overwrite_existing  // 覆盖现有文件
		);
		std::cout << "模组安装成功！" << std::endl;
	}
	catch (const fs::filesystem_error& e) {  // 修正异常类型
		std::cerr << "错误: " << e.what() << std::endl;
		log_er('e', "模组安装失败: " + string(e.what()));
	}
}
//安装模组函数

bool deleteModule(const string& moduleName) {
	string nametemp;
	const string filename = "mod_list.ini";
	nametemp = "./.ass/" + filename;
	vector<string> lines;
	string line;
	bool found = false;

	// 1. 读取文件内容
	ifstream inFile(nametemp);
	if (!inFile.is_open()) {
		cerr << "错误：无法打开文件 " << nametemp << endl;
		return false;
	}

	while (getline(inFile, line)) {
		// 2. 查找匹配的模组名
		if (line.find(moduleName) != string::npos && line != "end") {
			found = true;
			continue; // 跳过要删除的行
		}
		lines.push_back(line);
	}
	inFile.close();

	if (!found) {
		cerr << "错误：未找到模组 " << moduleName << endl;
		return false;
	}

	// 3. 重新生成序号
	int currentId = 1;
	for (auto& l : lines) {
		if (l.empty() || l.find("end") != string::npos) continue;
		size_t commaPos = l.find(',');
		if (commaPos != string::npos) {
			l = to_string(currentId++) + l.substr(commaPos);
		}
	}

	// 4. 写回文件
	ofstream outFile(nametemp, ios::trunc);
	if (!outFile.is_open()) {
		cerr << "错误：无法写入文件 " << nametemp << endl;
		return false;
	}

	for (const auto& l : lines) {
		outFile << l << endl;
	}
	outFile.close();

	// 5. 删除模组文件
	namespace fs = std::filesystem;
	string modPath = "./mods/" + moduleName;
	try {
		if (fs::exists(modPath)) {
			fs::remove_all(modPath);
			cout << "已删除模组文件: " << modPath << endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "文件删除错误: " << e.what() << endl;
	}

	return true;
}
