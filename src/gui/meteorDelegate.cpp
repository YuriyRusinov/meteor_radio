/*
 * @brief Делегат для редактирования параметров
 * meteorDelegate.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QLineEdit>
#include <QValidator>
#include <QDoubleValidator>
#include "meteorDelegate.h"

meteorDelegate::meteorDelegate( QObject* parent ) : QItemDelegate( parent ) {}
meteorDelegate::~meteorDelegate() {}

QWidget *meteorDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    QLineEdit* lE = new QLineEdit( parent );
    QValidator* val = new QDoubleValidator( 0.0, 10000.0, 16, parent );
    lE->setValidator( val );
    lE->resize( option.rect.size() );
    return lE;
}

void meteorDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const {
    QLineEdit* lE = qobject_cast< QLineEdit *>(editor);
    lE->setText( index.data( Qt::DisplayRole ).toString() );
}

void meteorDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const {
    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
    QString wText = lE->text();
    model->setData( index, wText, Qt::EditRole );
}

void meteorDelegate::updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    if( editor )
        editor->setGeometry( option.rect );
}
