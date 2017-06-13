/***************************************************************************
 *   Copyright (C) 2017 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
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

#ifndef EFFECTSTACKVIEW_H
#define EFFECTSTACKVIEW_H

#include <QWidget>
#include <memory>
#include <QItemDelegate>

class QVBoxLayout;
class QTreeView;
class CollapsibleEffectView;
class AssetParameterModel;
class EffectStackModel;
class EffectItemModel;
class AssetIconProvider;

class WidgetDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit WidgetDelegate(QObject *parent = nullptr);
    void setHeight(const QModelIndex &index, int height);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QMap<QModelIndex, int> m_height;
};

class EffectStackView : public QWidget
{
Q_OBJECT

public:
    EffectStackView(QWidget *parent = nullptr);
    virtual ~EffectStackView();
    void setModel(std::shared_ptr<EffectStackModel>model);
    void unsetModel(bool reset = true);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    QVBoxLayout *m_lay;
    QTreeView *m_effectsTree;
    std::shared_ptr<EffectStackModel> m_model;
    std::vector<CollapsibleEffectView *> m_widgets;
    AssetIconProvider *m_thumbnailer;
    const QString getStyleSheet();
    void loadEffects(int start = 0, int end = -1);

private slots:
    void refresh(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void slotAdjustDelegate(std::shared_ptr<EffectItemModel> effectModel, int height);

};

#endif
