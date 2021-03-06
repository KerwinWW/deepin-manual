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

#ifndef DEEPIN_MANUAL_DBUS_MANUAL_SEARCH_PROXY_H
#define DEEPIN_MANUAL_DBUS_MANUAL_SEARCH_PROXY_H

#include <DSysInfo>

/**
 * @brief The ManualSearchProxy class
 * 用于判断是否存在给定应用名称对应的帮助手册内容
 */
class ManualSearchProxy : public QObject
{
    Q_OBJECT
public:
    explicit ManualSearchProxy(QObject *parent = nullptr);
    ~ManualSearchProxy() override;

signals:
    void SendWinInfo(const QString &data);

public slots:
    bool ManualExists(const QString &app_name);

private slots:
    void RecvMsg(const QString &data);
    void OnNewWindowOpen(const QString &data);

private:
    void initDBus();
    void connectToSender();

    bool m_bWindowState;
    QString m_sApplicationPid = nullptr;
};

#endif // DEEPIN_MANUAL_DBUS_MANUAL_SEARCH_PROXY_H
