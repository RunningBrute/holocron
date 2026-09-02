#pragma once

#include <QObject>

class NodeManager : public QObject
{
    Q_OBJECT

public:
    explicit NodeManager(QObject *parent = nullptr);

    Q_INVOKABLE void start(int count);

signals:
    void nodeStarted(int count);
};