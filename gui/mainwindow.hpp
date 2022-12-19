#pragma once

class MainWindow : public wxFrame
{
public:
	MainWindow();

	void GeneratePasswords();

private:
	wxTextCtrl* _passwordList = nullptr;
	size_t _passwordLength = 0;
	size_t _passwordCount = 0;
};