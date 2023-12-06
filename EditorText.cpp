#include "EditorText.h"
#include "DrawingCanvas.h"
#include "ActionNewObject.h"

EditorText::EditorText(DrawingCanvas* parent)
	:Editor(parent)
{
}

void EditorText::OnMouseDown(wxMouseEvent& event)
{
    if (text) {
        parent->AddPath(text);
        text = nullptr;
    }
	text = new Text(event.GetPosition(), parent->GetPenColor(), parent->GetPenSize());
}

void EditorText::OnMouseMove(wxMouseEvent& event)
{
}

void EditorText::OnMouseUp(wxMouseEvent& event)
{
}

void EditorText::OnMouseLeave(wxMouseEvent& event)
{
    if (!text) return;
    parent->AddPath(text);
    text = nullptr;
}

void EditorText::OnKeyDown(wxKeyEvent& event)
{
    if (!text) return;
    wxChar uc = event.GetUnicodeKey();
    if (uc != WXK_NONE)
    {
        // It's a "normal" character. Notice that this includes
        // control characters in 1..31 range, e.g. WXK_RETURN or
        // WXK_BACK, so check for them explicitly.
        if (uc >= 32)
        {
            //wxLogMessage("You pressed '%c'", uc);
			text->Append(uc);
        }
        else
        {
            if (event.GetKeyCode() == WXK_BACK) {
                text->Pop();
            }
            return;
        }
    }

    if (event.GetKeyCode() == WXK_BACK) {
		text->Pop();
	}
    event.Skip();
}

void EditorText::OnChar(wxKeyEvent& event)
{
}

void EditorText::Draw(wxGraphicsContext* gc)
{
	if (text) {
		text->Draw(gc);
	}
}
