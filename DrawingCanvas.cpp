#include "DrawingCanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int width, int height)
	:wxWindow(parent, id, pos, size), width(width), height(height)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::onMouseDown, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::onMouseUp, this);
	this->Bind(wxEVT_MOTION, &DrawingCanvas::onMouseMove, this);
	this->Bind(wxEVT_PAINT, &DrawingCanvas::onPaint, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::onMouseLeave, this);
	this->Bind(wxEVT_MOUSEWHEEL, &DrawingCanvas::onMouseWheel, this);
	
	paperPos = wxPoint2DDouble(150, 100);
	Reset();
	//zoom
	wxArrayString zoomList;
	for (int i = 25; i <= 200; i += 25) {
		zoomList.Add(wxString::Format("%d%%", i));
	}
	zoomList.Add("400%");
	zoomComboBox = new wxComboBox(this, wxID_ANY, "100%", wxDefaultPosition, wxDefaultSize, zoomList, wxCB_READONLY);
	zoomComboBox->SetSelection(3);
	zoomComboBox->Bind(wxEVT_COMBOBOX, &DrawingCanvas::onZoom, this);

	layers.push_back(new Layer());
	activeLayer = layers[0];
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


void DrawingCanvas::SetPenColor(wxColor color)
{
	penColor = color;
}

void DrawingCanvas::SetBrushColor(wxColor color)
{
	brushColor = color;
}

void DrawingCanvas::SetPenSize(int size)
{
	penSize = size;
}

void DrawingCanvas::SetShape(Shape shape)
{
	this->shape = shape;
}

void DrawingCanvas::SetMode(int mode)
{
	this->mode = mode;
	if (editor) delete editor;
	editor = nullptr;

	std::vector<Object*> paths;
	switch (mode) {
	case DRAW:
		editor = new EditorDraw(this);
		break;

	case CURSOR:
		for (auto layer : layers) {
			auto pathOfLayer = layer->GetVectorData();
			for (auto path : pathOfLayer) {
				paths.push_back(path);
			}
		}
		editor = new EditorMouse(this, paths);
		break;

	case SHAPE:
		editor = new EditorShape(this);
		break;

	case TEXT:
		editor = new EditorText(this);
		break;
	}
	Refresh();
}

int DrawingCanvas::GetMode()
{
	return mode;
}

void DrawingCanvas::TransformCanvas(int id)
{
	wxAffineMatrix2D matrix;
	wxPoint2DDouble center = scaleMatrix.TransformPoint(wxPoint2DDouble(GetSize().x / 2, GetSize().y / 2));
	matrix.Translate(center.m_x, center.m_y);
	switch (id) {
	case 0:
		matrix.Rotate(acos(-1) / 2);
		break;
	case 1:
		matrix.Scale(-1, 1);
		break;
	case 2:
		matrix.Scale(1, -1);
		break;
	}
	matrix.Translate(-center.m_x, -center.m_y);
	matrix.Concat(scaleMatrix);
	imatrix = scaleMatrix = matrix;
	imatrix.Invert();
	Refresh();
}





void DrawingCanvas::OnExport(wxCommandEvent& event)
{
	scaleMatrix = imatrix = wxAffineMatrix2D();
	Refresh();

	wxFileDialog saveFileDialog(this, _("Save drawing"), "", "",
		"PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		Reset();
		return;
	}

	wxBitmap bitmap(width, height);

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

	Reset();
}

void DrawingCanvas::OnUndo(wxCommandEvent& event)
{
	if (editor) {
		wxMouseEvent e;
		editor->OnMouseUp(e);
	}
	history->Undo();
	Refresh();
}

void DrawingCanvas::OnRedo(wxCommandEvent& event)
{
	if (editor) {
		wxMouseEvent e;
		editor->OnMouseUp(e);
	}
	history->Redo();
	Refresh();
}

void DrawingCanvas::OnReset(wxCommandEvent& event)
{
	Reset();
}

void DrawingCanvas::Reset()
{
	scaleMatrix = imatrix = wxAffineMatrix2D();
	scaleMatrix.Translate(paperPos.m_x, paperPos.m_y);
	imatrix.Translate(-paperPos.m_x, -paperPos.m_y);
	Refresh();
}






void DrawingCanvas::AddPath(Object* path)
{
	if (!activeLayer) return;

	activeLayer->Last()->InsertNext(path);
	history->AddDoneAction(new ActionNewObject<Object*>(activeLayer->Last()));
	Refresh();
}

void DrawingCanvas::AddUndoneAction(Action* action)
{
	history->AddUndoneAction(action);
	Refresh();
}

void DrawingCanvas::FinishDrawing()
{
	onMouseUp(lastEvent);
}

void DrawingCanvas::TransformEvent(wxMouseEvent& event) {
	lastEvent = event;
	wxPoint2DDouble mousePos = imatrix.TransformPoint(event.GetPosition());
	event.SetPosition({ (int)mousePos.m_x, (int)mousePos.m_y });
}

void DrawingCanvas::onMouseDown(wxMouseEvent& event)
{
	TransformEvent(event);
	if (editor) {
		editor->OnMouseDown(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseUp(wxMouseEvent& event)
{
	TransformEvent(event);
	if (editor) {
		editor->OnMouseUp(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseMove(wxMouseEvent& event)
{
	TransformEvent(event);
	if (editor) {
		editor->OnMouseMove(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseLeave(wxMouseEvent& event)
{
	TransformEvent(event);
	if (editor) {
		editor->OnMouseLeave(event);
		Refresh();
	}
}

void DrawingCanvas::onZoom(wxCommandEvent& event)
{
	std::string str = zoomComboBox->GetValue().ToStdString();
	int zoom = std::stoi(str);
	scaleMatrix = imatrix = wxAffineMatrix2D();
	Scale(wxPoint2DDouble(GetSize().x / 2, GetSize().y / 2), 1.0 * zoom / 100.0);
}

void DrawingCanvas::onKeyDown(wxKeyEvent& event)
{
	if (editor) editor->OnKeyDown(event);
	if (event.GetKeyCode() == WXK_CONTROL) {
		ctrlHolding = true;
	}
	if (event.GetKeyCode() == WXK_ALT) {
		altHolding = true;
	}
	Refresh();
}

void DrawingCanvas::onKeyUp(wxKeyEvent& event)
{
	if (editor) editor->OnKeyUp(event);
	if (event.GetKeyCode() == WXK_CONTROL) {
		ctrlHolding = false;
	}
	if (event.GetKeyCode() == WXK_ALT) {
		altHolding = false;
	}
	Refresh();
}

void DrawingCanvas::onChar(wxKeyEvent& event)
{
	if (editor) editor->OnChar(event);
	Refresh();
}

void DrawingCanvas::Scale(wxPoint2DDouble pos, double scale)
{
	if (scale < 0) return;
	wxAffineMatrix2D matrix;

	matrix.Translate(pos.m_x, pos.m_y);
	matrix.Scale(scale, scale);
	matrix.Translate(-pos.m_x, -pos.m_y);
	matrix.Concat(scaleMatrix);
	scaleMatrix = matrix;
	imatrix = scaleMatrix;
	imatrix.Invert();
}

void DrawingCanvas::Move(wxPoint2DDouble move)
{
	wxAffineMatrix2D matrix;
	matrix.Translate(move.m_x, move.m_y);
	matrix.Concat(scaleMatrix);
	scaleMatrix = matrix;
	imatrix = scaleMatrix;
	imatrix.Invert();
}

void DrawingCanvas::onMouseWheel(wxMouseEvent& event)
{
	double x1 = 0, y1 = 0, x2 = GetSize().x, y2 = GetSize().y;
	double width = x2, height = y2;
	scaleMatrix.TransformPoint(&x1, &y1);
	scaleMatrix.TransformPoint(&x2, &y2);


	if (ctrlHolding) {
		wxPoint2DDouble scalePoint = event.GetPosition();
		double newScale = -1;
		if (event.GetWheelRotation() > 0) {
			double maxScale = 30;
			if (x2 - x1 <= width * 30) {
				newScale = std::min(1.1, width * 30 / (x2 - x1));
			}
		}
		else {
			if (x2 - x1 > width / 2) {
				newScale = std::max(1.0 / 1.1, width / 2 / (x2 - x1));
			}
		}
		Scale(scalePoint, newScale);
		return;
	}
	wxPoint2DDouble move(0, 0);
	int d = 20;
	if (altHolding) {
		if (event.GetWheelRotation() > 0) {
			move.m_x = d;
		}
		else {
			move.m_x = -d;
		}
	}
	else {
		if (event.GetWheelRotation() > 0) {
			move.m_y = d;
		}
		else {
			move.m_y = -d;
		}
	}
	Move(move);
	Refresh();
}



void DrawingCanvas::draw(wxGraphicsContext* gc)
{
	zoomComboBox->SetPosition(wxPoint(GetSize().x - zoomComboBox->GetSize().x, 0));
	gc->PushState();
	gc->SetTransform(gc->CreateMatrix(scaleMatrix));

	gc->SetPen(wxPen(*wxWHITE, 0));
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(0, 0, width, height);
	//gc->Clip(0, 0, GetSize().x, GetSize().y);

	for (Layer* layer : layers) {
		layer->Draw(gc);
	}
	if (editor) editor->Draw(gc);
	gc->PopState();

}

void DrawingCanvas::onPaint(wxPaintEvent&)
{
	wxAutoBufferedPaintDC dc(this);
	dc.SetBackground(wxBrush(wxColor(200, 200, 200)));
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::CreateFromUnknownDC(dc);
	if (gc)
	{
		draw(gc);
		delete gc;
	}
}

