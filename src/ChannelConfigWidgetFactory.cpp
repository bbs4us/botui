/* FIXME
#include "ChannelConfigWidgetFactory.h"

#include "ChannelConfigWidget.h"
#include "HsvChannelConfigWidget.h"

#ifdef WALLABY
#include <wallaby/camera.hpp>
#else
#include <kovan/camera.hpp>
#endif

ChannelConfigWidgetFactory::~ChannelConfigWidgetFactory()
{
}

bool ChannelConfigWidgetFactory::hasConfig(const QString &type)
{
	if(type == CAMERA_CHANNEL_TYPE_HSV_KEY) return true;
	
	return false;
}

ChannelConfigWidget *ChannelConfigWidgetFactory::create(const QModelIndex &index, const QString &type)
{
	if(type == CAMERA_CHANNEL_TYPE_HSV_KEY) return new HsvChannelConfigWidget(index);
	return 0;
}

ChannelConfigWidgetFactory::ChannelConfigWidgetFactory()
{
}
*/
