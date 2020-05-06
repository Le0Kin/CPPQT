#include "addtask.h"

addTask::addTask(QObject *parent) : QObject(parent),
  m_id(0), m_name(""), m_description(""), m_dateStart("00.00.0000"), m_dateEnd("00.00.0000"), m_progress("0%")
{

}

QString addTask::id() const
{
    return QString::number(m_id);
}

void addTask::addId()
{
    m_id += 1;
}

QString addTask::name() const
{
    return m_name;
}

void addTask::setName(const QString &name)
{
    m_name = name;
}

QString addTask::description() const
{
    return m_description;
}

void addTask::setDescription(const QString &description)
{
    m_description = description;
}

QString addTask::dateStart() const
{
    return m_dateStart;
}

void addTask::setDateStart(const QString &dateStart)
{
    QRegExp dateRX("[0-3][0-9]\.[0-1][0-9]\.[0-9][0-9][0-9][0-9]");
    dateRX.exactMatch(dateStart) ? m_dateStart = dateStart : m_dateStart = "00.00.0000";
}

QString addTask::dateEnd() const
{
    return m_dateEnd;
}

void addTask::setDateEnd(const QString &dateEnd)
{
    QRegExp dateRX("[0-3][0-9]\.[0-1][0-9]\.[0-9][0-9][0-9][0-9]");
    dateRX.exactMatch(m_dateEnd) ? m_dateEnd = dateEnd : m_dateEnd = "00.00.0000";
}

QString addTask::progress() const
{
    return m_progress;
}

void addTask::setProgress(const QString &progress)
{
    QRegExp progRX("[0-1]?[0-9]?[0-9]%");
    progRX.exactMatch(progress) ? m_progress = progress : m_progress = "0%";
}
