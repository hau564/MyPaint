#include "Text.h"

Text::Text(wxPoint2DDouble pos, wxColour color, int size, wxFont font)
	:pos(pos), color(color), size(size), font(font)
{
	this->font = wxFont(size, font.GetFamily(), font.GetStyle(), font.GetWeight(), font.GetUnderlined(), font.GetFaceName());
}

void Text::Pop()
{
	if (!text.empty())
		text.pop_back();
}

void Text::Append(char c)
{
	text.push_back(c);
}

void Text::DrawContent(wxGraphicsContext* gc)
{
	wxGraphicsMatrix matrix = gc->GetTransform();
	matrix.Concat(gc->CreateMatrix(selectionBox.GetTotalTransformMatrix()));
	gc->PushState();
	gc->SetTransform(matrix);
	gc->SetFont(font, color);
	gc->DrawText(text, pos.m_x, pos.m_y);

	double w = 0;
	std::string t = "";
	for (char c : text) {
		if (c == '\n') {
			gc->GetTextExtent(t, &w, &height);
			width = std::max(width, w);
			t.clear();
		}
		else
			t += c;
	}
	gc->GetTextExtent(t, &w, &height);
	width = std::max(width, w);

	gc->GetTextExtent(text, &w, &height);
	gc->PopState();
}

void Text::BuildSelectionBox()
{
	selectionBox.Build(pos.m_x, pos.m_y, width, height);
}
