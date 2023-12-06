#include "Panel.h"
#include <wx/colordlg.h>

Panel::Panel(wxWindow* parent, DrawingCanvas* _canvas, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: wxScrolled<wxPanel>(parent, wxID_ANY), canvas(_canvas)
{
	this->SetScrollRate(0, FromDIP(10));

	mainSizer = new wxBoxSizer(wxVERTICAL);

    wxInitAllImageHandlers();
    SetupButtons();
    SetupMouseButtons();
    SetupShapePanes();    
    SetupSizePanes();
    SetupColorPanes();
    SetupBrushPanes();

    this->SetSizer(mainSizer);
    
    SelectColorPane(colorPanes[0]);
    SelectSizePane(sizePanes[0]);
    SelectShapePane(shapePanes[0]);
    SelectBrushPane(brushPanes[0]);
    SelectMode(buttonPanes[1]);
    SelectPaint();
}

void Panel::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_TAB) {
        if (!shifting) {
            if (canvas->GetMode() == DrawingCanvas::CURSOR) return;
            shifting = 1;
            lastMode = canvas->GetMode();
            canvas->FinishDrawing();
        
            SelectMode(buttonPanes[0]);
		    SelectMouse();
        }
        else {
            shifting = 0;
            switch (lastMode) {
                case DrawingCanvas::DRAW:
                    SelectMode(buttonPanes[1]);
				    SelectPaint();
				    break;
        	    case DrawingCanvas::SHAPE:
                    SelectMode(buttonPanes[2]);
                    SelectShape();
                    break;
                case DrawingCanvas::TEXT:
                    SelectMode(buttonPanes[3]);
                    SelectText();
				    break;
                case DrawingCanvas::CURSOR:
                    SelectMode(buttonPanes[0]);
					SelectMouse();
					break;
            }
        }
	}
}
void Panel::OnKeyUp(wxKeyEvent& event)
{

}

void Panel::SetupButtons()
{
    buttonSizer = new wxWrapSizer(wxHORIZONTAL);

    auto mouse = new ImagePane(this, "data/mouse.png");
    mouse->Bind(wxEVT_LEFT_DOWN, [this, mouse](wxMouseEvent& event)
        {
            SelectMode(mouse);
            SelectMouse();
        });
    buttonSizer->Add(mouse, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    auto pen = new ImagePane(this, "data/pen.png");
    pen->Bind(wxEVT_LEFT_DOWN, [this, pen](wxMouseEvent& event)
        {
            SelectMode(pen);
            SelectPaint();
        });
    buttonSizer->Add(pen, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    auto shape = new ImagePane(this, "data/shape.png");
    shape->Bind(wxEVT_LEFT_DOWN, [this, shape](wxMouseEvent& event)
    		{
            SelectMode(shape);
            SelectShape();
        });
    buttonSizer->Add(shape, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    auto text = new ImagePane(this, "data/text.png");
    text->Bind(wxEVT_LEFT_DOWN, [this, text](wxMouseEvent& event)
    	{
                SelectMode(text);
            SelectText();
        });
    buttonSizer->Add(text, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    buttonPanes = { mouse, pen, shape, text };
    mainSizer->Add(buttonSizer, 0, wxALL, FromDIP(5));
}

void Panel::SetupMouseButtons()
{
    functionText = new wxStaticText(this, wxID_ANY, "Tools");
    mainSizer->Add(functionText, 0, wxALL, FromDIP(5));
    functionSizer = new wxWrapSizer(wxHORIZONTAL);
    
    ImagePane *rotate = new ImagePane(this, "data/rotate.png");
    rotate->Bind(wxEVT_LEFT_DOWN, [this, rotate](wxMouseEvent& event) {
			canvas->TransformCanvas(0);
            rotate->SetSelected(1);
		});
    functionSizer->Add(rotate, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    ImagePane *hflip = new ImagePane(this, "data/hflip.png");
    hflip->Bind(wxEVT_LEFT_DOWN, [this, hflip](wxMouseEvent& event) {
        canvas->TransformCanvas(1);
        hflip->SetSelected(1);
        });
    functionSizer->Add(hflip, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    ImagePane *vflip = new ImagePane(this, "data/vflip.png");
    vflip->Bind(wxEVT_LEFT_DOWN, [this, vflip](wxMouseEvent& event) {
		canvas->TransformCanvas(2);
		vflip->SetSelected(1);
		});
    functionSizer->Add(vflip, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    for (auto pane : { rotate, hflip, vflip })
        pane->Bind(wxEVT_LEFT_UP, [this, pane](wxMouseEvent& event)
        			{ pane->SetSelected(0); });

    mainSizer->Add(functionSizer, 0, wxALL, FromDIP(5));
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

    wxImage* customColorImage = new wxImage("data/customColorPane.png", wxBITMAP_TYPE_PNG);
    customColorImage->Rescale(colorPanes[0]->GetSize().x, colorPanes[0]->GetSize().y);

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

    for (int i = 1; i <= 10; i++)
    {
		auto sizePane = new SizePane(this, i * 2);
		sizePane->Bind(wxEVT_LEFT_DOWN, [this, sizePane](wxMouseEvent& event)
        			{ SelectSizePane(sizePane); });
		sizePanes.push_back(sizePane);
        sizePaneSizer->Add(sizePane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
	}

    mainSizer->Add(sizePaneSizer, 0, wxALL, FromDIP(5));

    wxSlider* slider = new wxSlider(this, wxID_ANY, 1, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    slider->Bind(wxEVT_SLIDER, [this, slider](wxCommandEvent& event)
        {
            SelectSizePane(slider->GetValue());
        });
    penSlider = slider;
    mainSizer->Add(slider, 0, wxEXPAND | wxALL, FromDIP(5));

}

void Panel::SetupShapePanes()
{
    shapeText = new wxStaticText(this, wxID_ANY, "Shapes");
    mainSizer->Add(shapeText, 0, wxALL, FromDIP(5));

    std::vector<std::vector<wxPoint2DDouble>> shapes = {
        {{0, 0}, {0, 100}, {100, 100}, {100, 0}, {0, 0} },
        {{25, 0}, {50, 50}, {0, 50}, {25, 0}},
        {{50, 0}, {100, 50}, {50, 100}, {0, 50}, {50, 0} }
    };

    //circle
    shapes.push_back(std::vector<wxPoint2DDouble>());
    double pi = acos(-1);
    for (double a = -pi; a <= pi; a += 0.01) {
        shapes.back().push_back({ 50.0 + 50.0 * cos(a), 50.0 + 50.0 * sin(a) });
    }

    //5
    shapes.push_back(std::vector<wxPoint2DDouble>());
    for (double a = -pi / 2; a <= pi * 3 / 2 + 0.000001; a += (pi * 2) / 5) {
        shapes.back().push_back({ 50.0 + 50.0 * cos(a), 50.0 + 50.0 * sin(a) });
    }
    //6
    shapes.push_back(std::vector<wxPoint2DDouble>());
    for (double a = -pi / 2; a <= pi * 3 / 2 + 0.000001; a += (pi * 2) / 6) {
        shapes.back().push_back({ 50.0 + 50.0 * cos(a), 50.0 + 50.0 * sin(a) });
    }

    //star
    shapes.push_back(std::vector<wxPoint2DDouble>());
    double b = pi / 5;
    for (double a = -pi / 2; a <= pi * 3 / 2 + 0.000001; a += (pi * 2) / 5) {
        shapes.back().push_back({ 50.0 + 50.0 * cos(a), 50.0 + 50.0 * sin(a) });
        shapes.back().push_back({ 50.0 + 25.0 * cos(a + b), 50.0 + 25.0 * sin(a + b) });
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

    auto colorPane = new ColorPane(this, wxColour(-1, -1, -1, 0));
    colorPane->Bind(wxEVT_LEFT_DOWN, [this, colorPane](wxMouseEvent& event)
        { SelectBrushPane(colorPane); });
    brushPanes.push_back(colorPane);
    brushPaneSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    wxImage* customColorImage = new wxImage("data/customColorPane.png", wxBITMAP_TYPE_PNG);
    customColorImage->Rescale(brushPanes[0]->GetSize().x, brushPanes[0]->GetSize().x);

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
    SelectSizePane(sizePane->GetWidth());
}

void Panel::SelectSizePane(int size)
{
    for (auto& pane : sizePanes)
    {
		pane->SetSelected(pane->GetWidth() == size);
	}
    penSlider->SetValue(size);
	canvas->SetPenSize(size);
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
        mainSizer->Show(penSlider);
	}
    else {
        mainSizer->Hide(sizeText);
        mainSizer->Hide(sizePaneSizer);
        mainSizer->Hide(penSlider);
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
    if (msk & FUNCTION) {
		mainSizer->Show(functionText);
        mainSizer->Show(functionSizer);
	}
    else {
        mainSizer->Hide(functionText);
		mainSizer->Hide(functionSizer);
	}
    mainSizer->Layout();
}

void Panel::SelectMode(ImagePane* pane)
{
    for (auto& p : buttonPanes)
        p->SetSelected(p == pane);
}

void Panel::SelectMouse()
{
    Layout(FUNCTION);
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