#pragma once

#include"../shload.h"

string $$DownloadURL;
string $$SavePath;

int argcsize = 0;
int skipmainload = 0;

int returncodeN = 0;

void argsApi(string args$api) {
	if (args$api == args$api) {
		argcsize++;
		if (argcsize == 1) {
			$$DownloadURL = args$api;
			return;
		}
		if (argcsize == 2) {
			$$SavePath = args$api;
			_prtendl();
			_prtoutmsg("Simple Download Toolkit v1");
			_prtoutmsg("Starting Download	");
			_prtoutmsg("URL :    " + $$DownloadURL);
			_prtoutmsg("Save :   " + $$SavePath);
			_prtendl();
			_prtoutmsg("If your url has Special characters, Please use \"URL\" format");
			_prtendl();
			_prtendl();
			skipmainload = 1;
			bool testexample = _urldown_api($$DownloadURL, $$SavePath);
			if (testexample) {
				_prtoutmsg("Download OK");
				returncodeN = 0;
			}
			else {
				_prtoutmsg("Download Failed");
				returncodeN = 1;
			}

			return;
		}

		return;
	}
}

int _HeadMainLoad() {
	if (skipmainload == 1) {
		return 0;
	}
	_prtendl();
	_prtoutmsg("Simple Download Toolkit v1");
	_prtoutmsg("Command Format :   ");
	_prtoutmsg("                               simdl <URL> <SavePath>");
	_prtoutmsg("  Copyright FoxaXu 2024");
	_pause();
	return returncodeN;
}