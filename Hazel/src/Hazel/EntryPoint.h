#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main()
{
	Hazel::Log::Init();

	HZ_CORE_TRACE("Welcome to Hazel Engine! {0}", "Wang.ZhiNang");
	HZ_INFO("Initilized!");

    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif