#include "MyFrame.h"
#include<queue>

#include<wx/splitter.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>


MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "MyPaint")
{
    this->SetSize(FromDIP(800), FromDIP(500));
    this->SetMinSize({ FromDIP(400), FromDIP(200) });

    splitter2 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
    splitter = new wxSplitterWindow(splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
        
    canvas = new DrawingCanvas(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel = new Panel(splitter, canvas, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    explorer = new Explorer(splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    canvas->SetExplorer(explorer);

    splitter->SplitVertically(panel, canvas, FromDIP(260));
    splitter->SetMinimumPaneSize(FromDIP(100));

    splitter2->SplitVertically(splitter, explorer, FromDIP(1300));
    this->splitter2->Unsplit();
    explorer->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event) {
		this->splitter2->Unsplit();
		event.Skip();
	});

    BuildMenuBar();
    Maximize();

    canvas->SetMode(DrawingCanvas::DRAW);
}

void MyFrame::BuildMenuBar()
{
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_FILE3, "&Export\tCtrl+E");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Shift+Z");

    wxMenu* viewMenu = new wxMenu;
    viewMenu->Append(wxID_FILE1, "&History\tCtrl+H");
    viewMenu->Append(wxID_FILE2, "&Reset Canvas\tCtrl+R");

    wxMenuBar* menuBar = new wxMenuBar;

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(viewMenu, "&View");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnExport, this, wxID_FILE3);
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
    Bind(wxEVT_MENU, &MyFrame::OnHistory, this, wxID_FILE1);
    Bind(wxEVT_MENU, &MyFrame::OnResetCanvas, this, wxID_FILE2);
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

void MyFrame::OnHistory(wxCommandEvent& event)
{
    splitter2->SplitVertically(splitter, explorer, FromDIP(1300));
}

void MyFrame::OnResetCanvas(wxCommandEvent& event)
{
    canvas->OnReset(event);
}

void MyFrame::OnKeyDown(wxKeyEvent& event)
{
    canvas->onKeyDown(event);
    panel->OnKeyDown(event);
}

void MyFrame::OnKeyUp(wxKeyEvent& event)
{
    canvas->onKeyUp(event);
    panel->OnKeyUp(event);
}

void MyFrame::OnChar(wxKeyEvent& event)
{
    canvas->onChar(event);
}
