#pragma once

#include "../../GameInfo.h"

enum class ELogPrintType
{
	Conole,
	VisualOutput,
	All
};

class CLog
{
private:

	static vector<string> mVecLog;
	static HANDLE hConsole;

public:
	static bool Init();
	static void Destroy();


public:
	static void PrintLog(const string& Text, ELogPrintType PrintType = ELogPrintType::All);
	static void SaveLog();
};

