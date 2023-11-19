#include "ActionPane.h"

ActionPane::ActionPane(wxWindow* parent, const Action* action, const int actionId, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, {2000, 30}), action(action), 
	  id(actionId) {
	SetSelected(true);
}

void ActionPane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	if (!selected) {
		gc->SetPen(wxPen(wxColor(200, 200, 200), 0.5));
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
		gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), 5);
	}

	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	gc->SetFont(font, *wxBLACK);
	wxDouble width, height;
	gc->GetTextExtent(action->GetName(), &width, &height);
	gc->DrawText(action->GetName(), rect.GetX() + 5, rect.GetY() + (rect.GetHeight() - height) / 2);
}


