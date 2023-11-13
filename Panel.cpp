#include "Panel.h"
#include <wx/colordlg.h>

Panel::Panel(wxWindow* parent, DrawingCanvas* _canvas, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: wxScrolled<wxPanel>(parent, wxID_ANY), canvas(_canvas)
{
	this->SetScrollRate(0, FromDIP(10));

	mainSizer = new wxBoxSizer(wxVERTICAL);

    SetupButtons();
    SetupColorPanes();
    SetupSizePanes();
        

    this->SetSizer(mainSizer);
    
    SelectColorPane(colorPanes[0]);
    SelectSizePane(sizePanes[0]);
}

void Panel::SetupButtons()
{
    mouseButton = new wxButton(this, wxID_ANY, "Mouse");
    mouseButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        SelectMouse();
        });
    paintButton = new wxButton(this, wxID_ANY, "Pen");
    paintButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        SelectPaint();
        });
    shapeButton = new wxButton(this, wxID_ANY, "Shape");
    shapeButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        SelectPaint();
        });

    buttonSizer = new wxWrapSizer(wxHORIZONTAL);
    buttonSizer->Add(mouseButton, 0, wxALL, FromDIP(5));
    buttonSizer->Add(paintButton, 0, wxALL, FromDIP(5));
    buttonSizer->Add(shapeButton, 0, wxALL, FromDIP(5));

    mainSizer->Add(buttonSizer, 0, wxALL, FromDIP(5));
}

void Panel::SetupColorPanes()
{
    colorText = new wxStaticText(this, wxID_ANY, "Colors");
    mainSizer->Add(colorText, 0, wxALL, FromDIP(5));
    colorPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    for (const auto& color : niceColors)
    {
        auto colorPane = new ColorPane(this, wxColour(color));

        colorPane->Bind(wxEVT_LEFT_DOWN, [this, colorPane](wxMouseEvent& event)
            { SelectColorPane(colorPane); });

        colorPanes.push_back(colorPane);
        colorPaneSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    }

    wxInitAllImageHandlers();
    wxImage* customColorImage = new wxImage("data/customColorPane.png", wxBITMAP_TYPE_PNG);
    customColorImage->Rescale(FromDIP(37), FromDIP(37));

    colorPicker = new wxBitmapButton((wxWindow*)this, wxID_ANY, wxBitmap(*customColorImage));
    colorPicker->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event)
        {
            wxColourDialog dialog(this);
            if (dialog.ShowModal() == wxID_OK)
            {
                wxColor color = dialog.GetColourData().GetColour();
                //AddColor(new ColorPane(this, color));
                SelectColorPane(new ColorPane(nullptr, color));
            }
        });

    colorPaneSizer->Add(colorPicker, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    mainSizer->Add(colorPaneSizer, 0, wxALL, FromDIP(5));
}

void Panel::SetupSizePanes()
{
    sizeText = new wxStaticText(this, wxID_ANY, "Sizes");
    mainSizer->Add(sizeText, 0, wxALL, FromDIP(5));

    sizePaneSizer = new wxWrapSizer(wxHORIZONTAL);

    for (int i = 1; i <= 9; i++)
    {
		auto sizePane = new SizePane(this, i * 2);
		sizePane->Bind(wxEVT_LEFT_DOWN, [this, sizePane](wxMouseEvent& event)
        			{ SelectSizePane(sizePane); });
		sizePanes.push_back(sizePane);
        sizePaneSizer->Add(sizePane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
	}
    mainSizer->Add(sizePaneSizer, 0, wxALL, FromDIP(5));
}



void Panel::SelectColorPane(ColorPane* colorPane)
{
    for (auto& pane : colorPanes)
    {
		pane->SetSelected(pane->GetColor() == colorPane->GetColor());
	}
    canvas->SetColor(colorPane->GetColor());
}

void Panel::SelectSizePane(SizePane* sizePane)
{
    for (auto& pane : sizePanes)
    {
        pane->SetSelected(pane == sizePane);
    }
    canvas->SetMode(DrawingCanvas::DRAW);
    canvas->SetSize(sizePane->GetWidth());
}

void Panel::Layout(int msk)
{
    if (msk & COLOR) {
        mainSizer->Show(colorText);
        mainSizer->Show(colorPaneSizer);
    }
    else {
        mainSizer->Hide(colorText);
        mainSizer->Hide(colorPaneSizer);
    }
    if (msk & SIZE) {
		mainSizer->Show(sizeText);
		mainSizer->Show(sizePaneSizer);
	}
    else {
        mainSizer->Hide(sizeText);
        mainSizer->Hide(sizePaneSizer);
    }
    mainSizer->Layout();
}

void Panel::SelectMouse()
{
    Layout(0);
	canvas->SetMode(DrawingCanvas::CURSOR);
}

void Panel::SelectPaint()
{
    Layout(COLOR | SIZE);
	canvas->SetMode(DrawingCanvas::DRAW);
}

void Panel::SelectShape()
{
    Layout(COLOR | SIZE);
	canvas->SetMode(DrawingCanvas::SHAPE);
}
