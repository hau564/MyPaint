#pragma once

#include "Editor.h"
#include "Text.h"
#include <map>

class EditorText : public Editor
{
public:
	EditorText(DrawingCanvas* parent);

	void OnMouseDown(wxMouseEvent& event) override;
	void OnMouseMove(wxMouseEvent& event) override;
	void OnMouseUp(wxMouseEvent& event) override;
	void OnMouseLeave(wxMouseEvent& event) override;
	void OnKeyDown(wxKeyEvent& event) override;
	void OnKeyUp(wxKeyEvent& event) override;
	void OnChar(wxKeyEvent& event) override;
	void Finish() override;

	void Draw(wxGraphicsContext* gc) override;
private:
	Text* text;
	std::map<int, int> up;
};
