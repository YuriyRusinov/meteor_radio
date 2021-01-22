/*
 * @brief Делегат для редактирования параметров
 * meteorDelegate.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QItemDelegate>

class meteorDelegate : public QItemDelegate {
public:
    meteorDelegate( QObject* parent = nullptr );
    virtual ~meteorDelegate();

    QWidget *createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    void setEditorData( QWidget* editor, const QModelIndex& index ) const override;
    void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const override;
    void updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;

private:
    Q_OBJECT
};
