#include "EasyDeviceCommunicationProvider.h"
#include "Device.h"
#include "FilesystemProvider.h"
#include "CompilingWidget.h"

#include <easydevice/Server.h>
#include <easydevice/DiscoveryClient.h>
#include <easydevice/DeviceInfo.h>

#include <kiss-compiler/ArchiveWriter.h>
#include <kiss-compiler/Temporary.h>
#include <kiss-compiler/CompilerManager.h>

#include "RootController.h"

#include <QDebug>

EasyDeviceCommunicationProvider::EasyDeviceCommunicationProvider(Device *device)
	: CommunicationProvider(device),
	m_server(new EasyDevice::Server(this, this)),
	m_discovery(new EasyDevice::DiscoveryClient(this))
{
	bool success = true;
	
	EasyDevice::DeviceInfo deviceInfo;
	deviceInfo.setDeviceType("kovan");
	deviceInfo.setDisplayName("Kovan 1234");
	deviceInfo.setSerialNumber("N/A");
	
	if(!m_discovery->setup()) {
		qDebug() << "Failed to setup listener";
		success &= false;
	}
	m_discovery->setDeviceInfo(deviceInfo);
	if(!m_server->listen(QHostAddress::Any, 8075)) {
		qDebug() << "Failed to listen";
		success &= false;
	}
}

EasyDeviceCommunicationProvider::~EasyDeviceCommunicationProvider()
{
	delete m_server;
	delete m_discovery;
}

const bool EasyDeviceCommunicationProvider::run(const QString& name)
{
	return true;
}

CompilationPtr EasyDeviceCommunicationProvider::compile(const QString& name)
{
	FilesystemProvider *filesystem = device()->filesystemProvider();
	if(!filesystem) return CompilationPtr();
	
	TinyArchive *archive = filesystem->program(name);
	if(!archive) return CompilationPtr();
	
	RootController::ref().presentWidget(new CompilingWidget(device()));
	
	ArchiveWriter writer(archive, Temporary::subdir(name));
	QMap<QString, QString> settings;
	QByteArray rawSettings = QTinyNode::data(archive->lookup("settings:"));
	QDataStream stream(rawSettings);
	stream >> settings;
	
	CompilationPtr compilation(new Compilation(CompilerManager::ref().compilers(), name, writer.files(), settings, "kovan"));
	bool success = compilation->start();
	qDebug() << "Results:" << compilation->compileResults();
	
	qDebug() << (success ? "Compile Succeeded" : "Compile Failed");
	
	/* if(success) m_compileResults[name] = compilation->compileResults();
	else m_compileResults.remove(name); */
	
	RootController::ref().dismissWidget();
	
	return compilation;
}

const bool EasyDeviceCommunicationProvider::download(const QString& name, TinyArchive *archive)
{
	FilesystemProvider *filesystem = device()->filesystemProvider();
	qDebug() << "Calling setProgram";
	return filesystem && filesystem->setProgram(name, archive);
}