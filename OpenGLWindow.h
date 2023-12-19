#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

#include "Shape.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

signals:
    void shapesUpdated();

public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();

    void addLines(Line line);
    void addPolygons(Shape* s);
    void addClippingPolygon(Shape* s);
    void clipPolygons();
    void drawGrid(int gridSize);
    void addSplineCurve(std::vector<Point>mPoints);
    void addHermiteCurve(std::vector<Point> points);
    
   




protected:
    void paintGL() override;
    void initializeGL() override;
   
private:
    void reset();

    void setRegion(double xMin, double yMin, double xMax, double yMax);
    void drawRegion(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void drawPolygon(Shape s, QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void createFill();
    void fillSquare(std::vector<float>& mPixelVertices, const QVector3D& fillColor);

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    double x_max = 6;
    double y_max = 6;
    double x_min = -6;
    double y_min = -6;

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;

    Shape mClippingPolygon;
    std::vector<Shape> mPolygons;
    std::vector<Line> mLines;
    std::vector<float> mPixelVertices;
    int mGridSize;
    // Line line;
    std::vector<Point> mSplinePoints;
};