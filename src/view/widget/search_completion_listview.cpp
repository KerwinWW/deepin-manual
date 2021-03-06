#include "search_completion_listview.h"
#include "base/utils.h"

#include <QMouseEvent>

SearchCompletionListView::SearchCompletionListView(QWidget *parent)
    : DListView(parent)
{
    setAutoFillBackground(false);
    initDelegate();
}

SearchCompletionListView::~SearchCompletionListView()
{
}

void SearchCompletionListView::initDelegate()
{
    m_searchCompletionDelegate = new SearchCompletionDelegate(this);
    this->setItemDelegate(m_searchCompletionDelegate);
}

QStandardItemModel *SearchCompletionListView::getErrorListSourceModel()
{
    return m_searchCompletionSourceModel;
}

void SearchCompletionListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftMouse = true;
    } else {
        m_bLeftMouse = false;
    }

    DListView::mousePressEvent(event);
}

void SearchCompletionListView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    DListView::setSelection(rect, command);

    QPoint clickPoint(rect.x(), rect.y());
    QModelIndex modelIndex = indexAt(clickPoint);

    if (m_bLeftMouse) {
        emit onClickSearchCompletionItem(modelIndex);
    }
}

void SearchCompletionListView::paintEvent(QPaintEvent *event)
{
    DListView::paintEvent(event);
}
