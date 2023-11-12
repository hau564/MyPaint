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

private:   
    
    void OnExit(wxCommandEvent& event);
    void OnExport(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);

private:
    DrawingCanvas *canvas;
    Panel* panel;
    
};

enum {
    ID_Export = 1
};

#endif // !MY_FRAME_H