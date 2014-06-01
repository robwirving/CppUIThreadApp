#pragma once

namespace CppUIThreadComponent
{
    public ref class WindowsPhoneRuntimeComponent sealed
    {
    public:
        WindowsPhoneRuntimeComponent();

		void DoUIThreadTest();
		static void OnPositionChanged(Windows::Devices::Geolocation::Geolocator ^sender, Windows::Devices::Geolocation::PositionChangedEventArgs ^args);
	};
}