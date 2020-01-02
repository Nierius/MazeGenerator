#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "canvas.h"
#include "mazegenerator.h"


class Canvas;
/**
 * @class cMain
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 03/01/20
 * @file cmain.h
 * @brief Application frame inherited from wxFrame
 */
class cMain : public wxFrame
{
public:
	/**
	 * @brief Constructor for the class.
	 */
    cMain();
	
	/**
	 * @brief Default destructor.
	 */
    ~cMain();
    
	/**
	 * @brief Button click event handler
	 * @param evt Command Event
	 */
    void OnButtonClicked(wxCommandEvent &evt);
    
private:
    Canvas* m_canvas;
	
    wxButton* m_drawbtn = nullptr;
	wxButton* m_launchGen = nullptr;
	
	wxStaticText* m_amountlabel = nullptr;
	wxSpinCtrl* m_amount = nullptr;
	wxStaticText* m_sleeplabel = nullptr;
	wxSpinCtrl* m_sleep = nullptr;
	
};

