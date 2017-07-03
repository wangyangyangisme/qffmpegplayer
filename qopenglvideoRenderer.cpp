
#include "qopenglvideorenderer.h"

#include <windows.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include "gl/glut.h"
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <iostream>


QOpenGLVideoRenderer::QOpenGLVideoRenderer()
{
	eye = 0;
	installEventFilter(this);
	setMouseTracking(true);
    glewInit();
}


void QOpenGLVideoRenderer::initializeGL()
{

    glClearColor(1.0, 1.0, 0, 1.0);
    shader = new Shader();
    shader->loadFromFile("C:\\Users\\huang\\Documents\\build-VRPlayer-Desktop_Qt_5_6_2_MSVC2013_64bit-Debug\\debug\\Shader.vert","C:\\Users\\huang\\Documents\\build-VRPlayer-Desktop_Qt_5_6_2_MSVC2013_64bit-Debug\\debug\\Shader.frag");
	tx = new QOpenGLTexture(QOpenGLTexture::Target2D);
	
}

void QOpenGLVideoRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
	shader->bind();
	GLint location1 = shader->getUniLocation("eyeseparation");
	glUniform1f(location1, eye);

	GLint location = shader->getUniLocation("tex");
	if (location != -1)
	{
		glUniform1i(location, 0);
		glActiveTexture(GL_TEXTURE0);
		if(tx->isCreated())
		tx->bind();
	}


    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport( 0, 0, this->width(), this->height() );
    glOrtho(-1, 1, -1, 1, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2d(1,1);
    glVertex3d(1.0, -1.0, -1);
    glTexCoord2d(0,1);
    glVertex3d(-1.0, -1.0, -1);
    glTexCoord2d(0,0);
    glVertex3d(-1.0,  1.0, -1);
    glTexCoord2d(1,0);
    glVertex3d(1.0,  1.0, -1);
    glEnd();

    glPopMatrix();
	shader->unbind();

}

void QOpenGLVideoRenderer::updateFrame(const QImage& img)
{
	tx->setData(img, QOpenGLTexture::DontGenerateMipMaps);
	update();
}

void QOpenGLVideoRenderer::setEyeSeparation(float v)
{
	eye = v;
}

void QOpenGLVideoRenderer::resizeGL(int w, int h)
{

}

void QOpenGLVideoRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (this->isFullScreen() == false) {
		this->showFullScreen();
	}
	else 
	{
		this->showNormal();
	}
}

void QOpenGLVideoRenderer::mouseMoveEvent(QMouseEvent *event)
{
	//controller->setVisible(true);
}

void QOpenGLVideoRenderer::mouseReleaseEvent(QMouseEvent *event)
{

}

bool QOpenGLVideoRenderer::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_1)
		{
			eye = eye + 0.01;
			//qDebug() << "Up";
		}
			
		if (keyEvent->key() == Qt::Key_2)
		{
			eye = eye - 0.01;
			//qDebug() << "Down";
		}
			
	}
	return QObject::eventFilter(obj, event);
}

void QOpenGLVideoRenderer::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		std::cout << event->key() << std::endl;
	case Qt::Key_Escape:
		close();
		break;
	case Qt::UpArrow:
		eye = eye + 0.1;
		break;
	case Qt::DownArrow:
		eye = eye - 0.1;
		break;
	default:
		break;
	}

	event->accept();
}
