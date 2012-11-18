/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c NMSettingsConnection -p NMSettingsConnection -N -i NetworkManagerConnection.h nm-settings-connection.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NMSETTINGSCONNECTION_H_1353213530
#define NMSETTINGSCONNECTION_H_1353213530

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "NetworkManagerConnection.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManager.Settings.Connection
 */
class NMSettingsConnection: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.Settings.Connection"; }

public:
    NMSettingsConnection(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NMSettingsConnection();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Delete()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Delete"), argumentList);
    }

    inline QDBusPendingReply<Connection> GetSecrets(const QString &setting_name)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(setting_name);
        return asyncCallWithArgumentList(QLatin1String("GetSecrets"), argumentList);
    }

    inline QDBusPendingReply<Connection> GetSettings()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetSettings"), argumentList);
    }

    inline QDBusPendingReply<> Update(Connection properties)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(properties);
        return asyncCallWithArgumentList(QLatin1String("Update"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void Removed();
    void Updated();
};

#endif