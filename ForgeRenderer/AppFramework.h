/********************************************************************
	created  :	2016/6/16
	author   :	Sivan
	source   :  äÖÈ¾´°¿Ú
*********************************************************************/

#ifndef Forge_RenderWindow_hpp__
#define Forge_RenderWindow_hpp__

#pragma once

#include "PreDeclare.h"

namespace Forge
{
	enum DeviceType
	{
		DT_Soft,
		DT_D3D11
	};

	class AppFramework
	{
	public:
		AppFramework();
		~AppFramework();

		bool Initialize(HINSTANCE hInstance, uint32_t width, uint32_t height, std::wstring const & title_name, DeviceType type = DT_Soft);
		void ShutDown();
		void Run();
		bool Refresh();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	protected:
		bool InitializeWindow(HINSTANCE hInstance, uint32_t width, uint32_t height, std::wstring const & title_name);
		bool InitializeDevice(DeviceType type);
		void InitCamera();
		void InitKeyboardInput();
		void InitModel();

	private:
		HWND				hwnd_;
		uint32_t			width_;
		uint32_t			height_;
		HINSTANCE			hinstance_;

		std::wstring		class_name_;
		std::wstring		title_name_;

		DeviceType          device_type_;
		RenderDevicePtr     render_device_;
		CameraPtr           camera_;
		KeyboardInputPtr    input_;
	};
}

#endif // Forge_RenderWindow_hpp__