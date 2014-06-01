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
	void DoActivity()
	{
		// Now we are back on the UI thread! Let's try that purchase
		CurrentApp::RequestProductPurchaseAsync(ref new String(L"test"), false);
		// you should see an error popup on your phone
		// but that's okay you successfully attempted a store purchase from the UI thread!
	};
};

WindowsPhoneRuntimeComponent::WindowsPhoneRuntimeComponent()
{
}

void WindowsPhoneRuntimeComponent::DoUIThreadTest()
{
	ThreadPool::RunAsync(ref new WorkItemHandler([](IAsyncAction^) 
	{
		// Right now we are on the thread pool, not the UI Thread
		// Because we're not on the UI thread the following code will raise an exception
#if 0
		CurrentApp::RequestProductPurchaseAsync(ref new String(L"test"), false);
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
