#include "EditorText.h"
#include "DrawingCanvas.h"
#include "ActionNewObject.h"

EditorText::EditorText(DrawingCanvas* parent)
	:Editor(parent)
{
    std::string s = "`1234567890-=[]\\;',./";
    std::string t = "~!@#$%^&*()_+{}|:\"<>?";
    for (int i = 0; i < (int)s.size(); ++i)
        up[s[i]] = t[i];
}

void EditorText::OnMouseDown(wxMouseEvent& event)
{
    Finish();
	text = new Text(event.GetPosition(), parent->GetPenColor(), parent->GetPenSize(), parent->GetTextFont());
}

void EditorText::OnMouseMove(wxMouseEvent& event)
{
}

void EditorText::OnMouseUp(wxMouseEvent& event)
{
}

void EditorText::OnMouseLeave(wxMouseEvent& event)
{
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
            char c = uc;
            if (c >= 'A' && c <= 'Z') {
                if (!(event.ShiftDown() ^ wxGetKeyState(WXK_CAPITAL))) {
                    c = c - 'A' + 'a';
                }
            }
            else {
                if (event.ShiftDown()) c = up[c];
            }
            text->Append(c);
        }
        else
        {
            switch (uc)
            {
            case WXK_BACK:
                text->Pop();
                break;
            case WXK_RETURN:
                text->Append('\n');
                break;
            default:
                Finish();
                break;
            }
            return;
        }
    }
    event.Skip();
}

void EditorText::OnKeyUp(wxKeyEvent& event)
{
}

void EditorText::OnChar(wxKeyEvent& event)
{
}

void EditorText::Finish()
{
    if (!text) return;
    parent->AddPath(text);
    text = nullptr;
}

void EditorText::Draw(wxGraphicsContext* gc)
{
	if (text) {
		text->Draw(gc);
	}
}
