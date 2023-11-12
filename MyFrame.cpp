#include "MyFrame.h"
#include<queue>

#include<wx/splitter.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "MyPaint")
{
    CreateStatusBar();
    SetStatusText("hello");
    this->SetSize(FromDIP(800), FromDIP(500));
    this->SetMinSize({ FromDIP(400), FromDIP(200) });

    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
        
    canvas = new DrawingCanvas(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel = new Panel(splitter, canvas, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    splitter->SplitVertically(panel, canvas, FromDIP(200));
    splitter->SetMinimumPaneSize(FromDIP(100));

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_Export, "&Export\tCtrl+E");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Shift+Z");

    wxMenuBar* menuBar = new wxMenuBar;

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnExport, this, ID_Export);
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnExport(wxCommandEvent& event)
{
    canvas->OnExport(event);
}

void MyFrame::OnUndo(wxCommandEvent& event)
{
	canvas->OnUndo(event);
}

void MyFrame::OnRedo(wxCommandEvent& event)
{
	canvas->OnRedo(event);
}