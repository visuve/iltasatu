#include "pch.hpp"
#include "iltasatu_gui.hpp"
#include "mainwindow.hpp"

wxIMPLEMENT_APP(Iltasatu);

bool Iltasatu::OnInit()
{
	wxLog::SetActiveTarget(new wxLogStderr());
	auto window = new MainWindow();
	window->Show(true);
	window->CenterOnScreen();

	SetTopWindow(window);

	return true;
}