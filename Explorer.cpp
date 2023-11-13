#include "Explorer.h"

Explorer::Explorer(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: wxScrolled<wxPanel>(parent, wxID_ANY)
{
	this->SetScrollRate(0, FromDIP(10));
	mainSizer = new wxBoxSizer(wxVERTICAL);
	
	//mainSizer->Add(new ActionPane(this, new ActionNewObject<int>(nullptr)));

	this->SetSizer(mainSizer);
}

void Explorer::Add(ActionPane* pane)
{
	mainSizer->Add(pane);
	this->FitInside();
}

void Explorer::Remove(int i)
{
	mainSizer->Hide(i);
	mainSizer->Remove(i);
	this->FitInside();
}

void Explorer::SetSelected(int i, bool selected)
{
	((ActionPane*)mainSizer->GetItem(i)->GetWindow())->SetSelected(selected);
}
