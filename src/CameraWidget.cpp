#include "CameraWidget.h"

#include <QDebug>

#ifdef WALLABY
#include <wallaby/camera.hpp>
#else
#include <kovan/camera.hpp>
#endif

CameraWidget::CameraWidget(QWidget *parent)
  : CvWidget(parent),
  m_camDevice(new Camera::Device()),
  m_timer(new QTimer(this))
{  
  connect(m_timer, SIGNAL(timeout()), SLOT(update()));
  this->fastFrameRate();
}

CameraWidget::~CameraWidget()
{
  m_camDevice->close();
  delete m_timer;
  delete m_camDevice;
}

void CameraWidget::setConfig(Config *config)
{
  m_camDevice->setConfig(config ? *config : Config());
}

void CameraWidget::setChannelConfig(const Config &config, int channelNum)
{
  if(m_camDevice->channels().size() <= channelNum)
    return;
  
  m_camDevice->channels()[channelNum]->setConfig(config);
}

void CameraWidget::setTrackBlobs(const bool trackBlobs)
{
  m_trackBlobs = trackBlobs;
}

bool CameraWidget::trackBlobs() const
{
  return m_trackBlobs;
}

// TODO: Make it configurable which channels to show
void CameraWidget::update()
{
  if(!m_camDevice->isOpen()) {
    // Camera isn't open, so try to open
    if(!m_camDevice->open()) {
      // Camera not available; lower frame rate and quit
      this->slowFrameRate();
      return;
    }
    
    // Successfully opened camera; raise frame rate
    this->fastFrameRate();
  }
  
  if(!isVisible()) return;
  
  cv::Mat image;
  if(!m_camDevice->update()) {
    // Update failed, so close camera and lower frame rate
    m_camDevice->close();
    this->slowFrameRate();
  }
  else {
    qDebug() << "Camera updated!";
    image = m_camDevice->rawImage();
    if(m_trackBlobs) {
      int h = 0;
      const static int hStep = 137; // Golden angle
      Camera::ChannelPtrVector::const_iterator it = m_camDevice->channels().begin();
      for(; it != m_camDevice->channels().end(); ++it, h += hStep) {
        const QColor rectColor = QColor::fromHsv(h % 360, 255, 255);
        const Camera::ObjectVector *objs = (*it)->objects();
        Camera::ObjectVector::const_iterator oit = objs->begin();
        for(; oit != objs->end(); ++oit) {
          const Camera::Object &obj = *oit;
          cv::rectangle(image, cv::Rect(obj.boundingBox().x(), obj.boundingBox().y(),
            obj.boundingBox().width(), obj.boundingBox().height()),
            cv::Scalar(rectColor.red(), rectColor.blue(), rectColor.blue()), 2);
        }
      }
    }
  }
  
  this->updateImage(image);
}

void CameraWidget::setFrameRate(const unsigned frameRate)
{
  if(frameRate == m_frameRate)
    return;
  
  m_frameRate = frameRate;
  if(m_frameRate == 0)
    m_timer->stop();
  else
    m_timer->start(1000.0 / m_frameRate); 
}

void CameraWidget::slowFrameRate()
{
  this->setFrameRate(1);
}

void CameraWidget::fastFrameRate()
{
  this->setFrameRate(10);
}