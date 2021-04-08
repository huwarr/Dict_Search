#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , words(QDir::currentPath() + "/words.txt")
    , allSeen(false)
{
    ui->setupUi(this);
    words.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::NewOnly);
    if (words.open(QIODevice::ReadOnly | QIODevice::Text)) {
        in.setDevice(&words);
    } else {
        QMessageBox msg;
        msg.setText("WTF");
        msg.exec();
        this->~MainWindow();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void add_word(const QString &word, const QString &inp, QTextEdit *output) {
    auto iter = word.begin();
    int j = 0;
    while (iter != word.end()) {
        if (j < inp.size() && inp[j] == *iter) {
            output->moveCursor (QTextCursor::End);
            output->insertHtml("<b>" + QString(*iter) + "</b>");
            j++;
        } else {
            output->moveCursor (QTextCursor::End);
            output->insertHtml(*iter);
        }
        iter++;
    }
}

void MainWindow::on_input_textChanged(const QString &inp)
{
    ui->output->clear();
    if (inp.isEmpty())
        return ;
    in.seek(0);
    QString word;
    int lines = ui->output->height() / ui->output->fontMetrics().height() - 1.5;
    int i;
    for (i = 0; i < lines && !in.atEnd();) {
        in >> word;
        if (word.contains(inp)) {
            add_word(word, inp, ui->output);
            if (i < lines - 1)
                ui->output->append("");
            i++;
        }
    }
    if (i == lines) {
        allSeen = false;
        ui->output->append("...");
    } else {
        if (i > 0) {
            ui->output->append("");
            ui->output->insertHtml("<i>the end</i>");
        }
        allSeen = true;
    }
}

void MainWindow::on_input_returnPressed()
{
    ui->pushButton->click();
}

void MainWindow::on_pushButton_clicked()
{
    if (!allSeen) {
        allSeen = true;
        ui->output->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->output->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        ui->output->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
        ui->output->textCursor().removeSelectedText();
        ui->output->textCursor().deletePreviousChar();
        QString word;
        QString inp = ui->input->text();
        while(!in.atEnd()) {
            in >> word;
            if (word.contains(inp)) {
                add_word(word, inp, ui->output);
                ui->output->append("");
            }
        }
        ui->output->append("");
        ui->output->insertHtml("<i>the end</i>");
        ui->output->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
    }
    ui->centralwidget->setFocus();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   this->on_input_textChanged(ui->input->text());
   QMainWindow::resizeEvent(event);
}
