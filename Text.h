#pragma once

#include "Object.h"

class Text : public Object
{
public:
	Text(wxPoint2DDouble pos, wxColour color, int size);

	void Pop();
	void Append(char c);

	void BuildSelectionBox() override;
private:
	void DrawContent(wxGraphicsContext* gc) override;

	std::string text;
	wxColour color;
	wxFont font;
	int size;
	wxPoint2DDouble pos;
	double width, height;
};

