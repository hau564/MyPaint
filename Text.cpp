#include "Text.h"

Text::Text(wxPoint2DDouble pos, wxColour color, int size)
	:pos(pos), color(color), size(size)
{
	font = wxFont(size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
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
	gc->GetTextExtent(text, &width, &height);
	gc->PopState();
}

void Text::BuildSelectionBox()
{
	selectionBox.Build(pos.m_x, pos.m_y, width, height);
}
