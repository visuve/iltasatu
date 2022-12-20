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
		new wxTextCtrl(this, wxID_ANY, "Your passwords will be generated here", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE)),
	_characterMask(IltasatuMask::Punctuation | IltasatuMask::Number | IltasatuMask::Uppercase | IltasatuMask::Lowercase)
{
	auto boxSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Options");
	auto gridSizer = new  wxGridSizer(6, 2, Style::Border, Style::Border);

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

	{
		auto punctuationCheckBox = new wxCheckBox(this, wxID_ANY, " ! \" # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \\ ] ^ _ ` { | } ~");
		punctuationCheckBox->SetValue((_characterMask & IltasatuMask::Punctuation) == IltasatuMask::Punctuation);

		punctuationCheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& e)->void
		{
			_characterMask ^= IltasatuMask::Punctuation;
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Punctuation:"), 1, wxEXPAND);
		gridSizer->Add(punctuationCheckBox, 1, wxEXPAND);
	}

	{
		auto numbersCheckBox = new wxCheckBox(this, wxID_ANY, " 0 1 2 3 4 5 6 7 8 9");
		numbersCheckBox->SetValue((_characterMask & IltasatuMask::Number) == IltasatuMask::Number);

		numbersCheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& e)->void
		{
			_characterMask ^= IltasatuMask::Number;
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Numbers:"), 1, wxEXPAND);
		gridSizer->Add(numbersCheckBox, 1, wxEXPAND);
	}

	{
		auto uppercaseCheckBox = new wxCheckBox(this, wxID_ANY, " A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
		uppercaseCheckBox->SetValue((_characterMask & IltasatuMask::Uppercase) == IltasatuMask::Uppercase);

		uppercaseCheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& e)->void
		{
			_characterMask ^= IltasatuMask::Uppercase;
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Uppercase:"), 1, wxEXPAND);
		gridSizer->Add(uppercaseCheckBox, 1, wxEXPAND);
	}

	{
		auto lowercaseCheckBox = new wxCheckBox(this, wxID_ANY, " a b c d e f g h i j k l m n o p q r s t u v w x y z");
		lowercaseCheckBox->SetValue((_characterMask & IltasatuMask::Lowercase) == IltasatuMask::Lowercase);

		lowercaseCheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& e)->void
		{
			_characterMask ^= IltasatuMask::Lowercase;
		});

		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Lowecase:"), 1, wxEXPAND);
		gridSizer->Add(lowercaseCheckBox, 1, wxEXPAND);
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
	options.Mask = _characterMask;

	IltasatuHandle iltasatu = IltasatuInitialize(options);

	for (size_t i = 0; i < _passwordCount; ++i)
	{
		const char* rawPassword = IltasatuGenerate(iltasatu);
		auto password = wxString::FromAscii(rawPassword, _passwordLength);

		_passwordList->AppendText(password + '\n');
	}

	IltasatuDelete(iltasatu);
}
