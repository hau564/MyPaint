#pragma once

#include<wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>

#include "Path.h"
#include "Shape.h"
#include "Layer.h"
#include "History.h"

#include "ActionNewObject.h"
#include "ActionTransform.h"

#include "EditorDraw.h"
#include "EditorMouse.h"
#include "EditorShape.h"
#include "EditorText.h"

#include "ToolsSelection.h"

class DrawingCanvas : public wxWindow, public ToolsSelection
{
public:
    DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int width = 1000, int height = 750);
    ~DrawingCanvas();

    void SetExplorer(Explorer* explorer);
    void SetMode(int mode);

    int GetMode();
    void TransformCanvas(int id);

    void OnExport(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnReset(wxCommandEvent& event);
    void Reset();

    void onKeyDown(wxKeyEvent& event);
    void onKeyUp(wxKeyEvent& event);
    void onChar(wxKeyEvent& event);
    void onMouseWheel(wxMouseEvent& event);

    void AddPath(Object* path);
    void AddUndoneAction(Action* action);

    void FinishDrawing();

    enum {
        CURSOR = 1,
        DRAW = 2,
        SHAPE = 4,
        TEXT = 16,
        ERASER = 32,
    };

private:

    void draw(wxGraphicsContext* gc);

    void TransformEvent(wxMouseEvent &event);
    void Scale(wxPoint2DDouble pos, double scale);
    void Move(wxPoint2DDouble move);

    void onMouseDown(wxMouseEvent&);
    void onMouseUp(wxMouseEvent&);
    void onPaint(wxPaintEvent&);
    void onMouseMove(wxMouseEvent& event);
    void onMouseLeave(wxMouseEvent& event);
    void onZoom(wxCommandEvent& event);

private:
    int width, height;
    wxPoint2DDouble paperPos;

    int mode = CURSOR;
    wxMouseEvent lastEvent;
    wxComboBox *zoomComboBox;

    std::vector<Layer*> layers;
    Layer* activeLayer;
    Editor* editor;
    History* history;

    wxAffineMatrix2D scaleMatrix, imatrix;
};
