#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QTextCursor>
#include <QResizeEvent>
#include <QFont>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_input_textChanged(const QString &arg1);

    void on_input_returnPressed();

    void on_pushButton_clicked();

    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    QFile words;
    QTextStream in;
    bool allSeen;
};
#endif // MAINWINDOW_H
