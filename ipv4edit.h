#ifndef IPV4EDIT_H
#define IPV4EDIT_H

#include <QFrame>


class QValidator;
class QLineEdit;

class IPv4Edit : public QFrame
{
    Q_OBJECT

public:
    IPv4Edit(QWidget *parent = 0);

    quint32 toIPv4Address();
    int getValidCount();
    QString text();
    void setText(QString);
//    ~IPv4Edit();
protected:
    bool eventFilter(QObject *obj, QEvent *event);


private:
    QList<QLineEdit *> list;
};

#endif
