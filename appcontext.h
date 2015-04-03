#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>

class AppContext : public QObject
{
    Q_OBJECT
public:
    explicit AppContext(QObject *parent = 0);
    ~AppContext();

signals:

public slots:
};

#endif // APPCONTEXT_H
