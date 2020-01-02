#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/dcbuffer.h>
#include "cmain.h"


class cMain;

/**
 * @class Canvas
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 02/01/20
 * @file canvas.h
 * @brief Drawing surface inherited from wxPanel
 */
class Canvas : public wxPanel
{
public:
	/**
	 * @brief Constructor for the class.
	 * @param parent
	 */
	explicit Canvas(cMain* parent);

	/**
	 * @brief Default destructor.
	 */
	~Canvas();

	/**
	 * @brief Paint event handler
	 * @param evt wxPaintEvent
	 */
	void OnPaint(wxPaintEvent& evt);

private:
	wxPen _pen;
	wxDECLARE_EVENT_TABLE();
};
