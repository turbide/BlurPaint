#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QGLWidget>
#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QTimer>

#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW  0xFFFF00

class PaintWindow;
struct PixelInfo;

class PaintWidget : public QGLWidget{
	Q_OBJECT

	public:	
		PaintWidget( QWidget* parent = 0 );
		~PaintWidget();
		int selectedTool() const;
		int nSides() const;
		void putPixel( int x, int y, const QColor& c );
		void putSquare( int x, int y, const QColor& c );
		void drawLine( int x1, int y1, int x2, int y2 );
		void drawCircle( int xC, int yC, int r );
		void drawEllipse( int xC, int yC, int rX, int rY );
		void drawSpline( QPoint* points );
		void sprayPixels( int x, int y );
		void drawPolygon( int xC, int yC, int r, float curAngle, int sides );
		void fillArea( int x, int y, PixelInfo bgcolor, PixelInfo fillcolor );
		
	public slots:
		void setSelectedTool( int t );
		void setNSides( int n );
		void setColor( int c );

	protected:
		void initializeGL();
		void resizeGL( int w, int h );
		void paintGL();
		void mousePressEvent( QMouseEvent* event );
		void mouseReleaseEvent( QMouseEvent* event );
		void mouseMoveEvent( QMouseEvent* event );
		void paintEvent( QPaintEvent* event );
		
	private:
		int selectedTool_;
		int nSides_;
		int radius;
		int rx;
		int ry;
		int nClicks;
		double polygonAngle;
		bool firstDone;
		bool pencilActive;
		bool eraserActive;
		bool sprayActive;
		bool clicked;
		PixelInfo* pixelInfo;
		PixelInfo* tempInfo;
		QPoint clickPoint;
		QPoint curPoint;
		QPoint* splinePoints;
		QColor color;
		QColor bgColor;
		QPainter painter;
		QTimer* timer;
		
		void putCirclePixels( int x, int y, int xC, int yC );
		void putEllipsePixels( int x, int y, int xC, int yC );
		QPoint* getVertex( int xC, int yC, int r, float angle );
		void correctPixelPlacement( int newWidth, int newHeight, int oldWidth, int oldHeight );
};

#endif //PAINT_WIDGET_H
