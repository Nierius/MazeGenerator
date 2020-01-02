#include "cmain.h"

cMain::cMain()
	: wxFrame(nullptr, wxID_ANY, "Maze Generator", wxPoint(0, 0), wxSize(1000, 850))
{
	this->Centre(wxBOTH);

	// Canvas setup
	m_canvas = new Canvas(this);

	// Button setup
	m_drawbtn = new wxButton(this, 10001, "Initialize maze", wxPoint(825, 140), wxSize(150, 50));
	m_drawbtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
	m_launchGen = new wxButton(this, 10002, "Launch generation", wxPoint(825, 190), wxSize(150, 50));
	m_launchGen->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
	m_launchGen->Hide();

	// Spinbox setup
	m_amountlabel = new wxStaticText(this, wxID_ANY, "Target cell amount: ",wxPoint(825, 5));
	m_amount = new wxSpinCtrl(this, wxID_ANY, "100", wxPoint(825, 25), wxSize(150,40), wxSP_ARROW_KEYS, 100, 50000, 100);
	m_amountlabel = new wxStaticText(this, wxID_ANY, "Sleep time (ms): ",wxPoint(825, 70));
	m_sleep = new wxSpinCtrl(this, wxID_ANY, "10", wxPoint(825, 90), wxSize(150,40), wxSP_ARROW_KEYS, 0, 150, 10);
}

cMain::~cMain()
{
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	MazeGenerator& mazeGen = MazeGenerator::getInstance();

	if (evt.GetEventObject() == m_launchGen) {
		bool status = mazeGen.startGeneration();
		std::cout << "Maze generation finished!" << std::endl;
		m_launchGen->Hide();
		if (status) {
			m_drawbtn->Enable();
			m_amount->Enable();
			m_sleep->Enable();
		}
	} else {
		mazeGen.setCanvas(m_canvas);
		mazeGen.initBlocks(m_amount->GetValue(), m_sleep->GetValue());

		m_drawbtn->Disable();
		m_amount->Disable();
		m_sleep->Disable();

		m_launchGen->Show();
	}
	evt.Skip();
}
