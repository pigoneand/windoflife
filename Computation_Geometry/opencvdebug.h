
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <string>
#include <vector>
#include <utility>
using namespace std;

namespace Drawing
{

  const int DEBUGWINSIZE = 256;
  double debugMaxCoor;
  IplImage * drawingImage = NULL;

  void cvText(IplImage* img, const char* text, int x, int y)
  {
    CvFont font;
    double hscale = 0.5;
    double vscale = 0.5;
    int linewidth = 1;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC,hscale,vscale,0,linewidth);
    CvScalar textColor =cvScalar(0,255,255);
    CvPoint textPos =cvPoint(x, y);
    cvPutText(img, text, textPos, &font,textColor);
  }

  inline CvPoint getPoint(const Point & p) { return cvPoint(p.x * DEBUGWINSIZE / debugMaxCoor + DEBUGWINSIZE
    , DEBUGWINSIZE - p.y * DEBUGWINSIZE / debugMaxCoor); }

  inline double getLen(double r) { return r * DEBUGWINSIZE / debugMaxCoor; }

  string toString(double d)
  {
    char temp[20];
    sprintf(temp, "%.2f", d);
    return string(temp);
  }

  void init(double maxCoor)
  {  
    if (drawingImage == NULL)
      drawingImage = cvCreateImage(cvSize(DEBUGWINSIZE * 2, DEBUGWINSIZE * 2), 8, 3);
    cvZero(drawingImage);

    cvLine(drawingImage, cvPoint(DEBUGWINSIZE, 0), cvPoint(DEBUGWINSIZE, DEBUGWINSIZE * 2 - 1), CV_RGB(0, 0, 255));
    cvLine(drawingImage, cvPoint(0, DEBUGWINSIZE), cvPoint(DEBUGWINSIZE * 2 - 1, DEBUGWINSIZE), CV_RGB(0, 0, 255));

    debugMaxCoor = maxCoor;
  }

  void clear()
  {
    if (drawingImage != NULL) 
      init(debugMaxCoor);
  }

  void drawPoints(const vector<Point> & ps, 
    CvScalar color = CV_RGB(255, 0, 0))
  {
    for (int i = 0; i < (int) ps.size(); ++i)
      cvCircle(drawingImage, getPoint(ps[i]), 1, color, 3);
  }

  void drawPoint(const Point & p, CvScalar color = CV_RGB(255, 0, 0))
  {
    cvCircle(drawingImage, getPoint(p), 1, color, 3);
  }

  void drawSegs(vector<pair<Point, Point> > & lines, 
    CvScalar color = CV_RGB(0, 255, 0))
  {
    for (int i = 0; i < (int) lines.size(); ++i)
      cvLine(drawingImage, getPoint(lines[i].first), getPoint(lines[i].second), color);
  }

  void drawSeg(const Point & a, const Point & b, 
    CvScalar color = CV_RGB(0, 255, 0))
  {
    //if (a.id < 0 || b.id < 0) color = CV_RGB(255, 255, 0);
    cvLine(drawingImage, getPoint(a), getPoint(b), color);
  }

  void drawTriangle(const Point & a, const Point & b, const Point & c)
  {
    drawPoint(a);
    drawPoint(b);
    drawPoint(c);
    drawSeg(a, b);
    drawSeg(b, c);
    drawSeg(a, c);
  }

  void drawCircle(Point & o, double r)
  {
    cvCircle(drawingImage, getPoint(o), getLen(r), CV_RGB(255, 255, 0), 1);
  }

  void showDrawing(int wait = 0)
  {
    if (drawingImage == NULL) return;
    cvNamedWindow("drawing");
    cvMoveWindow("drawing", 800, 0);
    cvShowImage("drawing", drawingImage);
    cvWaitKey(wait);
  }
}