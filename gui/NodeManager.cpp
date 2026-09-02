#include "NodeManager.h"

#include <QDebug>

NodeManager::NodeManager(QObject *parent) : QObject(parent){}

void NodeManager::start(int count)
{
    qDebug() << "C++: starting" << count << "nodes";
    emit nodeStarted(count);
}