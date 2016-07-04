// ForgeRender.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ForgeRenderer.h"
#include "AppFramework.h"

using namespace Forge;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DeviceType type = DT_Soft;
	std::wstring device_type(lpCmdLine);
	if (device_type == L"soft")
		type = DT_Soft;
	else if (device_type == L"d3d11")
		type = DT_D3D11;

	AppFrameworkPtr app = std::make_shared<AppFramework>();
	if (!app->Initialize(hInstance, 800, 600, L"一个简单的光栅化渲染器实现"))
		return 1;
	app->Run();
	app->ShutDown();
	return 0;
}