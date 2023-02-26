//DL    -fullname =  download
// Use Windows API

#include<Windows.h>
#include<iostream>
#include<fstream>
#pragma comment(lib,"URlmon.lib")

#undef UNICODE
#undef _UNICODE

using namespace std;

LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

bool existcheck(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << endl << endl;
		cout << "Help" << endl;
		cout << "       Format:   dl %DownloadURL% %SavePath%" << endl;
		cout << "   Use Windows API Download" << endl;
		cout << "   Maybe cannot running in PE Environment" << endl << endl;
		return 0;
	}
	if (argc == 2) {
		cout << endl << endl;
		cout << "Help" << endl;
		cout << "       Format:   dl %DownloadURL% %SavePath%" << endl;
		cout << "   Use Windows API Download" << endl;
		cout << "   Maybe cannot running in PE Environment" << endl << endl;
		return 0;
	}
	if (argc == 3) {
		int argvlang = 0;
		argvlang < argc;

		argvlang++;
		string durl = argv[argvlang];
		argvlang++;
		string dsp = argv[argvlang];

		bool retDSP = existcheck(dsp);

		LPCWSTR LcDsp = stringToLPCWSTR(dsp);
		LPCWSTR LcDURL = stringToLPCWSTR(durl);

		char delmark[20];
		strcpy_s(delmark, dsp.c_str());

		if (retDSP) {
			remove(delmark);
		}

		cout << endl;
		cout << "Start Download Service" << endl;
		cout << "URL:  " << durl << endl;
		cout << "Save Path:  " << dsp << endl << endl;

		HRESULT applydownload = URLDownloadToFileW(
			nullptr,
			LcDURL,
			LcDsp,
			0,
			nullptr
		);
		bool retDSPsucc = existcheck(dsp);
		if (retDSPsucc) {
			cout << endl;
			cout << "Download Task Successfully" << endl;
			cout << "Task Ending. Process Exit" << endl << endl;;
			return 22;
		}
		else
		{
			cout << endl;
			cout << "Download Task Failed" << endl;
			cout << "Check your internet and URL" << endl;
			cout << "Task Ending. Process Exit" << endl << endl;
			return 999;
		}
	}
	cout << "Command Error" << endl;
	return 0;
}