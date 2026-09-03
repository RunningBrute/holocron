#pragma once

#include <QObject>
#include <QProcess>

class NodeManager : public QObject
{
    Q_OBJECT

public:
    explicit NodeManager(QObject *parent = nullptr);

    Q_INVOKABLE void start(int count);

signals:
    void nodesStarted(int count);

private:
    QProcess supervisorProcess;
};