#include "pch.hpp"

#include "mainwindow.hpp"

namespace Style
{
	constexpr long Frame = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX);
	constexpr int Border = 5;
}

MainWindow::MainWindow() :
	wxFrame(nullptr, wxID_ANY, wxT("Iltasatu"), wxDefaultPosition, wxSize(800, 600), Style::Frame),
	_passwordList(
		new wxTextCtrl(this, wxID_ANY, "Your passwords will be generated here", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE))
{
	auto boxSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Options");
	auto gridSizer = new  wxGridSizer(2, 2, Style::Border, Style::Border);

	{
		auto passwordLengthSpin = new wxSpinCtrl(
			this,
			wxID_ANY,
			wxEmptyString,
			wxDefaultPosition,
			wxDefaultSize,
			wxSP_ARROW_KEYS | wxALIGN_RIGHT,
			3,
			100,
			_passwordLength);

		passwordLengthSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
		{
			_passwordLength = e.GetValue();
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Password length:"), 1, wxEXPAND);
		gridSizer->Add(passwordLengthSpin, 1, wxEXPAND);
	}

	{
		auto passwordCountSpin = new wxSpinCtrl(
			this,
			wxID_ANY,
			wxEmptyString,
			wxDefaultPosition,
			wxDefaultSize,
			wxSP_ARROW_KEYS | wxALIGN_RIGHT,
			1,
			1000,
			_passwordCount);

		passwordCountSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
		{
			_passwordCount = e.GetValue();
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Password count:"), 1, wxEXPAND);
		gridSizer->Add(passwordCountSpin, 1, wxEXPAND);
	}

	boxSizer->Add(gridSizer, 2, wxEXPAND);

	{
		auto generateButton = new wxButton(this, wxID_ANY, wxT("Generate!"));

		generateButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)->void
		{
			GeneratePasswords();
		});

		boxSizer->Add(generateButton, 1, wxEXPAND);
	}

	boxSizer->Add(_passwordList, 15, wxEXPAND);

	SetSizer(boxSizer);
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
