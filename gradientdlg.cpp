#include "gradientdlg.h"
#include <iostream>

IMPLEMENT_DYNAMIC_CLASS(wxGradientDialog, wxDialog)

BEGIN_EVENT_TABLE(wxGradientDialog, wxDialog)
EVT_CLOSE(wxGradientDialog::OnCloseWindow)
EVT_BUTTON(wxID_EDIT, wxGradientDialog::OnEditColor)
EVT_BUTTON(wxID_DELETE, wxGradientDialog::OnDeleteColor)
END_EVENT_TABLE()

wxGradientDialog::wxGradientDialog()
{
}
wxGradientDialog::wxGradientDialog(wxWindow* parent, wxGradient grad)
{
	Create(parent, grad);
}
wxGradientDialog::~wxGradientDialog()
{
	delete m_gradient;
}
bool wxGradientDialog::Create(wxWindow* parent, wxGradient grad)
{
	if (!wxDialog::Create(GetParentForModalDialog(parent, wxBG_STYLE_COLOUR), wxID_ANY, wxT("Gradient Editor")))
		return false;
	CreateWidgets();
	stopsStatBmp->Connect(ID_STOPSAREA, wxEVT_LEFT_DOWN, wxMouseEventHandler(wxGradientDialog::OnStopsAreaClick), NULL, this);
	selectedColorStop = -1;
	m_gradient = new wxGradient(grad);
	m_gradient->setMin(0);
	m_gradient->setMax(gradientStatBmp->GetSize().GetWidth());
	paintGradient();
	paintStops();
	return true;
}
wxGradient wxGradientDialog::GetGradient()
{
	return *m_gradient;
}
int wxGradientDialog::ShowModal()
{
	return wxDialog::ShowModal();
}
void wxGradientDialog::CreateWidgets()
{
	topSizer = new wxBoxSizer(wxVERTICAL);

	gradientSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Gradient");
	topSizer->Add(gradientSizer, 1, wxEXPAND | wxALL, FromDIP(12));

	gradientStatBmp = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(FromDIP(300), FromDIP(50)), wxBORDER_SIMPLE);
	gradientSizer->Add(gradientStatBmp, 1, wxALL | wxALIGN_CENTER_HORIZONTAL);

	stopAreaSizer = new wxBoxSizer(wxHORIZONTAL);
	gradientSizer->Add(stopAreaSizer, 1, wxEXPAND | wxTOP | wxBOTTOM, FromDIP(6));

	stopsStatBmp = new wxStaticBitmap(this, ID_STOPSAREA, wxNullBitmap, wxDefaultPosition, wxSize(FromDIP(350), FromDIP(16)));
	stopAreaSizer->Add(stopsStatBmp);

	stopEditSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Stops");
	gradientSizer->Add(stopEditSizer, 1, wxEXPAND | wxALL, FromDIP(2));

	colorSizer = new wxBoxSizer(wxHORIZONTAL);
	stopEditSizer->Add(colorSizer, 1, wxEXPAND | wxALL, FromDIP(6));

	colorTxt = new wxStaticText(this, wxID_ANY, "Color: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	colorSizer->Add(colorTxt, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, FromDIP(12));

	colorStatBmp = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(FromDIP(30), FromDIP(20)), wxBORDER_DOUBLE);
	colorSizer->Add(colorStatBmp, 0, wxALIGN_CENTER_VERTICAL);

	colorEditBtn = new wxButton(this, wxID_EDIT, "...", wxDefaultPosition, wxSize(FromDIP(30), FromDIP(22)));
	colorSizer->Add(colorEditBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(6));
	colorEditBtn->Enable(false);

	colorDeleteBtn = new wxButton(this, wxID_DELETE, "Delete", wxDefaultPosition, wxSize(FromDIP(80), FromDIP(30)));
	colorSizer->Add(colorDeleteBtn, 0, wxLEFT, FromDIP(100));
	colorDeleteBtn->Enable(false);

	buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	if (buttonSizer)
	{
		topSizer->Add(buttonSizer, wxSizerFlags().Expand().DoubleBorder());
	}

	this->SetSizer(topSizer);
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
}
void wxGradientDialog::paintGradient()
{
	wxBufferedDC* dc = new wxBufferedDC();
	wxBitmap* gradientBmpTemp = new wxBitmap(gradientStatBmp->GetSize().GetWidth(), gradientStatBmp->GetSize().GetHeight());

	dc->SelectObject(*gradientBmpTemp);
	for (int i = m_gradient->getMin(); i < m_gradient->getMax(); i++)
	{
		dc->SetPen(wxPen(m_gradient->getColorAt(i), 1));
		dc->DrawLine(i, 0, i, gradientStatBmp->GetSize().GetHeight());
	}
	dc->SelectObject(wxNullBitmap);
	gradientStatBmp->SetBitmap(*gradientBmpTemp);
	delete gradientBmpTemp;
	delete dc;
}
void wxGradientDialog::paintStops()
{
	m_displayedStops = m_gradient->getStops();
	wxVector<wxColor>::iterator itr;
	int ctr = gradientStatBmp->GetPosition().x / 2;
	int dist = (gradientStatBmp->GetClientSize().GetWidth() / (m_displayedStops.size() - 1));
	wxBufferedDC* dc = new wxBufferedDC();
	wxBitmap* stopsBmpTmp = new wxBitmap(stopsStatBmp->GetSize().GetWidth(), stopsStatBmp->GetSize().GetHeight());
	dc->SelectObject(*stopsBmpTmp);
	dc->SetBackground(wxBrush(GetBackgroundColour()));
	dc->Clear();
	for (itr = m_displayedStops.begin(); itr != m_displayedStops.end(); ++itr)
	{
		// draw triangle
		dc->SetPen(wxPen(*wxBLACK));
		dc->SetBrush(wxBrush(wxTRANSPARENT));
		//dc->SetBrush(wxBrush(wxNullColour, wxTRANSPARENT));
		wxPoint triangle[] = { wxPoint(ctr, FromDIP(5)), wxPoint(ctr + FromDIP(5), 0), wxPoint(ctr + FromDIP(10), FromDIP(5)) };
		dc->DrawPolygon(3, triangle);

		// draw color
		dc->SetBrush(wxBrush(*itr));
		dc->DrawRectangle(ctr, FromDIP(5), FromDIP(11), FromDIP(11));

		// draw accents
		dc->SetPen(wxPen(*wxWHITE));
		dc->DrawLine(ctr + FromDIP(1), FromDIP(6), ctr + FromDIP(10), FromDIP(6));
		dc->DrawLine(ctr + FromDIP(1), FromDIP(7), ctr + FromDIP(1), FromDIP(15));
		dc->SetPen(wxPen(wxColor(156, 155, 159)));
		dc->DrawLine(ctr + FromDIP(2), FromDIP(14), ctr + FromDIP(10), FromDIP(14));
		dc->DrawLine(ctr + FromDIP(9), FromDIP(7), ctr + FromDIP(9), FromDIP(14));
		dc->DrawLine(ctr + FromDIP(5), FromDIP(1), ctr + FromDIP(9), FromDIP(5));

		ctr += (dist);
	}
	dc->SelectObject(wxNullBitmap);
	stopsStatBmp->SetBitmap(*stopsBmpTmp);

	delete stopsBmpTmp;
	delete dc;
}
void wxGradientDialog::OnStopsAreaClick(wxMouseEvent& event)
{
	selectedColorStop = -1;
	int ctr = gradientStatBmp->GetPosition().x / 2;
	int i = 0; // index of color stop
	int dist = (gradientStatBmp->GetClientSize().GetWidth() / (m_displayedStops.size() - 1));
	wxVector<wxColor>::iterator itr;
	for (itr = m_displayedStops.begin(); itr != m_displayedStops.end(); ++itr)
	{
		if (event.GetX() >= ctr + i * dist && event.GetX() <= ctr + i * dist + FromDIP(11))
		{
			selectedColorStop = i;
			break;
		}
		i++;
	}
	m_displayedStops = m_gradient->getStops();
	if (selectedColorStop != -1)
	{
		colorStatBmp->SetBackgroundColour(m_displayedStops[selectedColorStop]);
		colorStatBmp->ClearBackground();
		paintStops();
	}
	else
	{
		int insertAt = m_displayedStops.size() - (gradientStatBmp->GetSize().GetWidth() - event.GetX()) / dist - 1;
		m_gradient->insertColorStop(insertAt, *wxBLACK);
		selectedColorStop = insertAt;
		m_displayedStops = m_gradient->getStops();
		dist = (gradientStatBmp->GetSize().GetWidth() / (m_displayedStops.size() - 1));
		colorStatBmp->SetBackgroundColour(m_displayedStops[selectedColorStop]);
		colorStatBmp->ClearBackground();
		paintGradient();
		paintStops();
	}

	colorEditBtn->Enable(true);
	if (m_displayedStops.size() > 2)
		colorDeleteBtn->Enable(true);
	event.Skip();
}
void wxGradientDialog::OnEditColor(wxCommandEvent& WXUNUSED(event))
{
	wxColourData data;
	data.SetCustomColour(0, colorStatBmp->GetBackgroundColour());
	data.SetColour(colorStatBmp->GetBackgroundColour());
	wxColourDialog dialog(this, &data);
	if (dialog.ShowModal() == wxID_OK)
	{
		colorStatBmp->SetBackgroundColour(dialog.GetColourData().GetColour());
		colorStatBmp->ClearBackground();
		m_gradient->editColorStop(selectedColorStop, dialog.GetColourData().GetColour());
		paintGradient();
		paintStops();
	}
}
void wxGradientDialog::OnDeleteColor(wxCommandEvent& WXUNUSED(event))
{
	if (selectedColorStop != -1 && m_displayedStops.size() > 2)
	{
		m_gradient->removeColorStop(selectedColorStop);
		paintGradient();
		paintStops();
		selectedColorStop = -1;
		colorStatBmp->SetBackgroundColour(wxNullColour);
		colorStatBmp->ClearBackground();
		colorEditBtn->Enable(false);
		colorDeleteBtn->Enable(false);
	}
}
void wxGradientDialog::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
	EndModal(wxID_CANCEL);
}
