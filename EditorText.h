#pragma once

#include "Editor.h"
#include "Text.h"

class EditorText : public Editor
{
public:
	EditorText(DrawingCanvas* parent);

	void OnMouseDown(wxMouseEvent& event) override;
	void OnMouseMove(wxMouseEvent& event) override;
	void OnMouseUp(wxMouseEvent& event) override;
	void OnMouseLeave(wxMouseEvent& event) override;
	void OnKeyDown(wxKeyEvent& event) override;
	void OnChar(wxKeyEvent& event) override;

	void Draw(wxGraphicsContext* gc) override;
private:
	Text* text;
	std::string charSet = " `1234567890-=qwertyuiop[]\asdfghjkl;zxcvbnm,./\'!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>?";
};
