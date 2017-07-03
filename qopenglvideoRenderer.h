#ifndef QOPENGLVIDEOPLAYER_H
#define QOPENGLVIDEOPLAYER_H
#include "gl/glew.h"
#include <QOpenGLWidget>
#include <QVideoFrame>
#include "Shader.h"
#include <QOpenGLTexture>

class QOpenGLVideoRenderer : public QOpenGLWidget
{
public:
    QOpenGLVideoRenderer();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void updateFrame(const QImage& img);
	void setEyeSeparation(float v);
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	bool eventFilter(QObject *obj, QEvent *event);
    Shader* shader;
	QOpenGLTexture* tx;
	float eye;
};

#endif // QOPENGLVIDEOPLAYER_H