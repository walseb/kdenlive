/***************************************************************************
 *   Copyright (C) 2017 by Nicolas Carion                                  *
 *   This file is part of Kdenlive. See www.kdenlive.org.                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3 or any later version accepted by the       *
 *   membership of KDE e.V. (or its successor approved  by the membership  *
 *   of KDE e.V.), which shall act as a proxy defined in Section 14 of     *
 *   version 3 of the license.                                             *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "assetlistwidget.hpp"
#include "assets/assetlist/view/qmltypes/asseticonprovider.hpp"
#include "kdenlivesettings.h"

#include <KDeclarative/KDeclarative>
#include <QQmlContext>
#include <QQuickItem>
#include <QStandardPaths>

AssetListWidget::AssetListWidget(QWidget *parent)
    : QQuickWidget(parent)
{
}

void AssetListWidget::setup()
{
    KDeclarative::KDeclarative kdeclarative;
    kdeclarative.setDeclarativeEngine(engine());
    kdeclarative.setupBindings();

    setResizeMode(QQuickWidget::SizeRootObjectToView);
    engine()->addImageProvider(QStringLiteral("asseticon"), m_assetIconProvider.get());
    setSource(QUrl(QStringLiteral("qrc:/qml/assetList.qml")));
    setFocusPolicy(Qt::StrongFocus);
}

QString AssetListWidget::getName(const QModelIndex &index) const
{
    return m_model->getName(m_proxyModel->mapToSource(index));
}

QString AssetListWidget::getDescription(const QModelIndex &index) const
{
    return m_model->getDescription(m_proxyModel->mapToSource(index));
}

void AssetListWidget::setFilterName(const QString &pattern)
{
    m_proxyModel->setFilterName(!pattern.isEmpty(), pattern);
    if (!pattern.isEmpty()) {
        QVariantList mapped;
        for (const QModelIndex &ix : m_model->getChildrenIndexes()) {
            mapped << m_proxyModel->mapFromSource(ix);
        }
        QMetaObject::invokeMethod(rootObject(), "expandNodes", Qt::QueuedConnection, Q_ARG(QVariant, mapped));
    }
}

QVariantMap AssetListWidget::getMimeData(const QString &assetId) const
{
    QVariantMap mimeData;
    mimeData.insert(getMimeType(assetId), assetId);
    return mimeData;
}

void AssetListWidget::activate(const QModelIndex &ix)
{
    const QString assetId = m_model->data(m_proxyModel->mapToSource(ix), AssetTreeModel::IdRole).toString();
    const QVariantMap data = getMimeData(assetId);
    emit activateAsset(data);
}

bool AssetListWidget::showDescription() const
{
    return KdenliveSettings::showeffectinfo();
}

void AssetListWidget::setShowDescription(bool show)
{
    KdenliveSettings::setShoweffectinfo(show);
    emit showDescriptionChanged();
}
