using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using CppUIThreadApp.Resources;
using CppUIThreadComponent;

namespace CppUIThreadApp
{
    public partial class MainPage : PhoneApplicationPage
    {
        private WindowsPhoneRuntimeComponent _component = new WindowsPhoneRuntimeComponent();

        private ComponentDispatcher _nativeDispatcher = new ComponentDispatcher();

        // Constructor
        public MainPage()
        {
            InitializeComponent();

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
            _nativeDispatcher.SetDequeueDelegate(DequeueUIDispatchActivity);
        }

        public void DequeueUIDispatchActivity()
        {
            Dispatcher.BeginInvoke(() =>
            {
                _nativeDispatcher.DequeueUIDispatchActivity();
            });
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            _component.DoUIThreadTest();
        }


        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}
    }
}