#include "Object.h"

void Object::DrawBox(wxGraphicsContext* gc)
{
	selectionBox.Draw(gc);
}

void Object::Draw(wxGraphicsContext* gc)
{
	if (showing) DrawContent(gc);
	DrawBox(gc);
}
