#include <QtWidgets>
#include "huffmancode.h"
#include "window.h"

//! [17]
enum { absoluteFileNameRole = Qt::UserRole + 1 };
//! [17]

//! [18]
static inline QString fileNameOfItem(const QTableWidgetItem* item)
{
    return item->data(absoluteFileNameRole).toString();
}
//! [18]

//! [14]
static inline void openFile(const QString& fileName)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
//! [14]

//! [0]
Window::Window(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Zip Program "));
    const QSize buttonsize=QSize(60, 20);
    QPushButton* browseButton = new QPushButton(tr("&Browse..."), this);
    //browseButton->setFixedSize(buttonsize);
    connect(browseButton, &QAbstractButton::clicked, this, &Window::browse);
     QPushButton* browseButton2= new QPushButton(tr("&Browse..."), this);
     connect(browseButton2, &QAbstractButton::clicked, this, &Window::browse2);
     QPushButton* RunButton = new QPushButton(tr("&Run"), this);
     RunButton->setFixedSize(buttonsize);
     connect(RunButton, &QAbstractButton::clicked, this, &Window::Run);
     //QPushButton* CancelButton = new QPushButton(tr("&Cancel"), this);
     //CancelButton->setFixedSize(buttonsize);
     progressBar = new QProgressBar;
     this->setWindowIcon(QIcon(tr("C:/Users/88697/Desktop/Program Group.ico")));
    label = new QLabel(tr("Input File:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);
    label2 = new QLabel(tr("Ouput dir:"));
    lineEdit2 = new QLineEdit;
    label2->setBuddy(lineEdit2);
    comcheck = new QCheckBox(tr("zip"));
    decomcheck = new QCheckBox(tr("unzip"));
    this->resize(450, 150);

    initCheckBoxGroup();
    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label,1,0);
    mainLayout->addWidget(lineEdit, 1, 1);
    mainLayout->addWidget(label2, 2, 0);
    mainLayout->addWidget(lineEdit2, 2, 1);
    mainLayout->rowStretch(2);
    mainLayout->addWidget(comcheck, 0, 0, 1, 1);
    mainLayout->addWidget(decomcheck, 0, 1, 1,1);
    mainLayout->addWidget(browseButton, 1, 2);
    mainLayout->addWidget(browseButton2, 2, 2);
    
    mainLayout->addWidget(progressBar, 3, 0,1,3);
    mainLayout->addWidget(RunButton,4,2);
    //mainLayout->addWidget(CancelButton, 3,2);
}

//! [2]
void Window::Run() {
    QMessageBox *msgbox;
    if (!comcheck->checkState() && !decomcheck->checkState()) {
        msgbox = new QMessageBox;
        msgbox->warning(this, tr("Warning!"), tr("  Choose 'zip' or 'unzip'  \n"),QMessageBox::Ok);
       
    }
    else if(comcheck->checkState()&&ext=="txt") {
        QString outext = "encode";
        QString outpath = lineEdit2->text();
        outpath += "/";
        outpath += FileName;
        outpath.replace(ext, outext);
        
        FILE* fi=fopen(lineEdit->text().toLocal8Bit().data(), "rb");
        FILE* fo=fopen(outpath.toLocal8Bit().data(), "wb");
        progressBar->reset();
        
        
        float cr;
        compress(fi, fo, progressBar,cr);
        msgbox = new QMessageBox;
        QString outmsg = tr(" Success zip the File\n CR is :  ");
        QString  t = QString::number(cr*100);
        outmsg += t;
        outmsg += "% !!  \n";
        msgbox->information(this, tr("Complete!"), outmsg, QMessageBox::Ok);
        
    }
    else if (decomcheck->checkState()&&ext=="encode") {
        QString outext = "decode";
        QString outpath = lineEdit2->text();
        outpath += "/";
        outpath += FileName;
        outpath.replace(ext, outext);
        
        FILE* fi = fopen(lineEdit->text().toLocal8Bit().data(), "rb");
        FILE* fo = fopen(outpath.toLocal8Bit().data(), "wb");
        
        progressBar->reset();
        decode(fi, fo, progressBar);
        msgbox = new QMessageBox;

        msgbox->information(this, tr("Complete!"), tr(" Success unzip the File  \n"), QMessageBox::Ok);

    }
    else {
        msgbox = new QMessageBox;
        msgbox->warning(this, tr("Warning!"), tr("  You are using wrong file format,Check it.  \n"), QMessageBox::Ok);
    }
}
void Window::initCheckBoxGroup() {
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(comcheck);
    pButtonGroup->addButton(decomcheck);

}
void Window::browse()
{
    //QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath());
    QFileInfo fi;
    QFileDialog myFileDialog(this);
    QString itemPath = myFileDialog.getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr(" txt files or encode files(*.txt *.encode)"));
    
    
    if (itemPath.isEmpty()) {
        lineEdit->setText(myFileDialog.directory().absolutePath());
    }
    else {
        lineEdit->setText(itemPath);

    }
    fi = QFileInfo(lineEdit->text());
    FileName = fi.fileName();
    ext = fi.suffix();
   
  
 
    
}
void Window::browse2()
{

    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));


    lineEdit2->setText(directory);
    
   
}
//! [2]

static void updateComboBox(QComboBox* comboBox)
{
    if (comboBox->findText(comboBox->currentText()) == -1)
        comboBox->addItem(comboBox->currentText());
}

//! [3]
void Window::find()
{
    filesTable->setRowCount(0);

    QString fileName = fileComboBox->currentText();
    QString text = textComboBox->currentText();
    QString path = QDir::cleanPath(directoryComboBox->currentText());
    currentDir = QDir(path);
    //! [3]

    updateComboBox(fileComboBox);
    updateComboBox(textComboBox);
    updateComboBox(directoryComboBox);

    //! [4]
    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFiles(files);
}
//! [4]

void Window::animateFindClick()
{
    findButton->animateClick();
}

//! [5]
QStringList Window::findFiles(const QStringList& files, const QString& text)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));

    //! [5] //! [6]
    QMimeDatabase mimeDatabase;
    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %n...", nullptr, files.size()).arg(i));
        QCoreApplication::processEvents();
        //! [6]

        if (progressDialog.wasCanceled())
            break;

        //! [7]
        const QString fileName = files.at(i);
        const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
        if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
            qWarning() << "Not searching binary file " << QDir::toNativeSeparators(fileName);
            continue;
        }
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}
//! [7]

//! [8]
void Window::showFiles(const QStringList& paths)
{
    for (const QString& filePath : paths) {
        const QString toolTip = QDir::toNativeSeparators(filePath);
        const QString relativePath = QDir::toNativeSeparators(currentDir.relativeFilePath(filePath));
        const qint64 size = QFileInfo(filePath).size();
        QTableWidgetItem* fileNameItem = new QTableWidgetItem(relativePath);
        fileNameItem->setData(absoluteFileNameRole, QVariant(filePath));
        fileNameItem->setToolTip(toolTip);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem* sizeItem = new QTableWidgetItem(QLocale().formattedDataSize(size));
        sizeItem->setData(absoluteFileNameRole, QVariant(filePath));
        sizeItem->setToolTip(toolTip);
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
        filesTable->setItem(row, 1, sizeItem);
    }
    filesFoundLabel->setText(tr("%n file(s) found (Double click on a file to open it)", nullptr, paths.size()));
    filesFoundLabel->setWordWrap(true);
}
//! [8]

//! [10]
QComboBox* Window::createComboBox(const QString& text)
{
    QComboBox* comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
//! [10]

//! [11]
void Window::createFilesTable()
{
    filesTable = new QTableWidget(0, 2);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setShowGrid(false);
    //! [15]
    filesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(filesTable, &QTableWidget::customContextMenuRequested,
        this, &Window::contextMenu);
    connect(filesTable, &QTableWidget::cellActivated,
        this, &Window::openFileOfItem);
    //! [15]
}
//! [11]


//! [12]

void Window::openFileOfItem(int row, int /* column */)
{
    const QTableWidgetItem* item = filesTable->item(row, 0);
    openFile(fileNameOfItem(item));
}

//! [12]

//! [16]
void Window::contextMenu(const QPoint& pos)
{
    const QTableWidgetItem* item = filesTable->itemAt(pos);
    if (!item)
        return;
    QMenu menu;
#ifndef QT_NO_CLIPBOARD
    QAction* copyAction = menu.addAction("Copy Name");
#endif
    QAction* openAction = menu.addAction("Open");
    QAction* action = menu.exec(filesTable->mapToGlobal(pos));
    if (!action)
        return;
    const QString fileName = fileNameOfItem(item);
    if (action == openAction)
        openFile(fileName);
#ifndef QT_NO_CLIPBOARD
    else if (action == copyAction)
        QGuiApplication::clipboard()->setText(QDir::toNativeSeparators(fileName));
#endif
}
//! [16]
