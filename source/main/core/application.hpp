#pragma once

#include "window.hpp"

class Application
{
public:
	Application();

	void run();
private:
	Window m_window;
};