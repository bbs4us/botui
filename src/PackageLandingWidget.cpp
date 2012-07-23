#include "PackageLandingWidget.h"
#include "ui_PackageLandingWidget.h"
#include "MenuBar.h"
#include "RootController.h"
#include "StatusBar.h"
#include "Device.h"
#include <QDebug>

PackageLandingWidget::PackageLandingWidget(Device *device, QWidget *parent)
	: QWidget(parent),
	ui(new Ui::PackageLandingWidget),
	m_device(device),
	m_menuBar(new MenuBar(this)),
	m_statusBar(new StatusBar(this))
{
	ui->setupUi(this);
	m_menuBar->addHomeAndBackButtons();
	m_menuBar->setTitle("Packages");
	layout()->setMenuBar(m_menuBar);
	m_statusBar->loadDefaultWidgets(m_device);
	layout()->addWidget(m_statusBar);
}

PackageLandingWidget::~PackageLandingWidget()
{
	delete ui;
	delete m_menuBar;
	delete m_statusBar;
}