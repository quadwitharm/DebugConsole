#ifndef TERMINAL_H
#define TERMINAL_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QByteArray>

class Terminal : public QTextEdit
{
public:
    explicit Terminal(QWidget *parent);
    ~Terminal();
public slots:
    void CommandOutput(QByteArray);
    void DebugOutput(QByteArray);
};

#endif // TERMINAL_H
