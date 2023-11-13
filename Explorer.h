#pragma once

#ifndef EXPLORER_H
#define EXPLORER_H

#include <wx/wx.h>
#include<wx/splitter.h>
#include "ActionPane.h"

class Explorer : public wxScrolled<wxPanel>
{
public:
	Explorer(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
	void Add(ActionPane* pane);
	void Remove(int i);
	void SetSelected(int i, bool selected);

private:
	wxBoxSizer* mainSizer;
};

#endif // !EXPLORER_H