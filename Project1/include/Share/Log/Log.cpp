#include "Log.h"


// 전역변수라 초기화 한번 해주자
vector<string> CLog::mVecLog;
HANDLE CLog::hConsole;

bool CLog::Init()
{
#ifdef _DEBUG
	// 콘솔창 열기
	AllocConsole();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#else

#endif // _DEBUG
// # 붙으면 보통 전처리기
// 컴파일러 전에 전처리기가 코드 한 번 정리



	// 공간 10000개 예약해두자
	// size opacity
	// reserve
	// resize 는 저거 둘다
	mVecLog.reserve(10000);
	// mVecLog.resize(10000);


	return true;
}
void CLog::Destroy()
{
#ifdef _DEBUG
	// 콘솔창 닫기
	FreeConsole();
#else

#endif
}

void CLog::PrintLog(const string& Text, ELogPrintType PrintType)
{
	// 로그 출력 시
	// 시간 출력
	// LPSYSTEMTIME;
	SYSTEMTIME sysTime;

	// UTC 표준시간
	// GetSystemTime(&sysTime);

	// 지역시간
	GetLocalTime(&sysTime);

	char TimeText[256] = {};

	sprintf_s(TimeText, "[%d_%d_%d_%d_%d_%d_%d]", 
		sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

	string OutputText = TimeText;

	OutputText += " : ";
	OutputText += Text;
	OutputText += " \n ";
	mVecLog.emplace_back(OutputText);

	DWORD Number = 0;
	switch (PrintType)
	{
	case ELogPrintType::Conole:
		WriteConsoleA(hConsole, OutputText.c_str(), (DWORD)OutputText.length(), &Number, nullptr);
		break;
	case ELogPrintType::VisualOutput:
		OutputDebugStringA(OutputText.c_str());
		break;
	case ELogPrintType::All:
		WriteConsoleA(hConsole, OutputText.c_str(), (DWORD)OutputText.length(), &Number, nullptr);
		OutputDebugStringA(OutputText.c_str());
		break;
	// default:
		// break;
	}
}

void CLog::SaveLog()
{
	// 로그 출력시
	// 시간 출력
	// LPSYSTEMTIME;
	SYSTEMTIME sysTime;

	// UTC 표준시간
	// GetSystemTime(&sysTime);

	// 지역시간
	GetLocalTime(&sysTime);


	

	char TimeText[256] = {};

	sprintf_s(TimeText, "bin/Log/[%d_%d_%d %d_%d_%d_%d].txt", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

	// 파일 열기
	FILE* File = nullptr;
	fopen_s(&File, TimeText, "wt");

	if (!File)
	{
		return;
	}

	size_t Size = mVecLog.size();

	for (size_t i = 0; i < Size; i++)
	{
		// 한 줄씩 넣겠다.
		fputs(mVecLog[i].c_str(), File);
	}

	// 파딜 닫기
	fclose(File);

}


