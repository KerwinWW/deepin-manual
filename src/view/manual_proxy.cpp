/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "view/manual_proxy.h"
#include "controller/config_manager.h"
#include "base/consts.h"
#include "base/utils.h"

namespace dman {

ManualProxy::ManualProxy(QObject *parent)
    : QObject(parent)
{
    AppInfo::registerMetaType();
}

ManualProxy::~ManualProxy() {}

QString ManualProxy::getSystemManualDir()
{
    QString str = Utils::getSystemManualDir();
    return str;
}

QStringList ManualProxy::getSystemManualList()
{
    QStringList list = Utils::getSystemManualList();
    saveAppList(list);
    return list;
}

void ManualProxy::openExternalLink(const QString &url)
{
    qDebug() << "ManualProxy::openExternalLink：" << url;
    QDesktopServices::openUrl(url);
}

/**
 * @brief ManualProxy::setApplicationState
 * @param appName
 * 应用图标点击后修改配置文件
 */
void ManualProxy::setApplicationState(const QString &appName)
{
    QString strApp;
    //部分传的是完整路径,部分直接是模块名称
    if (appName.contains("%2F")) {
        //以"%2F"分割字符,取倒数第三位为具体模块名
        QStringList strlist = appName.split("%2F");
        strApp = strlist.at(strlist.count() - 3);
    } else {
        strApp = appName;
    }
    qDebug() << "open app---->" << strApp;

    QSettings *setting = ConfigManager::getInstance()->getSettings();
    setting->beginGroup(CONFIG_APPLIST);
    if (setting->contains(strApp)) {
        setting->setValue(strApp, false);
        qDebug() << setting->applicationName() << setting->fileName() << ": " << appName << " state=false";
    } else {
        qDebug() << setting->fileName() << ": " << strApp << " not find";
    }
    setting->endGroup();
}

/**
 * @brief ManualProxy::getUsedAppList
 * @return
 * 获取已经使用过的应用列表
 */
QStringList ManualProxy::getUsedAppList()
{
    QSettings *setting = ConfigManager::getInstance()->getSettings();
    setting->beginGroup(CONFIG_APPLIST);
    QStringList list = setting->allKeys();
    QStringList appList;
    for (int i = 0; i < list.size(); ++i) {
        if (!setting->value(list.at(i)).toBool()) {
            appList.append(list.at(i));
        } else {
            continue;
        }
    }
    setting->endGroup();
    qDebug() << "The application of already used： " << appList;
    return appList;
}

/**
 * @brief ManualProxy::hasSelperSupport
 * @return
 * @note 显示服务与支持功能条件：　专业版并且已经安装 "uos-service-support"应用
 */
bool ManualProxy::hasSelperSupport()
{
    bool b = Utils::hasSelperSupport();
    return b;
}

void ManualProxy::finishChannel()
{
    emit channelInit();
}

/**
 * @brief ManualProxy::saveAppList
 * @param list
 * 保存应用列表至配置文件并设置状态
 */
void ManualProxy::saveAppList(const QStringList &list)
{
    Q_UNUSED(list)
    QSettings *setting = ConfigManager::getInstance()->getSettings();
    setting->beginGroup(CONFIG_APPLIST);
    for (int i = 0; i < list.size(); ++i) {
        if (setting->contains(list.at(i))) {
            continue;
        } else {
            setting->setValue(list.at(i), true);
        }
    }
    QStringList l = setting->allKeys();
    setting->endGroup();
    qDebug() << "app config  allKeys count : " << l.size();

}

}  // namespace dman

//bool ManualPro
