// CppUIThreadComponent.cpp
#include "pch.h"
#include "CppUIThreadComponent.h"
#include "UIDispatchActivity.h"

using namespace CppUIThreadComponent;
using namespace concurrency;
using namespace Platform;
using namespace Windows::Devices::Geolocation;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Windows::ApplicationModel::Store;


class MyUIDispatchActivity : public UIDispatchActivity
{
	void DoActivity() override
	{
		// Now we are back on the UI thread! Let's try that purchase
		CurrentApp::RequestProductPurchaseAsync(ref new String(L"test.iap"), false);
		// you should see an error popup on your phone
		// but that's okay you successfully attempted a store purchase from the UI thread!
	};

	Platform::String^ Name() override
	{
		return ref new Platform::String(L"MyUIDispatchActivity");
	};
};

WindowsPhoneRuntimeComponent::WindowsPhoneRuntimeComponent()
{
}

void WindowsPhoneRuntimeComponent::DoUIThreadTest()
{
	ThreadPool::RunAsync(ref new WorkItemHandler([](IAsyncAction^) 
	{
#if 0
		// Right now we are on the thread pool, not the UI Thread
		// Because we're not on the UI thread the following code will raise an exception
		CurrentApp::RequestProductPurchaseAsync(ref new String(L"test.iap"), false);
#elif 0
		// If this were a Direct3D App we would be able to use the CoreWindow dispatcher to access the UI thread
		// But from a WinRT component the CoreWindow won't be available
		auto window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
		window->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new Windows::UI::Core::DispatchedHandler([]()
		{
			CurrentApp::RequestProductPurchaseAsync(ref new String(L"test.iap"), false);
		}));
#else
		MyUIDispatchActivity* pActivity = new MyUIDispatchActivity();
		GetNativeDispatcher()->EnqueueUIDispatchActivity(pActivity);
#endif
	}));
}

void CppUIThreadComponent::WindowsPhoneRuntimeComponent::OnPositionChanged(Geolocator ^sender, PositionChangedEventArgs ^args)
{
	throw ref new Platform::NotImplementedException();
}
