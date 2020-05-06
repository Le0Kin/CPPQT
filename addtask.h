#ifndef ADDTASK_H
#define ADDTASK_H

#include <QObject>

class addTask : public QObject
{
    Q_OBJECT
public:
    explicit addTask(QObject *parent = nullptr);

public:
    Q_INVOKABLE QString id() const;
    Q_INVOKABLE void addId();

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName(const QString &name);

    Q_INVOKABLE QString description() const;
    Q_INVOKABLE void setDescription(const QString &description);

    Q_INVOKABLE QString dateStart() const;
    Q_INVOKABLE void setDateStart(const QString &dateStart);

    Q_INVOKABLE QString dateEnd() const;
    Q_INVOKABLE void setDateEnd(const QString &dateEnd);

    Q_INVOKABLE QString progress() const;
    Q_INVOKABLE void setProgress(const QString &progress);

private:
    qint32 m_id;
    QString m_name;
    QString m_description;
    QString m_dateStart;
    QString m_dateEnd;
    QString m_progress;
};

#endif // ADDTASK_H
