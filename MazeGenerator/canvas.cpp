#include "canvas.h"

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT  (Canvas::OnPaint)
wxEND_EVENT_TABLE()

Canvas::Canvas(cMain* parent) :
	wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize(801,801)), _pen(wxPen())
{
	_pen = wxPen(wxColour(255,255,255));
}

Canvas::~Canvas()
{
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	wxBufferedPaintDC dc(this);
	dc.SetPen(_pen);
	dc.Clear();

	wxRegionIterator upd(GetUpdateRegion());
	while (upd) {
		wxRect rect(upd.GetRect());
		std::vector<std::shared_ptr<Block> > blocks =
		    MazeGenerator::getInstance().getBlocksInside(rect);

		for (auto& block : blocks) {
			block->Draw(dc);
		}
		upd++;
	}
	this->SetFocus();
	evt.Skip();
}
