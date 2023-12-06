#include "SelectablePane.h"

SelectablePane::SelectablePane(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SelectablePane::OnPaint, this);
    Bind(wxEVT_MOTION, &SelectablePane::OnMouseMove, this);
    Bind(wxEVT_LEAVE_WINDOW, &SelectablePane::OnMouseLeave, this);
}

void SelectablePane::SetSelected(bool selected)
{
    this->selected = selected;
    Refresh();
}

bool SelectablePane::IsSelected()
{
    return selected;
}

void SelectablePane::DrawSelected(wxGraphicsContext* gc, const wxRect& selectionRect, int roundness) 
{
    gc->SetPen(wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE_PEN : *wxBLACK_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);
}

void SelectablePane::DrawFocus(wxGraphicsContext* gc, const wxRect& selectionRect, int roundness)
{
    gc->SetPen(*wxLIGHT_GREY_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);
}

void SelectablePane::OnMouseMove(wxMouseEvent& event)
{
    focus = 1;
    Refresh();
}

void SelectablePane::OnMouseLeave(wxMouseEvent& event)
{
    focus = 0;
    Refresh();
}

void SelectablePane::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect selectionRect{ 0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight() };
        selectionRect.Deflate(FromDIP(1));

        wxRect contentRect = selectionRect;
        contentRect.Deflate(FromDIP(2));

        const auto roundness = FromDIP(4);

        DrawContent(gc, contentRect, roundness);

        if (selected)
        {
            DrawSelected(gc, selectionRect, roundness);
        }
        else if (focus)
        {
			DrawFocus(gc, selectionRect, roundness);
		}

        delete gc;
    }
}
