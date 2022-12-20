#pragma once

class MainWindow : public wxFrame
{
public:
	MainWindow();

	void GeneratePasswords();

private:
	wxTextCtrl* _passwordList = nullptr;
	size_t _passwordLength = 6;
	size_t _passwordCount = 10;
	uint32_t _characterMask;
};