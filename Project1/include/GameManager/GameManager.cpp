#include "GameManager.h"

#include "../../resource.h"

#include "../Share/Timer/Timer.h"
#include "Device/Device.h"
#include "../Asset/AssetManager.h"
#include "../Shader/ShaderManager.h"

#include "../Share/SharedPtr/SharedPtr.h"
#include "../Share/Object/Object.h"
#include "../Share/Log/Log.h"


#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Shader/ShaderClass/Shader.h"

#include "../Shader/ConstantBuffer/Transform/TransformCBuffer.h"
#include "../Scene/SceneManager.h"

#include "ProfileManager/ProfileManager.h"

#include "../Render/RenderManager.h"
#include "../Render/RenderState.h"
#include "../Render/RenderStateManager.h"

//Gameinfo에 extern을 선언해준다.
//그럼 Gameinfo를 받아간 파일들은 모두 gRootPath를 사용할수있다.
TCHAR gRootPath[MAX_PATH];


bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}
CGameManager::~CGameManager()
{
	// 소멸자
	CLog::Destroy();


	// DC 반납
	ReleaseDC(mhWnd, mhDC);
}


bool CGameManager::Init(HINSTANCE hInst)
{
	mhInst = hInst;

	lstrcpy(mClassName, TEXT("Project1"));
	lstrcpy(mTitleName, TEXT("Project1"));

	RegisterWindowClass();

	if (!Create())
	{
		return false;
	}

	if (!CLog::Init())
	{
		return false;
	}

	// DC : 디바이스 컨텍스트
	// 주의사항 -> GetDC 꼭 해제 해줘야한다.
	mhDC = GetDC(mhWnd);

	// 게임 초기화
	if (!CDevice::GetInst()->Init(mhWnd, 1280, 720, true))
	{
		MessageBox(nullptr, L"Device Init Failed", L"Error", MB_OK);
		return false;
	}

	// Render 매니저
	if (!CRenderManager::GetInst()->Init())
	{
		return false;
	}
	
	if (!CShaderManager::GetInst()->Init())
	{
		MessageBox(nullptr, L"ShaderManager Init Failed", L"Error", MB_OK);
		return false;
	}

	if (!CAssetManager::GetInst()->Init())
	{
		MessageBox(nullptr, L"AssetManager Init Failed", L"Error", MB_OK);
		return false;
	}

	// Collision Profile 매니저 초기화
	if (!CProfileManager::GetInst()->Init())
	{
		return false;
	}

	CTimer::Init();

	if (!CSceneManager::GetInst()->Init())
	{
		MessageBox(nullptr, L"SceneManager Init Failed", L"Error", MB_OK);
		return false;
	}
	


	return true;
}

int CGameManager::Run()
{
	MSG msg;	// 운영체제가 만들어 주는 메세지를 전달 받기 위한 구조체
	// PeekMessage : 메세지큐의 메세지를 얻어오는 함수
	// 이 함수는 메세지큐가 비어있을 경우 바로 빠져나오면서 0 을 반환한다.
	// 메세지큐에 메세지가 있다면 해당 메세지를 가져온다.
	while (mLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 메세지를 처리하는 함수
			// 키보드 입력 메세지가 발생할 경우 동작한다.
			TranslateMessage(&msg);
			// WndProc 함수로 메세지를 전달해주는 함수다.
			DispatchMessage(&msg);
		}
		else
		{
			// 윈도우 데드타임
			// 여기서 부터 게임을 만들 수 있게 된다.
			Logic();
		}
	}

	return (int)msg.wParam;

	
}

void CGameManager::Logic()
{
	float DeltaTime = CTimer::Update();	// 델타타임 구하기
	Input(DeltaTime);
	Update(DeltaTime);
	Collision(DeltaTime);
	Render(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{
	CSceneManager::GetInst()->Input(DeltaTime);
}

void CGameManager::Update(float DeltaTime)
{
	CSceneManager::GetInst()->Update(DeltaTime);

	//CLog::PrintLog("GameManager Update", ELogPrintType::All);

	static bool push = false;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		push = true;
	}
	else if (push)
	{
		push = false;
		CLog::SaveLog();
	}
}

void CGameManager::Collision(float DeltaTime)
{
	CSceneManager::GetInst()->Collision(DeltaTime);
}

void CGameManager::Render(float DeltaTime)
{
	CDevice::GetInst()->ClearBackBuffer(mClearColor);
	CDevice::GetInst()->ClearDepthStencil(1.f, 0);
	CDevice::GetInst()->SetTarget();

	// 출력
	// 블랜드스테이트 세팅
	// CRenderState* AlphaBlend = CRenderManager::GetInst()->GetStateManager()->FindState("AlphaBlend");

	// if (AlphaBlend)
	// {
	// 	AlphaBlend->SetState();
	// }

	CSceneManager::GetInst()->Render();

	CRenderManager::GetInst()->Render();

	//블렌드 스테이트 회수 
	// if (AlphaBlend)
	// {
	// 	AlphaBlend->ResetState();
	// }

	CDevice::GetInst()->Render();
}

ATOM CGameManager::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	// 윈도우 클래스 구조체의 크기를 나타낸다. 반드시 지정되어야 한다.
	wcex.cbSize = sizeof(WNDCLASSEX);

	// 윈도우 클래스의 스타일을 지정한다.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// 메세지를 처리하는 함수의 포인터
	wcex.lpfnWndProc = WndProc;

	// 윈도우 클래스에 대한 추가 메모리를 지정한다.
	wcex.cbClsExtra = 0;

	// 윈도우 인스턴스에 대한 추가 메모리를 지정한다.
	wcex.cbWndExtra = 0;

	// 운영체제에서 부여해준 HINSTANCE를 지정해준다.
	wcex.hInstance = mhInst;

	// 실행파일 아이콘을 지정한다.
	// 솔루션 탐색기 -> 리소스 파일-> 우클릭 -> 추가-> 리소스-> 아이콘 새로만들기
	wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IDI_ICON1));

	// 커서 모양
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);

	// 클라이언트 영역의 색상 지정
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// 윈도우 메뉴 지정
	wcex.lpszMenuName = 0;		// 0을 넣으면 메뉴가 없는 윈도우가 된다.

	// 윈도우 클래스의 이름을 지정한다.
	wcex.lpszClassName = mClassName;

	// 타이틀 바 왼쪽의 아이콘을 의미한다.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	// 위에서 설정한 윈도우 클래스를 등록한다.
	return RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
	// CreateWindowW : 윈도우 창을 생성해주는 함수이다.
	// 잘못된 생성일 경우 0 을 반환한다.
	mhWnd = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mhInst, nullptr);

	if (!mhWnd)
	{
		return FALSE;
	}

	RECT WindowRC = { 0, 0, 1280, 720 };

	AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, WindowRC.right - WindowRC.left, WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(mhWnd, SW_SHOW);
	UpdateWindow(mhWnd);


	return TRUE;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SYSKEYDOWN:
		if (wParam == VK_F4)
		{
			mLoop = false;
			DestroyWindow(hWnd);
		}
		break;
	
	case WM_DESTROY:
		mLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
