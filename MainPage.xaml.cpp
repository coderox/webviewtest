#include "pch.h"
#include "MainPage.xaml.h"

using namespace App14;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

static WebView^ webView;

MainPage::MainPage()
{
	InitializeComponent();
	DelayedInit();
	DelayedNavigation();
}

SwapChainPanel^ MainPage::GetSwapChainPanel()
{
	auto win = Window::Current;
	if (win != nullptr && webView != nullptr) {
		auto page = dynamic_cast<Page^>(win->Content);
		if (page != nullptr) {
			return dynamic_cast<SwapChainPanel^>(page->Content);
		}
	}
	return nullptr;
}

void MainPage::DelayedInit() {
	if (mDelayedInitializeDone) {
		return;
	}

	auto dispatcher = CoreWindow::GetForCurrentThread()->Dispatcher;

	if (dispatcher != nullptr) {
		dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]() {
			webView = ref new WebView();
			auto swapChainPanel = GetSwapChainPanel();
			if (swapChainPanel != nullptr) {
				swapChainPanel->Children->Append(webView);
				//webView->Visibility = ::Visibility::Collapsed;
				mDelayedInitializeDone = true;
			}
		}));
	}
}

void MainPage::DelayedNavigation() {
	auto dispatcher = CoreWindow::GetForCurrentThread()->Dispatcher;

	if (dispatcher != nullptr) {
		dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]() {
			webView->Navigate(ref new Uri(L"http://www.bing.com"));
		}));
	}
}

