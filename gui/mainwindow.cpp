#include "pch.hpp"

#include "mainwindow.hpp"

namespace Styles
{
	constexpr long Frame = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX);
	constexpr int Border = 3;
}

MainWindow::MainWindow() :
	wxFrame(nullptr, wxID_ANY, wxT("Iltasatu"), wxDefaultPosition, wxSize(600, 800), Styles::Frame),
	_passwordList(
		new wxTextCtrl(this, wxID_ANY, "Your passwords will be generated here", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE))
{
	auto sizer = new wxBoxSizer(wxVERTICAL);

	{
		auto passwordLength = new wxSpinCtrl(
			this,
			wxID_ANY,
			wxT("Password length"),
			wxDefaultPosition,
			wxDefaultSize,
			wxSP_ARROW_KEYS | wxALIGN_RIGHT,
			3,
			128,
			0);

		passwordLength->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
		{
			_passwordLength = e.GetValue();
		});

		sizer->Add(passwordLength, 1, wxEXPAND | wxALL, Styles::Border);
	}

	{
		auto passwordCount = new wxSpinCtrl(
			this,
			wxID_ANY,
			wxT("Password count"),
			wxDefaultPosition,
			wxDefaultSize,
			wxSP_ARROW_KEYS | wxALIGN_RIGHT,
			1,
			1000,
			0);

		passwordCount->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
		{
			_passwordCount = e.GetValue();
		});

		sizer->Add(passwordCount, 1, wxEXPAND | wxALL, Styles::Border);
	}

	{
		auto generateButton = new wxButton(this, wxID_ANY, wxT("Generate!"));

		generateButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)->void
		{
			GeneratePasswords();
		});

		sizer->Add(generateButton, 1, wxEXPAND | wxALL, Styles::Border);
	}

	sizer->Add(_passwordList, 1, wxEXPAND | wxALL, Styles::Border);

	SetSizer(sizer);
}

void MainWindow::GeneratePasswords()
{
	_passwordList->Clear();

	IltasatuOptions options;
	options.Size = _passwordLength;
	options.Mask = IltasatuMask::Uppercase | IltasatuMask::Lowercase;

	IltasatuHandle iltasatu = IltasatuInitialize(options);

	for (size_t i = 0; i < _passwordCount; ++i)
	{
		const char* rawPassword = IltasatuGenerate(iltasatu);
		auto password = wxString::FromAscii(rawPassword, _passwordLength);

		_passwordList->AppendText(password);
		_passwordList->AppendText('\n');
	}

	IltasatuDelete(iltasatu);
}
