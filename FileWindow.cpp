#include "FileWindow.h"

FileWindow::FileWindow()
{
    //left layout
    returnBtn=new QPushButton("返回");
    this->leftLayout->addWidget(returnBtn);

    QTextEdit *leftTextEdit=new QTextEdit;
    this->leftLayout->addWidget(leftTextEdit);

    //right layout
    tabWidget=new QTabWidget;
    rightLayout->addWidget(tabWidget);


}

bool FileWindow::import(QString path)
{
    QDir directory(path);
    QStringList files = directory.entryList(QDir::Files);
    for(QString fileName : files)
    {
        qDebug() << fileName;
        if(fileName.contains(".cpp")||fileName.contains(".h"))
        {
            QFile file(path+"/"+fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"file failed to open";
            }
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();
            // 创建一个QTextEdit作为标签页的内容
            QTextEdit *textEdit = new QTextEdit();
            // 将QTextEdit添加到QTabWidget中
            highlighter = new Highlighter(textEdit->document());
            textEdit->setText(content);
            tabWidget->addTab(textEdit, fileName);
        }
    }
}
