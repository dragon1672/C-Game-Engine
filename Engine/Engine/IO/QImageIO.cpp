#include "QImageIO.h"
#include <QtWidgets\QApplication>
#include <QtCore\QFile>
#include <Engine\Tools\Printer.h>
#include <cassert>
#include <QtOpenGL/QGLWidget>
#include <QtCore/QDebug>

namespace FileIO {
	QString formatFileName(QString& fileName) {
		QString formatedName = fileName.replace(QRegExp("[_]")," ");
		formatedName = formatedName.remove(".jpg",Qt::CaseInsensitive);
		formatedName = formatedName.remove(".png",Qt::CaseInsensitive);
		int lastSlash = formatedName.lastIndexOf('/');
		formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
		lastSlash = formatedName.lastIndexOf('\\');
		formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
		return formatedName;
	}

	QImage getImageFromFile(QString& fileName, bool flipHorz, bool flipVert) {
		QImage myTexture = QGLWidget::convertToGLFormat(QImage(fileName).mirrored(flipHorz,flipVert));

		if(myTexture.isNull()) {
			qDebug() << "attempt to load " << fileName << " failed";
			assert(false);
		} else {
			QString formatedName = fileName.replace(QRegExp("[_]")," ");
			formatedName = formatedName.remove(".jpg",Qt::CaseInsensitive);
			formatedName = formatedName.remove(".png",Qt::CaseInsensitive);
			int lastSlash = formatedName.lastIndexOf('/');
			formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
			lastSlash = formatedName.lastIndexOf('\\');
			formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
			qDebug() << "Texture Loaded ( " << myTexture.width() << "x" << myTexture.width() << " ): " << formatFileName(fileName);
		}

		return myTexture;
	}

	QImage loadImage(const char * path, bool flipHorz /*= false*/, bool flipVert /*= false*/)
	{
		QString data(path);
		return getImageFromFile(data,flipHorz,flipVert);
	}

	QImage loadImage(std::string path, bool flipHorz /*= false*/, bool flipVert /*= false*/)
	{
		return loadImage(path.c_str(),flipHorz,flipVert);
	}

}