#pragma once

#include "MainPage.g.h"

namespace App14
{
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void DelayedInit();
		void DelayedNavigation();
		Windows::UI::Xaml::Controls::SwapChainPanel^ GetSwapChainPanel();

		bool mDelayedInitializeDone;
	};
}
