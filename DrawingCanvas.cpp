#include "DrawingCanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
	:wxWindow(parent, id, pos, size)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::onMouseDown, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::onMouseUp, this);
	this->Bind(wxEVT_MOTION, &DrawingCanvas::onMouseMove, this);
	this->Bind(wxEVT_PAINT, &DrawingCanvas::onPaint, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::onMouseUp, this);
	
	layers.push_back(new Layer());
	activeLayer = layers[0];
	activePath = nullptr;
}

void DrawingCanvas::SetExplorer(Explorer* explorer)
{
	history = new History(this, explorer);
}

DrawingCanvas::~DrawingCanvas()
{
	while (!layers.empty()) {
		delete layers.back();
		layers.pop_back();
	}
}



void DrawingCanvas::SetColor(wxColor color)
{
	penColor = color;
}

void DrawingCanvas::SetSize(int size)
{
	penSize = size;
}

void DrawingCanvas::SetMode(int mode)
{
	editMode = mode;
	if (editor) delete editor;

	switch (editMode) {
	case CURSOR:
		BuildPathList();
		break;
	case DRAW:
		editor = new EditorDraw(this);
	}
}





void DrawingCanvas::OnExport(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save drawing"), "", "",
		"PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxBitmap bitmap(this->GetSize() * this->GetContentScaleFactor());

	wxMemoryDC memDC;

	memDC.SetUserScale(this->GetContentScaleFactor(), this->GetContentScaleFactor());

	memDC.SelectObject(bitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);

	if (gc)
	{
		draw(gc);
		delete gc;
	}

	bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
}

void DrawingCanvas::OnUndo(wxCommandEvent& event)
{
	history->Undo();
	Refresh();
}

void DrawingCanvas::OnRedo(wxCommandEvent& event)
{
	history->Redo();
	Refresh();
}







void DrawingCanvas::draw(wxGraphicsContext* gc)
{
	for (Layer* layer : layers) {
		layer->Draw(gc);
	}
	if (activePath) activePath->Draw(gc);
}

void DrawingCanvas::onMouseDown(wxMouseEvent& event)
{
	switch (editMode) {
	case DRAW:
		activePath = new Path(penColor, penSize);
		activePath->OnPenDown(event.GetPosition());
		break;

	case CURSOR:
		activePath = nullptr;
		for (auto path : paths) {
			activePath = path->OnMouseDown(event.GetPosition());
			if (activePath) break;
		}
		for (auto path : paths) if (path != activePath) path->SetSelected(false);
		Refresh();
		break;
	}
	if (editor) editor->OnMouseDown(event);
}

void DrawingCanvas::onMouseUp(wxMouseEvent& event)
{
	switch (editMode) {
	case DRAW :
		if (!activePath) return;
		if (!activeLayer) return;
		
		activePath->OnPenUp();
		activeLayer->Last()->InsertNext(activePath);

		history->AddDoneAction(new ActionNewObject<Path*>(activeLayer->Last()));

		activePath = nullptr;
		Refresh();
		break;
	}
	if (editor) {
		editor->OnMouseUp(event);
	}
}

void DrawingCanvas::onMouseMove(wxMouseEvent& event)
{
	switch (editMode) {
	case DRAW:
		if (!activePath) return;
		activePath->OnPenMove(event.GetPosition());
		Refresh();
		break;
	}
	if (editor) {
		editor->OnMouseUp(event);
	}
}

void DrawingCanvas::onMouseLeave(wxMouseEvent& event)
{
	if (editor) {
		editor->OnMouseLeave(event);
	}
}

void DrawingCanvas::onPaint(wxPaintEvent&)
{
	wxAutoBufferedPaintDC dc(this);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		draw(gc);
		delete gc;
	}
}

void DrawingCanvas::BuildPathList()
{
	paths.clear();
	for (Layer* layer : layers) {
		auto layerPaths = layer->GetVectorData();
		paths.insert(paths.end(), layerPaths.begin(), layerPaths.end());
	}
	
	sort(paths.begin(), paths.end(),
		[&](const Path* a, const Path* b) {
			return a->GetBoundArea() < b->GetBoundArea();
		});
}
