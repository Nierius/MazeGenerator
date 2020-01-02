#include "capp.h"

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
    m_frame = new cMain();
    m_frame->Show();
    return true;
}
