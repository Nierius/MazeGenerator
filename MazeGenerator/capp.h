#pragma once

#include <wx/wx.h>
#include "cmain.h"

/**
 * @class cApp
 * @author Marius Niemenmaa (GitHub/LokSrc)
 * @date 03/01/20
 * @file capp.h
 * @brief Application inherited from wxApp
 */
class cApp : public wxApp
{
public:
	/**
	 * @brief Constructor for the class.
	 */
	cApp();

	/**
	 * @brief Default destructor.
	 */
	~cApp();

	/**
	 * @brief Set-up Application
	 * @return true: everytime
	 */
	virtual bool OnInit();

private:
	cMain* m_frame = nullptr;

};
