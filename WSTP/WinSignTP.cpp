// Sign for windows program
//use Microsoft SDK signtool.exe and capicom.dll
// All Code in Github
#undef UNICODE
#undef _UNICODE

#include<Windows.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;

bool existcheck(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

LPCWSTR STL(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

string INIReadAPI(string api,string file, string head, string reg) {
	string B;
	B = api;
	bool retire = existcheck(B);
	if (retire) {
		string C;
		C = B + " read " + file + " " + head + " " + reg + " >>$OutINI~" + head + "~" + reg;

		system(C.c_str());

		C = "$OutINI~" + head + "~" + reg;
		
		string D;
		ifstream ReadPoint;
		ReadPoint.open(C);
		ReadPoint >> D;
		ReadPoint.close();

		remove(C.c_str());
		return D;
	}
	else {
		MessageBox(0, "IRE NOT FOUND, API Load Failed", "ERROR", MB_OK);
		B = "load.failed";
		return B;
	}
}

int main() {

	errno_t	err = 0;
	char	fileName[100] = { 0 };
	char    ProcessFullName[_MAX_PATH] = { 0 };
	DWORD   ProcessPID = 0;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	ProcessPID = GetCurrentProcessId();
	GetModuleFileNameA(NULL, ProcessFullName, _MAX_PATH);

	tmp1 = strrchr((char*)ProcessFullName, '\\');
	tmp2 = strrchr((char*)ProcessFullName, '.');

	string A = "Root\\Config.ini";
	bool retROOT = existcheck(A);
	if (retROOT) {
		//��ʽ����
		//����INI
		string SignFile = INIReadAPI("Root\\ire.exe", "Root\\Config.ini", "Cert", "File");
		string SignKey = INIReadAPI("Root\\ire.exe", "Root\\Config.ini", "Sign", "Password");
		string TimeStampSwitch = INIReadAPI("Root\\ire.exe", "Root\\Config.ini", "Cert", "TimeStamp");
		string TMServer = INIReadAPI("Root\\ire.exe", "Root\\Config.ini", "Sign", "TimeStampServer");
		
		ifstream ReadPoint;
		ofstream WritePoint;

		ReadPoint.open("Root\\quotation.mark");
		string quo;
		ReadPoint >> quo;
		ReadPoint.close();

		cout << "���ü������" << endl;
		cout << "֤��:  " << SignFile << endl;
		cout << "TimeStamp����:  " << TimeStampSwitch << endl;
		cout << "TM Server: " << TMServer << endl;
		cout << "������Ϣ����� https://developer.foxaxu.com/wstp" << endl;
		cout << "������� Root\\Config.ini ������Ӻ��޸�����,���ڿ�����ʹ�� Enabled(����) �� Disabled (����)" << endl;
		cout << "���� newsign ����ѡ��һ���ļ�����ǩ��" << endl;
		string LINE;
	BackShell:
		cout << "WinSignTP  ~$";
		getline(cin, LINE);
		if (LINE == "newsign") {
			ShellExecute(0, "runas", "Root\\NewSign.exe", 0, 0, SW_SHOW);
			cout << endl;
			goto BackShell;
		}
		bool retLine = existcheck(LINE);
		if (retLine) {}
		else {
			cout << "����������������⣬����������Ȼ�᳢��ִ���������������˫���ŵ��µĴ˴���,����Ժ���";
		}
		if (TimeStampSwitch == "Enabled") {
			WritePoint.open("$GET~SIGN.bat");
			WritePoint << "@echo off" << endl;
			WritePoint << "Root\\signtool.exe sign /f " + quo + SignFile + quo + " /p " + SignKey + " /fd SHA256 /t " + quo + TMServer + quo +" /a " +  LINE << endl;
			WritePoint << "pause" << endl;
			WritePoint << "del $GET~SIGN.bat" << endl;
			WritePoint.close();
		}
		if (TimeStampSwitch == "Disabled") {
			WritePoint.open("$GET~SIGN.bat");
			WritePoint << "@echo off" << endl;
			WritePoint << "Root\\signtool.exe sign /f " + quo + SignFile + quo + " /p " + SignKey + " /fd SHA256 " + LINE << endl;
			WritePoint << "pause" << endl;
			WritePoint << "del $GET~SIGN.bat" << endl;
			WritePoint.close();
		}

		ShellExecute(0, "open", "$GET~SIGN.bat", 0, 0, SW_SHOW);
		cout << " �����Ѿ��༭��ɣ���ʼִ��" << endl;
		cout << endl;
		goto BackShell;
	}
	else {
		//���س�ʼ�ļ�
		cout << "Connecting Server";
		CreateDirectoryA("Root", NULL);
		string durl = "https://developer.foxaxu.com/download/cppcore/dl.exe";
		LPCWSTR LcURL = STL(durl);
		string dsp = "Root\\dl.exe";
		LPCWSTR LcSP = STL(dsp);

		HRESULT applydownload = URLDownloadToFileW(
			nullptr,
			LcURL,
			LcSP,
			0,
			nullptr
		);

		bool retdownload = existcheck(dsp);
		if (retdownload) {
			ShellExecute(0, "open", "Root\\dl.exe", "https://developer.foxaxu.com/download/cppcore/ire.exe Root\\ire.exe", 0, SW_HIDE);
			ShellExecute(0, "open", "Root\\dl.exe", "https://developer.foxaxu.com/download/cpptools/NewSign.exe Root\\NewSign.exe", 0, SW_HIDE);
			ShellExecute(0, "open", "Root\\dl.exe", "https://gitcode.net/FoxaXu1/download/-/raw/master/Capicom/signtool.exe Root\\signtool.exe", 0, SW_HIDE);
			ShellExecute(0, "open", "Root\\dl.exe", "https://api.foxaxu.com/res/char/quotation.mark Root\\quotation.mark", 0, SW_HIDE);
			ShellExecute(0, "open", "Root\\dl.exe", "https://api.foxaxu.com/settings/timestamp.txt Root\\timestamp.txt", 0, SW_HIDE);
			A = "C:\\Windows\\SysWOW64\\cmd.exe";
			bool retBitTest = existcheck(A);
			if (retBitTest) {
				A = "C:\\Windows\\SysWOW64\\capicom.dll";
				bool retCAPICOMTest = existcheck(A);
				if (retCAPICOMTest) {}
				else {
					cout << endl;
					cout << "Your System has no capicom.dll. We need Administrator to install this dll file, We need your allow" << endl;
					cout << "You can check this dll digital certificate. Issued by Microsoft Corporation" << endl;
					cout << "y/n  $";
					string Dialog;
					getline(cin, Dialog);
					if (Dialog == "y") goto AllowSC;
					if (Dialog == "Y") goto AllowSC;
					cout << "Prepare Run Dll Failed" << endl;
					cout << "User Cancel" << endl;
					Sleep(5000);
					return 0;
				}
			}
			else {
				A = "C:\\Windows\\System32\\capicom.dll";
				bool retCAPICOMTest = existcheck(A);
				if (retCAPICOMTest) {}
				else {
					cout << endl;
					cout << "Your System has no capicom.dll. We need Administrator to install this dll file, We need your allow" << endl;
					cout << "You can check this dll digital certificate. Issued by Microsoft Corporation" << endl;
					cout << "y/n  $";
					string Dialog;
					getline(cin, Dialog);
					if (Dialog == "y") goto AllowSC;
					if (Dialog == "Y") goto AllowSC;
					cout << "Prepare Run Dll Failed" << endl;
					cout << "User Cancel" << endl;
					Sleep(5000);
					return 0;
				}
			}
			// ������� 
			goto SkipSetupCAPICOM;

		AllowSC:
			if (retBitTest) {
				string temp = getenv("temp");
				string scbat, copynew;
				scbat = temp + "\\SetupCapicom.bat";
				copynew = temp + "\\capicom.dll";

				ShellExecute(0, "open", "Root\\dl.exe", "https://gitcode.net/FoxaXu1/download/-/raw/master/Capicom/capicom.dll Root\\capicom.dll", 0, SW_HIDE);
				Sleep(3000);
				CopyFile("Root\\capicom.dll", copynew.c_str(),0);

				remove("Root\\capicom.dll");
				ofstream WritePoint;
				WritePoint.open(scbat);
				WritePoint << "@echo off" << endl;
				WritePoint << "copy %temp%\\capicom.dll C:\\Windows\\SysWOW64" << endl;
				WritePoint << "regsvr32 C:\\Windows\\SysWOW64\\capicom.dll" << endl;
				WritePoint << "del %temp%\\capicom.dll" << endl;
				WritePoint << "del %temp%\\SetupCapicom.bat" << endl;
				WritePoint << "exit" << endl;
				WritePoint.close();
				ShellExecute(0, "runas", scbat.c_str(), 0, 0, SW_HIDE);
			}
			else {
				string temp = getenv("temp");
				string scbat, copynew;
				scbat = temp + "\\SetupCapicom.bat";
				copynew = temp + "\\capicom.dll";

				ShellExecute(0, "open", "Root\\dl.exe", "https://gitcode.net/FoxaXu1/download/-/raw/master/Capicom/capicom.dll Root\\capicom.dll", 0, SW_HIDE);
				Sleep(3000);
				CopyFile("Root\\capicom.dll", copynew.c_str(), 0);

				remove("Root\\capicom.dll");
				ofstream WritePoint;
				WritePoint.open(scbat);
				WritePoint << "@echo off" << endl;
				WritePoint << "copy %temp%\\capicom.dll C:\\Windows\\System32" << endl;
				WritePoint << "regsvr32 C:\\Windows\\System32\\capicom.dll" << endl;
				WritePoint << "del %temp%\\capicom.dll" << endl;
				WritePoint << "del %temp%\\SetupCapicom.bat" << endl;
				WritePoint << "exit" << endl;
				WritePoint.close();
				ShellExecute(0, "runas", "Root\\SetupCapicom.bat", 0, 0, SW_HIDE);
			}
		SkipSetupCAPICOM:
			//��ʼ����ǩ��
			ifstream ReadPoint;
			ReadPoint.open("Root\\quotation.mark");
			string quo;
			ReadPoint >> quo;
			ReadPoint.close();

			cout << endl << endl;
			cout << "�������ǩ��" << endl;
			cout << "ѡ�����ǩ���ļ�" << endl;
			cout << "���ǲ�����֤����ļ���һ��Ĭ��֤��Ϊpfx��ʽ" << endl;
			cout << "֤��·����ò�Ҫ�����ո���ᵼ��֤���ȡ����" << endl;
			cout << "Cert File ~$";
			string CertFile;
			getline(cin, CertFile);
			A = "write .\\Root\\Config.ini Cert File " + quo + CertFile + quo;
			ShellExecute(0, "open", "Root\\ire.exe", A.c_str(), 0, SW_HIDE);
			cout << "�����֤�������" << endl;
			cout << "Cert Password ~$";
			string CertPass;
			getline(cin, CertPass);
			A = "write .\\Root\\Config.ini Sign Password " + CertPass;
			ShellExecute(0, "open", "Root\\ire.exe", A.c_str(), 0, SW_HIDE);
			cout << "�Ƿ�����timestamp����" << endl;
			cout << "Use TimeStamp Server (y/n) ~$";
			string ts;
			getline(cin, ts);
			if (ts == "y") {

				string TMServer;
				ifstream ReadPoint;
				ReadPoint.open("Root\\timestamp.txt");
				ReadPoint >> TMServer;
				ReadPoint.close();

				cout << "TimeStamp is Enabled" << endl;
				A = "write .\\Root\\Config.ini Cert TimeStamp Enabled";
				ShellExecute(0, "open", "Root\\ire.exe", A.c_str(), 0, SW_HIDE);
				A = "write .\\Root\\Config.ini Sign TimeStampServer " + TMServer;
				ShellExecute(0, "open", "Root\\ire.exe", A.c_str(), 0, SW_HIDE);
			}
			else {
				cout << "TimeStamp is Disabled" << endl;
				A = "write .\\Root\\Config.ini Cert TimeStamp Disabled";
				ShellExecute(0, "open", "Root\\ire.exe", A.c_str(), 0, SW_HIDE);
			}
			remove("Root\\timestamp.txt");
			cout << "�������" << endl;
			cout << "���������������" << endl;
			Sleep(1000);
			ShellExecute(0, "open", ProcessFullName, 0, 0, SW_SHOW);
			return 0;
		}
		else
		{
			cout << endl;
			cout << "WSTP requires some auxiliary files, " << endl;
			cout << "Cannot Connect Server. Please check your Internet" << endl;
			getchar();
			return 0;
		}
	}
}