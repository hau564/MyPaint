#pragma once

#ifndef MY_FRAME_H
#define MY_FRAME_H

#include <wx/wx.h>
#include "DrawingCanvas.h"
#include "ColorPane.h"
#include "Panel.h"




class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);

private:   
    void BuildMenuBar();
    
    void OnExit(wxCommandEvent& event);
    void OnExport(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnHistory(wxCommandEvent& event);
    void OnResetCanvas(wxCommandEvent& event);

private:
    DrawingCanvas *canvas;
    Panel* panel;
    Explorer* explorer;

    wxSplitterWindow* splitter;
    wxSplitterWindow* splitter2;
};

enum {
    ID_Export = 1
};

#endif // !MY_FRAME_H