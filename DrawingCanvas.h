#pragma once

#ifndef DRAWING_CANVAS_H
#define DRAWING_CANVAS_H

#include<wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>

#include "Path.h"
#include "Layer.h"
#include "History.h"
#include "ActionNewObject.h"
#include "EditorDraw.h"
#include "EditorMouse.h"

class DrawingCanvas : public wxWindow
{
public:
    DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    ~DrawingCanvas();

    void SetExplorer(Explorer* explorer);
    void SetPenColor(wxColor color);
    void SetPenSize(int size);
    void SetMode(int mode);

    wxColor GetPenColor() const { return penColor; }
    int GetPenSize() const { return penSize; }

    void OnExport(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);

    void onKeyDown(wxKeyEvent& event);
    void onKeyUp(wxKeyEvent& event);

    void AddPath(Path* path);

    enum {
        CURSOR = 1,
        DRAW = 2,
        SHAPE = 4,
        TEXT = 16,
        ERASER = 32,
    };

private:

    void draw(wxGraphicsContext* gc);

    void onMouseDown(wxMouseEvent&);
    void onMouseUp(wxMouseEvent&);
    void onPaint(wxPaintEvent&);
    void onMouseMove(wxMouseEvent& event);
    void onMouseLeave(wxMouseEvent& event);

private:
    wxColor penColor = wxColor(0, 0, 0);
    int penSize = 1;

    std::vector<Layer*> layers;
    Layer* activeLayer;
    Editor* editor;
    History* history;
};

#endif // !DRAWING_CANVAS_H