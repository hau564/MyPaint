#include "Panel.h"
#include <wx/colordlg.h>

Panel::Panel(wxWindow* parent, DrawingCanvas* _canvas, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: wxScrolled<wxPanel>(parent, wxID_ANY), canvas(_canvas)
{
	this->SetScrollRate(0, FromDIP(10));

	mainSizer = new wxBoxSizer(wxVERTICAL);

    SetupButtons();
    SetupShapePanes();    
    SetupSizePanes();
    SetupColorPanes();
    SetupBrushPanes();

    this->SetSizer(mainSizer);
    
    SelectColorPane(colorPanes[0]);
    SelectSizePane(sizePanes[0]);
    SelectShapePane(shapePanes[0]);
    SelectBrushPane(brushPanes[0]);

    SelectPaint();
}

void Panel::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_SHIFT)    {
        if (canvas->GetMode() == DrawingCanvas::CURSOR) return;
        lastMode = canvas->GetMode();
		SelectMouse();
	}
}

void Panel::OnKeyUp(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_SHIFT) {
        switch (lastMode) {
            case DrawingCanvas::DRAW:
				SelectPaint();
				break;
        	case DrawingCanvas::SHAPE:
                SelectShape();
                break;
            case DrawingCanvas::TEXT:
                SelectText();
				break;
        }
    }
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
        SelectShape();
        });

    textButton = new wxButton(this, wxID_ANY, "Text");
    textButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        SelectText();
        });


    buttonSizer = new wxWrapSizer(wxHORIZONTAL);
    buttonSizer->Add(mouseButton, 0, wxALL, FromDIP(5));
    buttonSizer->Add(paintButton, 0, wxALL, FromDIP(5));
    buttonSizer->Add(shapeButton, 0, wxALL, FromDIP(5));
    buttonSizer->Add(textButton, 0, wxALL, FromDIP(5));

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

void Panel::SetupShapePanes()
{
    shapeText = new wxStaticText(this, wxID_ANY, "Shapes");
    mainSizer->Add(shapeText, 0, wxALL, FromDIP(5));

    std::vector<std::vector<wxPoint2DDouble>> shapes = {
        {{0, 0}, {0, 100}, {100, 100}, {100, 0}, {0, 0} },
        {{0, 0}, {0, 50}, {50, 0}, {0, 0}},
        {{50, 0}, {100, 50}, {50, 100}, {0, 50}, {50, 0} }
    };

    //circle
    shapes.push_back(std::vector<wxPoint2DDouble>());
    double pi = acos(-1);
    for (double a = -pi; a <= pi; a += 0.01) {
        shapes.back().push_back({ 50 + 50 * cos(a), 50 + 50 * sin(a) });
    }

    //star
    shapes.push_back(std::vector<wxPoint2DDouble>());
    double b = pi / 10;
    for (double a = -pi * 3 / 2; a <= pi / 2 + 0.000001; a += (pi * 2) / 5) {
		shapes.back().push_back({ 50 + 50 * cos(a + pi), 50 + 50 * sin(a + pi) });
		//shapes.back().push_back({ 50 + 25 * cos(a + pi + b), 50 + 25 * sin(a + pi + b) });
	}

    shapePaneSizer = new wxWrapSizer(wxHORIZONTAL);
    
    for (auto points : shapes) {
        ShapePane *pane = new ShapePane(this, points);
        pane->Bind(wxEVT_LEFT_DOWN, [this, pane](wxMouseEvent& event)
        			{ SelectShapePane(pane); });
        shapePaneSizer->Add(pane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
        shapePanes.push_back(pane);
    }

    mainSizer->Add(shapePaneSizer, 0, wxALL, FromDIP(5));
}

void Panel::SetupBrushPanes()
{
    brushText = new wxStaticText(this, wxID_ANY, "Fill Colors");
    mainSizer->Add(brushText, 0, wxALL, FromDIP(5));
    brushPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    for (const auto& color : niceColors)
    {
        auto brushPane = new ColorPane(this, wxColour(color));

        brushPane->Bind(wxEVT_LEFT_DOWN, [this, brushPane](wxMouseEvent& event)
            { SelectBrushPane(brushPane); });

        brushPanes.push_back(brushPane);
        brushPaneSizer->Add(brushPane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    }

    wxImage* customColorImage = new wxImage("data/customColorPane.png", wxBITMAP_TYPE_PNG);
    customColorImage->Rescale(FromDIP(37), FromDIP(37));

    brushPicker = new wxBitmapButton((wxWindow*)this, wxID_ANY, wxBitmap(*customColorImage));
    brushPicker->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event)
        {
            wxColourDialog dialog(this);
            if (dialog.ShowModal() == wxID_OK)
            {
                wxColor color = dialog.GetColourData().GetColour();
                //AddColor(new ColorPane(this, color));
                SelectBrushPane(new ColorPane(nullptr, color));
            }
        });

    brushPaneSizer->Add(brushPicker, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    mainSizer->Add(brushPaneSizer, 0, wxALL, FromDIP(5));
}



void Panel::SelectColorPane(ColorPane* colorPane)
{
    for (auto& pane : colorPanes)
    {
		pane->SetSelected(pane->GetColor() == colorPane->GetColor());
	}
    canvas->SetPenColor(colorPane->GetColor());
}

void Panel::SelectSizePane(SizePane* sizePane)
{
    for (auto& pane : sizePanes)
    {
        pane->SetSelected(pane == sizePane);
    }
    canvas->SetPenSize(sizePane->GetWidth());
}

void Panel::SelectShapePane(ShapePane* shapePane)
{
    for (auto& pane : shapePanes)
    {
		pane->SetSelected(pane == shapePane);
	}
    canvas->SetShape(shapePane->GetShape());
}

void Panel::SelectBrushPane(ColorPane* brushPane)
{
    for (auto& pane : brushPanes)
    {
		pane->SetSelected(pane->GetColor() == brushPane->GetColor());
	}
	canvas->SetBrushColor(brushPane->GetColor());
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
    if (msk & SHAPE) {
        mainSizer->Show(shapeText);
        mainSizer->Show(shapePaneSizer);
    }
    else {
        mainSizer->Hide(shapeText);
        mainSizer->Hide(shapePaneSizer);
    }
    if (msk & BRUSH) {
		mainSizer->Show(brushText);
		mainSizer->Show(brushPaneSizer);
	}
    else {
		mainSizer->Hide(brushText);
		mainSizer->Hide(brushPaneSizer);
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
    Layout(COLOR | SIZE | SHAPE | BRUSH);
	canvas->SetMode(DrawingCanvas::SHAPE);
}

void Panel::SelectText()
{
    Layout(SIZE | COLOR);
	canvas->SetMode(DrawingCanvas::TEXT);
}