#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
class QCheckBox;
class QSize;
class QMessageBox;
class QProgressBar;
class QFileInfo;
QT_END_NAMESPACE

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget* parent = nullptr);

private slots:
    void browse();
    void browse2();
    void find();
    void animateFindClick();
    void openFileOfItem(int row, int column);
    void contextMenu(const QPoint& pos);
    void initCheckBoxGroup();
    void Run();
    

private:
    QStringList findFiles(const QStringList& files, const QString& text);
    void showFiles(const QStringList& paths);
    QComboBox* createComboBox(const QString& text = QString());
    void createFilesTable();
    
    QComboBox* fileComboBox;
    QComboBox* textComboBox;
    QComboBox* directoryComboBox;
    QLabel* filesFoundLabel;
    QPushButton* findButton;
    QTableWidget* filesTable;

    QDir currentDir;
    //////////////////////////// Edit//
    QString FileName;
    QString ext;
    QLabel* label;
    QLabel* label2;
    QLineEdit* lineEdit;
    QLineEdit* lineEdit2;
    QCheckBox* comcheck;
    QCheckBox* decomcheck;
    QProgressBar* progressBar;
};
//! [0]

#endif