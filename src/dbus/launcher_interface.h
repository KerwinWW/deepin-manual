/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.deepin.dde.daemon.Launcher.xml -p launcher_interface -i dbus/dbusvariant/app_info.h -c LauncherInterface
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef LAUNCHER_INTERFACE_H
#define LAUNCHER_INTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "dbus/dbusvariant/app_info.h"

/*
 * Proxy class for interface com.deepin.dde.daemon.Launcher
 */
class LauncherInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.dde.daemon.Launcher"; }

public:
    LauncherInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LauncherInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<AppInfoList> GetAllItemInfos()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetAllItemInfos"), argumentList);
    }

    inline QDBusPendingReply<AppInfo> GetItemInfo(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("GetItemInfo"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void ItemChanged(const QString &in0, AppInfo in1, qlonglong in2);
};

namespace com {
  namespace deepin {
    namespace dde {
      namespace daemon {
        typedef ::LauncherInterface Launcher;
      }
    }
  }
}
#endif