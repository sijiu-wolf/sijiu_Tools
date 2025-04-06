#include "func.h"

// ʵ�� FormatSystemTimeToString ����
string FormatSystemTimeToString(SYSTEMTIME systemTime) {
	FILETIME fileTime, localFileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);
	FileTimeToLocalFileTime(&fileTime, &localFileTime); // ת��Ϊ����ʱ��

	SYSTEMTIME localSystemTime;
	FileTimeToSystemTime(&localFileTime, &localSystemTime); // ʹ�ñ���ʱ��

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

// ������ת��Ϊ�ַ���
string intToString(int value) {
	stringstream ss;
	ss << value;
	return ss.str();
}

// ʵ�� cm_judge ����
short cm_judge(string cm) {
	log_er('j', "�߼��ж�: ���� = " + cm);
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
		log_er('r', "��װģ�����");
		if (adm == true) {
			reg();
			return 0;
		}
		else {
			cout << "\a";
			cerr << "��Ȩ�ޣ������Ƿ��Թ���Աģʽ����";
			log_er('r', "����ʧ�ܣ���Ȩ��");
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
		cout << "������Ҫɾ����ģ����>";
		string moduleName;
		cin >> moduleName;
		if (deleteModule(moduleName)) {
			cout << "ģ��ɾ���ɹ���" << endl;
			log_er('d', "ɾ��ģ��: " + moduleName);
		}
		else {
			cout << "ģ��ɾ��ʧ�ܣ�" << endl;
			log_er('e', "ɾ��ģ��ʧ��: " + moduleName);
		}
		return 0;
	}
	else {
		cout << endl << "\"\a" << cm << "\"" << "����һ����Ч��ָ��" << endl << "\n";
		log_er('e', "��Ч����: " + cm);
		return 0;
	}
}
//�߼��ж�

void inm() {
	log_er('i', "��ȡģ���б�");
	string Module_temp;
	fstream infile;
	infile.open("./.ass/mod_list.ini", ios::in);  

	if (!infile.is_open()) {
		cerr << "�����޷���ģ���б��ļ� './.ass/mod_list.ini'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		log_er('e', "�ļ���ʧ��: ./ass/mod_list.ini");
		return;
	}

	cout << "--------------����ģ��-------------------" << endl;

	while (infile >> Module_temp) {
		if (Module_temp == "end") {
			break;
		}
		cout << Module_temp << endl;
	}

	if (infile.bad()) {
		cerr << "���󣺶�ȡģ���б�ʱ��������" << endl;
		log_er('e', "��ȡģ���б�ʱ��������");
	}

	infile.close();
	cout << "------------------------------------------" << endl;
}
//����ģ���б�

void help() {
	log_er('h', "��ȡ�����б�");
	string ct;
	fstream infile;
	infile.open("./.ass/config.ini", ios::in);  // ��ȷָ���Զ�ȡģʽ���ļ�

	if (!infile.is_open()) {
		cerr << "�����޷��������ļ� './.ass/config.ini'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		log_er('e', "�ļ���ʧ��: ./ass/config.ini");
		return;
	}

	cout << "--------------�����б�-------------------" << endl;
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
		cerr << "���󣺶�ȡ�����б�ʱ��������" << endl;
		log_er('e', "��ȡ�����б�ʱ��������");
	}

	infile.close();
	cout << "------------------------------------------" << endl;
}
//��������б�

bool Adm() {
	log_er('a', "Ȩ�޼��");
	string Administrator;
	fstream infile;
	infile.open("./.ass/config.ini", ios::in);  // ��ȷָ���Զ�ȡģʽ���ļ�

	if (!infile.is_open()) {
		cerr << "�����޷��������ļ� './.ass/config.ini'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		log_er('e', "�ļ���ʧ��: ./ass/config.ini");
		return false;
	}

	while (infile >> Administrator) {
		if (Administrator == "Administrator=") {
			infile >> Administrator;
			if (Administrator == "1") {
				infile.close();
				return true;
			}
			log_er('a', "��Ȩ��");
			infile.close();

			return false;
		}
	}

	if (infile.bad()) {
		cerr << "���󣺶�ȡ����ԱȨ������ʱ��������" << endl;
		log_er('e', "��ȡ����ԱȨ������ʱ��������");
	}

	infile.close();
	return false;
}
//Ȩ�޼��

void start() {
	log_er('s', "����ģ��");
	cout << "��ѡ����Ҫ������ģ��>";
	string Module_temp, s("start ");
	short sm;

	cin >> sm;
	if (cin.fail()) {
		cin.clear();  // �������״̬
		cerr << "����������Ч��������һ�����֡�" << endl;
		log_er('e', "������Ч: ����������");
		return;
	}

	sm = sm * 2;
	fstream infile;
	infile.open("./.ass/mod_list.ini", ios::in);  // ��ȷָ���Զ�ȡģʽ���ļ�

	if (!infile.is_open()) {
		cerr << "�����޷���ģ���б��ļ� './.ass/mod_list.ini'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		log_er('e', "�ļ���ʧ��: ./ass/mod_list.ini");
		return;
	}

	while (sm--) {
		infile >> Module_temp;
		if (infile.eof()) {
			cerr << "����ģ���ų�����Χ��" << endl;
			log_er('e', "ģ���ų�����Χ");
			infile.close();
			return;
		}
	}

	infile.close();

	s.append(Module_temp);
	const char* p = s.data();
	int result = system(p);

	if (result != 0) {
		cerr << "��������ģ��ʱ�������󣬷��ش���: " << result << endl;

		// ʹ�� stringstream �� int ת��Ϊ string
		stringstream ss;
		ss << result;
		string resultStr = ss.str();

		log_er('e', "����ģ��ʧ��: ���ش��� = " + resultStr);
	}
	else {
		cout << "������ָ��ģ��" << endl;
	}
}
//����

// ���� log_er ����
void log_er(char log) {
	log_er(log, "");  // ���� log_er(char, const string&) �����ݿ��ַ���
}

void log_er(char log, const string& message) {
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	string Time = FormatSystemTimeToString(systemTime);
	fstream file;
	file.open("log.txt", ios::app);  // ��׷��ģʽ����־�ļ�

	if (!file.is_open()) {
		cerr << "�����޷�����־�ļ� 'log.txt'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		return;
	}

	file << "[" << Time << "] ";
	switch (log) {
	case 's':
		file << "[����ģ��] ";
		break;
	case 'i':
		file << "[��ȡģ���б�] ";
		break;
	case 'h':
		file << "[��ȡ�����б�] ";
		break;
	case 'j':
		file << "[�߼��ж�] ";
		break;
	case 'a':
		file << "[Ȩ�޼��] ";
		break;
	case 'e':
		file << "[����] ";
		break;
	case 'p':
		file << "[��������]";
		break;
	case 'r':
		file << "[��װģ��]";
		break;
	case 'd':  // ����ɾ����������
		file << "[ɾ��ģ��] ";
		break;
	default:
		file << "[δ֪����] ";
		break;
	}
	file << message << endl;  // ��¼����Ĵ�����Ϣ
	file.close();
}
//д����־

string in(string txt) {
	log_er('i', "��ȡ�����ļ�: " + txt);
	string txt_temp, a;
	fstream infile;
	infile.open("./languages/zh-ch.txt", ios::in);  // ��ȷָ���Զ�ȡģʽ���ļ�

	if (!infile.is_open()) {
		cerr << "�����޷��������ļ� './languages/zh-ch.txt'�������ļ��Ƿ���ڻ�Ȩ���Ƿ��㹻��" << endl;
		log_er('e', "�ļ���ʧ��: ./languages/zh-ch.txt");
		return "";  // ���ؿ��ַ���
	}

	while (infile >> txt_temp) {
		if (txt_temp == txt) {
			infile >> txt_temp;
			if (txt_temp == "end") {
				break;
			}
			a = txt_temp;
			infile.close();
			return a;  // ���ض�ȡ�����ַ���
		}
	}

	infile.close();
	return "";  // ���û���ҵ�ƥ����ı������ؿ��ַ���
}
//��ȡ����

void reg() {
	namespace fs = std::filesystem;
	outfile o;
	string path, name,temp,exe;
	cout << "��������Ҫ��װģ�������>";
	log_er('r', "����ģ����"); 
	cin >> name;
	log_er('r', name);
	temp = "./mods/" + name;
	const char* p = temp.c_str();
	std::wstring widePath = o.ManualConvert(p);
	const wchar_t* folderPath = widePath.c_str();

	
	cout << "��������Ҫ��װ��ģ��ľ���·��>";
	cin >> path;
	log_er('r', path);
	cout << "������ģ��Ŀ�ִ�г���(.exe/.bat��)>";
	cin >> exe;
	log_er('r', exe);


	if (o.insertModule(name, path,exe)) {
		cout << "ģ����ӳɹ���" << endl;
	}
	else {
		cout << "ģ�����ʧ�ܣ�" << endl;
	}


	try {
		fs::copy(
			path,                          // Դ·��
			temp,                     // Ŀ��·��
			fs::copy_options::recursive |  // �ݹ鸴��
			fs::copy_options::overwrite_existing  // ���������ļ�
		);
		std::cout << "ģ�鰲װ�ɹ���" << std::endl;
	}
	catch (const fs::filesystem_error& e) {  // �����쳣����
		std::cerr << "����: " << e.what() << std::endl;
		log_er('e', "ģ�鰲װʧ��: " + string(e.what()));
	}
}
//��װģ�麯��

bool deleteModule(const string& moduleName) {
	string nametemp;
	const string filename = "mod_list.ini";
	nametemp = "./.ass/" + filename;
	vector<string> lines;
	string line;
	bool found = false;

	// 1. ��ȡ�ļ�����
	ifstream inFile(nametemp);
	if (!inFile.is_open()) {
		cerr << "�����޷����ļ� " << nametemp << endl;
		return false;
	}

	while (getline(inFile, line)) {
		// 2. ����ƥ���ģ����
		if (line.find(moduleName) != string::npos && line != "end") {
			found = true;
			continue; // ����Ҫɾ������
		}
		lines.push_back(line);
	}
	inFile.close();

	if (!found) {
		cerr << "����δ�ҵ�ģ�� " << moduleName << endl;
		return false;
	}

	// 3. �����������
	int currentId = 1;
	for (auto& l : lines) {
		if (l.empty() || l.find("end") != string::npos) continue;
		size_t commaPos = l.find(',');
		if (commaPos != string::npos) {
			l = to_string(currentId++) + l.substr(commaPos);
		}
	}

	// 4. д���ļ�
	ofstream outFile(nametemp, ios::trunc);
	if (!outFile.is_open()) {
		cerr << "�����޷�д���ļ� " << nametemp << endl;
		return false;
	}

	for (const auto& l : lines) {
		outFile << l << endl;
	}
	outFile.close();

	// 5. ɾ��ģ���ļ�
	namespace fs = std::filesystem;
	string modPath = "./mods/" + moduleName;
	try {
		if (fs::exists(modPath)) {
			fs::remove_all(modPath);
			cout << "��ɾ��ģ���ļ�: " << modPath << endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "�ļ�ɾ������: " << e.what() << endl;
	}

	return true;
}
