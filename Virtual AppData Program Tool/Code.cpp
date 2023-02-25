// Default Loading Setting
// Copyright FoxaXu 2023

#include<Windows.h>
#include<fstream>
#include<string>
#include<iostream>
#include<stdio.h>
#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;

#undef UNICODE
#undef _UNICODE

bool existcheck(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}


int main(int argc, char* argv[]) {
	ofstream	 WritePoint;
	ifstream ReadPoint;

	errno_t	err = 0;
	char	fileName[100] = { 0 };
	char    ProcessFullName[_MAX_PATH] = { 0 };
	char    ProcessName[0x40] = { 0 };
	DWORD   ProcessPID = 0;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	ProcessPID = GetCurrentProcessId();
	GetModuleFileNameA(NULL, ProcessFullName, _MAX_PATH);

	tmp1 = strrchr((char*)ProcessFullName, '\\');
	tmp2 = strrchr((char*)ProcessFullName, '.');
	memcpy(ProcessName, tmp1 + 1, min(tmp2 - tmp1 - 1, 0x40));

	SetConsoleTitle("Virtual AppData Program");

	if (argc == 1) {

		string PFN = ProcessFullName;

		CreateDirectoryA("Root", 0);

		string charcode = ".\\Root\\quotation.mark";
		bool retQUO = existcheck(charcode);
		if (retQUO) {}
		else
		{
			string durl = "https://api.foxaxu.com/res/char/quotation.mark";
			LPCWSTR LcURL = stringToLPCWSTR(durl);
			string dsp = ".\\Root\\quotation.mark";
			LPCWSTR LcSP = stringToLPCWSTR(dsp);

			HRESULT applydownload = URLDownloadToFileW(
				nullptr,
				LcURL,
				LcSP,
				0,
				nullptr
			);

			bool retdownload = existcheck(dsp);
			if (retdownload) {}
			else
			{
				cout << "VAP requires some auxiliary files, " << endl;
				cout << "Cannot Connect Server. Please check your Internet" << endl;
				getchar();
				return 0;
			}
		}

		delete[] charcode.c_str();

		string quo;
		ReadPoint.open(".\\Root\\quotation.mark");
		ReadPoint >> quo;
		ReadPoint.close();

		WritePoint.open("Root\\SetEnv.bat");
		WritePoint << "@echo off" << endl;
		WritePoint << "set AppData=%cd%\\Root\\Users\\VAP\\AppData\\Roaming" << endl; 
		WritePoint << "set LOCALAPPDATA=%cd%\\Root\\Users\\VAP\\AppData\\Local" << endl;
		WritePoint << "set PUBLIC=%cd%\\Root\\Users\\Public" << endl;
		WritePoint << "set UserName=VAP" << endl;
		WritePoint << "set USERPROFILE=%cd%\\Root\\Users\\VAP" << endl;

		// Add Env to here


		WritePoint << quo + PFN + quo +" -setenvsucceed" << endl;
		WritePoint << "exit" << endl;
		WritePoint.close();



		ShellExecute(0, "open", "Root\\SetEnv.bat", 0, 0, SW_SHOW);
		return 0;
	}

	if (argc == 2) {

		string charcode = ".\\Root\\quotation.mark";
		bool retQUO = existcheck(charcode);
		if (retQUO) {}
		else
		{
			string durl = "https://api.foxaxu.com/res/char/quotation.mark";
			LPCWSTR LcURL = stringToLPCWSTR(durl);
			string dsp = ".\\Root\\quotation.mark";
			LPCWSTR LcSP = stringToLPCWSTR(dsp);

			HRESULT applydownload = URLDownloadToFileW(
				nullptr,
				LcURL,
				LcSP,
				0,
				nullptr
			);

			bool retdownload = existcheck(dsp);
			if (retdownload) {}
			else
			{
				cout << "VAP requires some auxiliary files, " << endl;
				cout << "Cannot Connect Server. Please check your Internet" << endl;
				getchar();
				return 0;
			}
		}

		delete[] charcode.c_str();

		string quo;
		ReadPoint.open(".\\Root\\quotation.mark");
		ReadPoint >> quo;
		ReadPoint.close();


		int alang = 0;
		alang < argc;
		
		alang++;
		string Verify = argv[alang];
		if (Verify == "-setenvsucceed") {
			// Put code in here
			// Start Run

			WritePoint.open("Taskkill.bat");
			WritePoint << "@echo off" << endl;
			WritePoint << "taskkill /f /im " << ProcessPID << endl;
			WritePoint << "exit" << endl;
			WritePoint.close();

			ofstream SessionLock;
			SessionLock.open("Root\\session.lock");
			SessionLock << "Copyright FoxaXu 2023" << endl;

			cout << "Welcome to Virtual AppData Program" << endl;
			cout << "Some Setting is change" << endl;
			cout << "%AppData% %LOCALAPPDATA% %PUBLIC% %UserName% %USERPROFILE%" << endl;
			cout << "More info please visit https://developer.foxaxu.com/vapt" << endl;
			cout << "Path:  " << ProcessFullName << endl;
			cout << "Type program to run" << endl;
			string Dialog;
		MainPage:
			cout << "VAP $";
			getline(cin, Dialog);

			bool retProgram = existcheck(Dialog);
			if (retProgram) {
				ShellExecute(0, "open", Dialog.c_str(), 0, 0, SW_SHOW);
				cout << endl;
				goto MainPage;
			}
			else
			{
				printf("your write seems has some problem but we can try to run this program");
				ShellExecute(0, "open", Dialog.c_str(), 0, 0, SW_SHOW);
				cout << endl << endl;
				goto MainPage;
			}

		}
		delete[] Verify.c_str();
	}
	return 0;
}