#include "Object.h"

void Object::DrawBox(wxGraphicsContext* gc)
{
	selectionBox.Draw(gc);
}

void Object::Draw(wxGraphicsContext* gc)
{
	DrawContent(gc);
	DrawBox(gc);
}
