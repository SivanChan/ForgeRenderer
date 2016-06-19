
#include "stdafx.h"
#include "AppFramework.h"
#include "RenderDevice.h"
#include "Resource.h"

namespace Forge
{
	AppFramework::AppFramework() : hwnd_(NULL), hinstance_(NULL), class_name_(L"ForgeRender")
	{

	}

	AppFramework::~AppFramework()
	{

	}

	bool AppFramework::Initialize(HINSTANCE hInstance, uint32_t width, uint32_t height, std::wstring const & title_name)
	{
		// initialize window
		if (!InitializeWindow(hInstance, width, height, title_name))
			return false;

		// initialize device
		if (!InitializeDevice())
			return false;

		return true;
	}

	void AppFramework::ShutDown()
	{
		if (render_device_)
			render_device_->ShutDown();

		::DestroyWindow(hwnd_);
		hwnd_ = NULL;

		UnregisterClass(class_name_.c_str(), hinstance_);
		hinstance_ = NULL;
	}

	void AppFramework::Run()
	{
		MSG msg;
		bool done = false;

		ZeroMemory(&msg, sizeof(MSG));
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				if (!FrameMove())
				{
					done = true;
				}
			}
		}
	}

	bool AppFramework::FrameMove()
	{
		render_device_->FrameMove();
		return true;
	}

	LRESULT CALLBACK AppFramework::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			::PostQuitMessage(0);
			return 0;
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK AppFramework::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		AppFramework* win = reinterpret_cast<AppFramework*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
		if (win)
			return win->MessageHandler(hWnd, uMsg, wParam, lParam);
		else
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	bool AppFramework::InitializeWindow(HINSTANCE hInstance, uint32_t width, uint32_t height, std::wstring const & title_name)
	{
		WNDCLASSEX wc;
		int x, y;
		hinstance_  = hInstance;
		title_name_ = title_name;
		width_      = width;
		height_     = height;

		// setup
		wc.style         = CS_BYTEALIGNCLIENT;
		wc.lpfnWndProc   = AppFramework::WndProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = hinstance_;
		wc.hIcon         = LoadIcon(hinstance_, MAKEINTRESOURCE(IDI_FORGERENDER));
		wc.hIconSm       = LoadIcon(hinstance_, MAKEINTRESOURCE(IDI_SMALL));
		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = class_name_.c_str();
		wc.cbSize        = sizeof(WNDCLASSEX);

		// register
		if (!RegisterClassEx(&wc))
			return false;

		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		::AdjustWindowRect(&rect, style, FALSE);

		x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;;
		y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

		// create window
		hwnd_ = CreateWindowEx(WS_EX_APPWINDOW, class_name_.c_str(), title_name.c_str(), style,
			x, y, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hinstance_, NULL);
		if (hwnd_ == NULL)
			return false;

		::SetWindowLongPtrW(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		::ShowWindow(hwnd_, SW_SHOW);
		::SetForegroundWindow(hwnd_);
		::SetFocus(hwnd_);

		return true;
	}

	bool AppFramework::InitializeDevice()
	{
		render_device_ = std::make_shared<RenderDevice>();
		return render_device_->Initialize(hwnd_, width_, height_);
	}
}