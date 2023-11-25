// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>
#include "MyFrame.h"

class MyApp : public wxApp
{
public:
    MyFrame* frame;
    bool OnInit() override;
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);
    DECLARE_EVENT_TABLE()
};

wxIMPLEMENT_APP(MyApp);

BEGIN_EVENT_TABLE(MyApp, wxApp)
    EVT_KEY_DOWN(MyApp::OnKeyDown)
    EVT_KEY_UP(MyApp::OnKeyUp)
    //EVT_CHAR_HOOK(MyApp::OnChar)
END_EVENT_TABLE()

bool MyApp::OnInit()
{
    frame = new MyFrame();
    frame->Show(true);
    return true;
}

void MyApp::OnKeyDown(wxKeyEvent& event)
{
    frame->OnKeyDown(event);
}

void MyApp::OnKeyUp(wxKeyEvent& event)
{
    frame->OnKeyUp(event);
}

void MyApp::OnChar(wxKeyEvent& event)
{
    frame->OnChar(event);
}
