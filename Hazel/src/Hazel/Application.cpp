#include "hzpch.h"

#include "Application.h"

#include "GLFW/glfw3.h"

namespace Hazel{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }


    Application::~Application()
    {
    }

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispather(e);
		dispather.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLay(Layer * layer)
	{
		m_LayerStack.PushOverLay(layer);
	}

    void Application::Run()
    {
        while (m_Running)
        {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
        }
    }

	
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

