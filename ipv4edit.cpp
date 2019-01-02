#include "ipv4edit.h"

#include <QHostAddress>
#include <QtGui>
#include <QWidget>
#include <QHostAddress>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

IPv4Edit::IPv4Edit(QWidget *parent) :
    QFrame(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);
    QLabel *label;
    for(int i = 0; i < 4; i++)
    {
        QLineEdit *lineEdit= new QLineEdit(this);
        this->list.append(lineEdit);
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {border: 0}"));
        lineEdit->setContentsMargins(0, 0, 0, 0);
        QRegExp rx("(2[0-4]\\d|25[0-5]|0|1\\d\\d|[1-9]\\d?)");
        QValidator *validator = new QRegExpValidator(rx, lineEdit);
        lineEdit->setValidator(validator);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setFixedHeight(26);
        lineEdit->installEventFilter(this);
        hLayout->addWidget(lineEdit);
        label = new QLabel(this);
        label->setStyleSheet(QString::fromUtf8("QLineEdit {border: 0}"));
        label->setStyleSheet(QString::fromUtf8("QLabel {background-color: white}"));
        label->setText(".");
        label->setFixedHeight(23);
        hLayout->addWidget(label);
    }
    label->hide();
    label->close();
    this->setStyleSheet(QString::fromUtf8("QFrame {background-color: white;border: 1px solid gray} QLabel {border: 0}"));
    this->setMaximumHeight(30);
}

bool IPv4Edit::eventFilter(QObject *obj, QEvent *event)
{
    int tmp = 0;
    QLineEdit *lineEdit = NULL;
    for(int i = 0; i < list.size(); i++)
    {
        if(obj == list.at(i))
        {
            tmp = i;
            lineEdit = list.at(i);
            break;
        }
    }
    if((list.at(tmp) == obj) && (event->type() == QEvent::KeyPress)) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(((keyEvent->key() == Qt::Key_Left) || (keyEvent->key() == Qt::Key_Backspace)) && (lineEdit->cursorPosition() == 0) && (tmp != 0))
        {
            list.at(tmp-1)->setFocus();
            return true;
        } else if((((keyEvent->key() == Qt::Key_Right) && (lineEdit->text().size() == lineEdit->cursorPosition())) || (keyEvent->key() == Qt::Key_Period))
            && (tmp != (list.size() - 1)))
        {
            list.at(tmp+1)->setFocus();
            return true;
        } else if((keyEvent->key() == Qt::Key_Space) && (tmp != (list.size() - 1)))
        {
            list.at(tmp+1)->setFocus();
            list.at(tmp+1)->setSelection(0, list.at(tmp+1)->text().size());
            return true;
        }  else
            return false;
    } else {
        return QFrame::eventFilter(obj, event);
    }
}

quint32 IPv4Edit::toIPv4Address()
{
    QHostAddress *hostAddress = new QHostAddress(text());
    return hostAddress->toIPv4Address();
}


QString IPv4Edit::text()
{
    QString tmp;
    for(int i = 0; i < list.size(); ++i)
    {
        tmp = tmp + list.at(i)->text() + QString(".");
    }
    tmp.truncate(tmp.size()-1);
    return tmp;
}

void IPv4Edit::setText(QString text)
{
    QStringList segs = text.split('.');
    if(segs.size() < 4)
        return;
    else
    {
        for (int i=0 ; i<list.size(); i++)
        {
            list.at(i)->setText(segs.at(i));
        }
    }

}

int IPv4Edit::getValidCount()
{
    int count = 0;
    for(int i = 0; i < list.size(); i ++)
    {
        if(!(list.at(i)->text().isEmpty()))
            count ++;
    }
    return count;
}
