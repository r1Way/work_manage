#include "FileWindow.h"

FileWindow::FileWindow()
{
    QFont font;
    font.setPointSize(14);

    //left layout
    returnBtn=new QPushButton("返回");
    returnBtn->setFont(font);
    this->leftSplitter->addWidget(returnBtn);
    // this->leftLayout->addWidget(returnBtn);

    //right layout
    tabWidget=new QTabWidget;
    tabWidget->setStyleSheet("QTabBar::tab { font-size: 13pt; }");
    rightLayout->addWidget(tabWidget);

}

bool FileWindow::import(QString path)
{
    QDir directory(path);

    //检测文件夹是否存在
    if(!directory.exists())
    {
        directory.mkpath(path);
    }


    //初始化 清空每个标签页
    if(tabWidget!=nullptr)
    {

        while (tabWidget->count()>0)
        {
            tabWidget->removeTab(0);
        }
    }

    QStringList files = directory.entryList(QDir::Files);

    if(files.size()!=0)
    {
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
                // // 创建一个QTextEdit作为标签页的内容
                CodeEditor *codeEdit=new CodeEditor();
                // // 将QTextEdit添加到QTabWidget中
                highlighter=new Highlighter(codeEdit->document());
                codeEdit->setPlainText(content);
                tabWidget->addTab(codeEdit,fileName);
                connect(codeEdit,&CodeEditor::deliver,this,&FileWindow::wheelAll);
            }
        }
    }
}

void FileWindow::wheelAll(QWheelEvent *e,CodeEditor *codeEdit)
{
    for (int i = 0; i < this->tabWidget->count(); ++i)
    {
        QWidget *widget = tabWidget->widget(i);
        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit*>(widget);
        if (e->angleDelta().y()>  0)
        { // If wheel scrolled up
            QFont f = textEdit->font();
            f.setPointSize(f.pointSize() + 1); // Increase font size
            textEdit->setFont(f);
        }
        else if (e->angleDelta().y() < 0)
        { // If wheel scrolled down
            QFont f = textEdit->font();
            f.setPointSize(f.pointSize() - 1); // Decrease font size
            textEdit->setFont(f);
        }
    }
}
