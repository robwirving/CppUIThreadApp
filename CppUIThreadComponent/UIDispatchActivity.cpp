#include "pch.h"
#include "UIDispatchActivity.h"

CppUIThreadComponent::ComponentDispatcher^ g_NativeDispatcher;

CppUIThreadComponent::ComponentDispatcher^ GetNativeDispatcher()
{
	return g_NativeDispatcher;
}

namespace CppUIThreadComponent 
{
	ComponentDispatcher::ComponentDispatcher()
	{
		g_NativeDispatcher = this;
	}

	void ComponentDispatcher::DequeueUIDispatchActivity()
	{
		// This method is called from the C# dispatcher on the UI Thread!
		m_qDispatch.front()->DoActivity();
		m_qDispatch.pop();
	}

	void ComponentDispatcher::EnqueueUIDispatchActivity(UIDispatchActivity* pActivity)
	{
		m_qDispatch.push(pActivity);
		m_delegate->Invoke();
	}
}
