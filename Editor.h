#pragma once

#ifndef EDITOR_H
#define EDITOR_H

#include <wx/wx.h>

class DrawingCanvas;

class Editor
{
public:
	Editor(DrawingCanvas *parent);

	virtual void OnMouseDown(wxMouseEvent event) = 0;
	virtual void OnMouseUp(wxMouseEvent event) = 0;
	virtual void OnMouseLeave(wxMouseEvent event) = 0;
	virtual void OnMouseMove(wxMouseEvent event) = 0;
protected:
	DrawingCanvas* parent;
};

#endif