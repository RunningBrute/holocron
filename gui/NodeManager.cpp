#include "NodeManager.h"

#include <QDebug>
#include <QCoreApplication>

NodeManager::NodeManager(QObject *parent)
    : QObject(parent)
{}

void NodeManager::start(int count)
{
    qDebug() << "Starting supervisor with" << count << "nodes";

    const auto nodesCount = QString::number(count);
    const auto supervisorPath = QCoreApplication::applicationDirPath() + "/supervisor";
    supervisorProcess.start(supervisorPath, {nodesCount});

    if (!supervisorProcess.waitForStarted())
    {
        qDebug() << "Failed to start supervisor:" << supervisorProcess.errorString();
        return;
    }

    connect(&supervisorProcess, &QProcess::finished,
        this, [](int exitCode, QProcess::ExitStatus status) {
            qDebug() << "Process finished:" << "exitCode =" << exitCode << "status =" << status;
        });

    connect(&supervisorProcess, &QProcess::errorOccurred,
        this, [](QProcess::ProcessError error) {
            qDebug() << "Process error:" << error;
        });

    connect(&supervisorProcess, &QProcess::readyReadStandardOutput,
        this, [this]() {
            qDebug().noquote() << "SUPERVISOR:" << supervisorProcess.readAllStandardOutput();
        });

    connect(&supervisorProcess, &QProcess::readyReadStandardError,
        this, [this]() {
            qDebug().noquote() << "SUPERVISOR ERR:" << supervisorProcess.readAllStandardError();
        });

    qDebug() << "Supervisor started, PID:" << supervisorProcess.processId();

    emit nodesStarted(count);
}
