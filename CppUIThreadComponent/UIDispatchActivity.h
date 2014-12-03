#pragma once

#include <queue>
#include <agile.h>

namespace CppUIThreadComponent
{
	public delegate void DequeueActivity(Platform::String^ sName);

	class UIDispatchActivity abstract
	{
	public:
		virtual void DoActivity() = 0;
		virtual Platform::String^ Name() = 0;
	};

	public ref class ComponentDispatcher sealed
	{
	public:
		ComponentDispatcher();
		void SetDequeueDelegate(DequeueActivity^ delegate) 
				{ m_delegate = delegate; };
		void DequeueUIDispatchActivity();

	internal:
		void EnqueueUIDispatchActivity(UIDispatchActivity* pActivity);

	private:
		std::queue<UIDispatchActivity*> m_qDispatch;
		Platform::Agile<DequeueActivity> m_delegate;
	};
}

CppUIThreadComponent::ComponentDispatcher^ GetNativeDispatcher();