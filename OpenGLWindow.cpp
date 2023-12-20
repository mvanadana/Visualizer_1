#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>

#include "SutherlandHodgeman.h"
#include "HermiteCurve.h"
#include "BeizerCurve.h"
#include "BSplineCurve.h"
#include "SimpleDDA.h"
#include "Grid.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) :
    mBackground(background), mClippingPolygon({})
{
    setParent(parent);
    setMinimumSize(300, 250);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    setupMatrix();
   

    addClippingPolygonVertices(vertices, colors);
    addPolygonsVertices(vertices, colors);
    addLinesVertices(vertices, colors);

    drawVertices(vertices, colors);

    mProgram->release();
}

void OpenGLWindow::clipPolygons()
{
    for (int i = 0; i < mPolygons.size(); i++) {
        SutherlandHodgeman sh(mClippingPolygon, mPolygons.at(i));
        mPolygons.at(i) = sh.getClippedPolygon();
    }
    emit shapesUpdated();
}


void OpenGLWindow::addClippingPolygon(Shape* s)
{
    mClippingPolygon = *s;
    emit shapesUpdated();
}

void OpenGLWindow::addPolygons(Shape* s)
{
    mPolygons.push_back(*s);
    emit shapesUpdated();
}

void OpenGLWindow::addLines(Line line)
{
    SimpleDDA sdd;
    sdd.drawLineBySimpleDDA(line, mPixelVertices);
    createFill(mPixelVertices);

    
}
void OpenGLWindow::drawGrid(int gridsize)
{
    mGridSize = gridsize;
    Grid grid(vertices, colors, mGridSize);
    emit shapesUpdated();
}
void OpenGLWindow::addHermiteCurve(std::vector<Point> points)
{
    HermiteCurve bs(points);
    std::vector<Point> hermitePoints = bs.calculateHermite();

    if (hermitePoints.size() < 2) {
        return;
    }
    addCurveLines(hermitePoints);
    emit shapesUpdated();
}

void OpenGLWindow::addBezierCurve(std::vector<Point> points)
{
    BeizerCurve bs(points);
    std::vector<Point> bezierPoints = bs.calculateBezier();

    if (bezierPoints.size() < 2) {
        return;
    }
    addCurveLines(bezierPoints);
    emit shapesUpdated();
}

void OpenGLWindow::createFill(std::vector<float>squareVertices)
{
    
    int i = 0;
    while (i < squareVertices.size()) {
        std::vector < float>qv;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        qv.push_back(squareVertices[i]);
        i++;
        QVector3D fillColor(1.0f, 0.0f, 0.0f);
        fillSquare(qv, fillColor);

    }
   
}
void OpenGLWindow::fillSquare(std::vector<float> qv, QVector3D fillColor)
{
    

    if (qv.size() % 2 != 0) {
        return;
    }

    for (size_t i = 0; i < qv.size(); i += 2) {
        float x = qv[i];
        float y = qv[i + 1];
        vertices << x << y;
        colors << fillColor.x() << fillColor.y() << fillColor.z();
    }
  
    
}
void OpenGLWindow::addBSplineCurve(std::vector<Point> points)
{
    BSplineCurve bs(3);
    std::vector<Point> bsplinePoints = bs.evaluate(points, 100);

    if (bsplinePoints.size() < 2) {
        return;
    }
    addCurveLines(bsplinePoints);
    emit shapesUpdated();
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::setupMatrix()
{
    QMatrix4x4 matrix;
    matrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    mProgram->setUniformValue(m_matrixUniform, matrix);
}

void OpenGLWindow::addClippingPolygonVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    addShapeVertices(mClippingPolygon, vertices, colors, 1.0f, 1.0f, 0.0f);
}

void OpenGLWindow::addPolygonsVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    for (int i = 0; i < mPolygons.size(); i++) {
        addShapeVertices(mPolygons.at(i), vertices, colors, 1.0f, 1.0f, 1.0f);
    }
}

void OpenGLWindow::addLinesVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    addShapeVertices(mLines, vertices, colors, 0.0f, 1.0f, 1.0f);
}

void OpenGLWindow::addShapeVertices(Shape shape, QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float red, float green, float blue)
{
    std::vector<Line> lines = shape.getShape();
    for (int j = 0; j < lines.size(); j++) {
        vertices << lines.at(j).p1().x() << lines.at(j).p1().y();
        vertices << lines.at(j).p2().x() << lines.at(j).p2().y();
        colors << red << green << blue;
        colors << red << green << blue;
    }
}

void OpenGLWindow::addCurveLines(const std::vector<Point>& points)
{
    for (int i = 0; i < points.size() - 1; i++) {
        mLines.push_back(Line(points[i], points[i + 1]));
    }
}

void OpenGLWindow::drawVertices(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors)
{
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}
