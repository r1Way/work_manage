# C++作业管理系统

题目：C++作业管理系统

 

## [系统要求]

该系统需创建和管理以下信息：

 1. 作业信息：

  \- 作业编号、作业标题、作业描述、截止日期、标准答案、分值等。

  \- 作业提交状态（未提交、已提交、已评分）。

 2. 学生信息：

  \- 学生姓名、学号、班级、提交的作业文件、提交时间、得分、评语等。

 3. 教师信息：

  \- 教师姓名、工号、负责的课程和作业、评分信息等。

 

## [系统功能要求]

 1. 创建和管理描述作业信息的对象：

  \- 教师可以创建、修改和删除作业信息，包括设置作业的截止日期等。

  \- 教师可以添加详细的作业描述。

 2. 创建和管理描述学生信息的对象：

  \- 管理学生的基本信息，包括学号、姓名、班级等。

  \- 系统记录学生每次提交的作业文件、时间、得分等信息。

 3. 作业提交管理：

  \- 学生可以查看已发布的作业并在线提交作业文件。

  \- 系统记录提交时间并提供反馈，确保作业在截止日期前提交。

  \- 支持多次提交作业，教师可以查看所有提交记录。

 4. 评分与反馈：

  \- 教师可以查看学生提交的作业，手动调整分数并添加评语。

 5. 作业状态管理与变更：

  \- 支持作业信息的变更，如修改作业描述、调整截止日期等。

  \- 学生提交作业后，系统自动更新提交状态。

 6. 基本查询功能：

  \- 查询所有作业及其状态。

  \- 查询特定作业的学生提交情况、代码运行结果和得分。

  \- 查询学生个人的作业提交历史和成绩。

 7. 基本信息显示：

  \- 显示所有已发布的作业及其基本信息。

  \- 显示特定作业的所有学生提交的作业情况及得分。

 

## [可选功能提升]

1. 提供在线测试环境，学生可以在正式提交前测试代码，查看其是否通过系统预设的测试用例。

2. 系统为每个作业提供讨论区，学生和教师可以在此交流作业相关问题。

3. 根据学生作业成绩，系统自动生成积分与排名。

4. 系统支持将作业信息、学生提交记录等导出到文件中。

5. 根据学生提交代码生成对应的文件依赖关系，关系依赖关系图谱。

6. 提供助教端，可以协助教师批改作业。

## Trouble Shooting

### 记得空格

```c++
    QString sql=QString("SELECT homework_class.name,homework_class.description,"
                          "homework_class.d,homework_class.t "
                          "WHERE class_id=%1;").arg(classId);
```



## 数据库模版

###  管理端

#### 密码

pass

|身份 |账号| 密码|
|--|---|----|
| user| id|password|



### 基本信息

student

| 学号 | 姓名 | 专业|
| --- | ---- |-|
| student_id | name|major|

teacher

|工号| 姓名|专业|
|-|-|-|
| teacher_id | name | major|

class
|课程号 |课程名| 课程描述|
| -| -| :--|
| class_id | name | description |

#### 课程管理

class_teacher

| 班号 |教师 |
|-|-|
| class_id | teacher_id |

#### 学生管理

class_student

|班号 |学号|
|-|-|
|class_id|student_id|

### 教师端

#### 作业管理

homework_class

|班号 |作业名称 |作业介绍 | DATE | TIME|
|-|-|-|-|-|
| class_id | name |description |d |t|
### 学生端

homework_student

|学号 |班级代号 |作业名称| 分数 |DATA | TIME |
|-|-|-|-|-|-|
|student_id |class_id|name|score| d|t|

### 文件存储

PATH / 班号 / 作业名称 / 学号

## 路径管理

* PATH
  * class_id1
    * homework1
      * student_id1
      * student_id2
    * homework2
  * class_id2

## 想法

* 用作用域来确定颜色
* 通过图谱定位代码位置

### 登录效果

> [Qt实现登录效果（超详细！超简单！）_qt登录界面输入密码登录-CSDN博客](https://blog.csdn.net/qq_45677405/article/details/126323748)

### 密码输入框

> [Qt实现密码输入框-隐藏或显示密码功能_qt密码输入框-CSDN博客](https://blog.csdn.net/u012959478/article/details/140342146?ops_request_misc=%7B%22request%5Fid%22%3A%22172406283016800211530366%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=172406283016800211530366&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduend~default-1-140342146-null-null.nonecase&utm_term=qt密码输入框&spm=1018.2226.3001.4450)

### 信号与槽

> [qt中的信号和槽会打断正在执行的函数吗 - 数据处理 - Qt开源社区 - qt qml linux 嵌入式 教程! (qter.org)](https://www.qter.org/forum.php?mod=viewthread&tid=3414)

### 搜索

```c++
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class StudentWidget : public QWidget {
    Q_OBJECT

public:
    StudentWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 创建表格控件
        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(3);  // 设置列数为3
        tableWidget->setHorizontalHeaderLabels({"姓名", "学号", "专业"});

        // 启用表头的排序功能
        tableWidget->setSortingEnabled(true);

        // 添加一些示例数据
        addStudent("张三", "2021001", "计算机科学");
        addStudent("李四", "2021002", "软件工程");
        addStudent("王五", "2021003", "信息安全");

        // 创建搜索框和按钮
        QLineEdit *searchBox = new QLineEdit(this);
        searchBox->setPlaceholderText("输入姓名、学号或专业进行搜索...");
        QPushButton *searchButton = new QPushButton("搜索", this);

        // 创建布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(searchBox);
        layout->addWidget(searchButton);
        layout->addWidget(tableWidget);
        setLayout(layout);

        // 连接搜索按钮点击信号到槽函数
        connect(searchButton, &QPushButton::clicked, [this]() {
            searchStudents(searchBox->text());
        });
    }

private:
    QTableWidget *tableWidget;

    void addStudent(const QString &name, const QString &id, const QString &major) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        tableWidget->setItem(row, 1, new QTableWidgetItem(id));
        tableWidget->setItem(row, 2, new QTableWidgetItem(major));
    }

    void searchStudents(const QString &keyword) {
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            bool match = false;
            for (int j = 0; j < tableWidget->columnCount(); ++j) {
                QTableWidgetItem *item = tableWidget->item(i, j);
                if (item->text().contains(keyword, Qt::CaseInsensitive)) {
                    match = true;
                    break;
                }
            }
            tableWidget->setRowHidden(i, !match);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StudentWidget studentWidget;
    studentWidget.setWindowTitle("学生信息管理");
    studentWidget.resize(600, 400);
    studentWidget.show();

    return app.exec();
}

#include "main.moc"
```



### 搜索时将对应字体标红

### 详细

```c++
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

// 初始化表格并添加数据
void setupTableWidget(QTableWidget *tableWidget) {
    tableWidget->setColumnCount(4);  // 比如3列数据列 + 1列按钮列
    tableWidget->setRowCount(10);    // 假设有10个学生

    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        // 添加学生信息到前3列
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString("学生 %1").arg(i + 1)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString("学号 %1").arg(1000 + i)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString("专业 %1").arg(i + 1)));

        // 在最后一列添加“详细”按钮
        QPushButton *detailsButton = new QPushButton("详细");
        tableWidget->setCellWidget(i, 3, detailsButton);

        // 连接按钮点击事件到槽函数
        QObject::connect(detailsButton, &QPushButton::clicked, [tableWidget, i]() {
            showDetails(tableWidget, i);
        });
    }
}

// 显示学生详细信息的对话框
void showDetails(QTableWidget *tableWidget, int row) {
    // 获取该行的学生信息
    QString name = tableWidget->item(row, 0)->text();
    QString studentID = tableWidget->item(row, 1)->text();
    QString major = tableWidget->item(row, 2)->text();

    // 创建并配置对话框
    QDialog detailsDialog;
    detailsDialog.setWindowTitle("学生详细信息");

    QVBoxLayout *layout = new QVBoxLayout(&detailsDialog);
    layout->addWidget(new QLabel("姓名: " + name));
    layout->addWidget(new QLabel("学号: " + studentID));
    layout->addWidget(new QLabel("专业: " + major));

    // 这里可以添加更多的详细信息，例如联系方式、课程信息等
    layout->addWidget(new QLabel("更多信息..."));

    QPushButton *closeButton = new QPushButton("关闭");
    layout->addWidget(closeButton);

    QObject::connect(closeButton, &QPushButton::clicked, &detailsDialog, &QDialog::accept);

    // 显示对话框
    detailsDialog.exec();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTableWidget tableWidget;
    setupTableWidget(&tableWidget);

    tableWidget.show();

    return app.exec();
}
```

### 批量删除

```c++
#include <QApplication>
#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMessageBox>

void setupTableWidget(QTableWidget *tableWidget) {
    tableWidget->setColumnCount(5);  // 4列数据 + 1列复选框
    tableWidget->setRowCount(10);    // 假设有10个学生

    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        // 在第一列添加复选框
        QCheckBox *checkBox = new QCheckBox();
        tableWidget->setCellWidget(i, 0, checkBox);

        // 添加学生信息到后4列
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString("学生 %1").arg(i + 1)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString("学号 %1").arg(1000 + i)));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString("专业 %1").arg(i + 1)));

        // 在最后一列添加“详细”按钮
        QPushButton *detailsButton = new QPushButton("详细");
        tableWidget->setCellWidget(i, 4, detailsButton);

        QObject::connect(detailsButton, &QPushButton::clicked, [tableWidget, i]() {
            showDetails(tableWidget, i);
        });
    }
}

void showDetails(QTableWidget *tableWidget, int row) {
    QString name = tableWidget->item(row, 1)->text();
    QString studentID = tableWidget->item(row, 2)->text();
    QString major = tableWidget->item(row, 3)->text();

    QDialog detailsDialog;
    detailsDialog.setWindowTitle("学生详细信息");

    QVBoxLayout *layout = new QVBoxLayout(&detailsDialog);
    layout->addWidget(new QLabel("姓名: " + name));
    layout->addWidget(new QLabel("学号: " + studentID));
    layout->addWidget(new QLabel("专业: " + major));

    QPushButton *closeButton = new QPushButton("关闭");
    layout->addWidget(closeButton);

    QObject::connect(closeButton, &QPushButton::clicked, &detailsDialog, &QDialog::accept);

    detailsDialog.exec();
}

void deleteSelectedRows(QTableWidget *tableWidget) {
    for (int i = tableWidget->rowCount() - 1; i >= 0; --i) { 
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(tableWidget->cellWidget(i, 0));
        if (checkBox && checkBox->isChecked()) {
            tableWidget->removeRow(i);
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout(&window);

    QTableWidget tableWidget;
    setupTableWidget(&tableWidget);

    layout.addWidget(&tableWidget);

    // 添加“删除选中”按钮
    QPushButton deleteButton("删除选中");
    layout.addWidget(&deleteButton);

    // 连接“删除选中”按钮到删除槽函数
    QObject::connect(&deleteButton, &QPushButton::clicked, [&tableWidget]() {
        deleteSelectedRows(&tableWidget);
    });

    window.show();

    return app.exec();
}
```

- **`tableWidget->cellWidget(i, 0)`**：获取第 `i` 行第 `0` 列（第一列）的单元格中的小部件（一般是 `QWidget` 类型）。
- **`qobject_cast<QCheckBox\*>`**：将该小部件强制转换为 `QCheckBox*` 类型。`qobject_cast` 是一种类型安全的转换方式，用于在运行时进行对象的类型检查。如果转换成功，`checkBox` 将是指向 `QCheckBox` 对象的指针；如果失败，则返回 `nullptr`。

### 滚轮条

```c++
#include <QApplication>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout(&window);

    // 创建 QTableWidget 并设置行列数
    QTableWidget *tableWidget = new QTableWidget(20, 3); // 例如，20行3列

    // 添加一些示例数据
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 3; ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(QString("Item %1,%2").arg(i).arg(j)));
        }
    }

    // 创建 QScrollArea 并将 QTableWidget 放入其中
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true); // 让 QTableWidget 随着 QScrollArea 的大小变化

    // 将 QScrollArea 添加到布局中
    layout.addWidget(scrollArea);

    window.show();

    return app.exec();
}
```

> [QT的自动滚动区QScrollArea的用法，图文详解-CSDN博客](https://blog.csdn.net/liji_digital/article/details/87071543)
>
> [2.3Qtabwidget和Qlistwidget和Qscrollarea - NoAcalculia - 博客园 (cnblogs.com)](https://www.cnblogs.com/yjydxuexi/p/17873282.html)

### 按钮间距

* 法一

```c++
// 设置 rightLayOut 中控件之间的间距为 20 像素
rightLayOut->setSpacing(20);
```

* 法二

```c++
// 在学生管理和教师管理按钮之间添加 15 像素的间距
leftLayOut->addWidget(studentButton);
leftLayOut->addSpacing(15); // 这里设置间距
leftLayOut->addWidget(teacherButton);
leftLayOut->addSpacing(15); // 这里设置间距
leftLayOut->addWidget(classButton);
```

* 法三

```c++
// 在 addStudent 和 deleteStudent 按钮之间添加一个弹性空间
searchLayOut->addWidget(addStudent);
searchLayOut->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
searchLayOut->addWidget(deleteStudent);
```

- **`setSpacing()`**: 适用于整体设置布局中所有控件之间的间距。
- **`addSpacing()`**: 用于手动控制特定两个控件之间的固定间距。
- **`QSpacerItem`**: 用于添加可伸缩的空间，常用于灵活布局。
- **`setContentsMargins()`**: 用于设置布局的整体边距。

> http://t.csdnimg.cn/Lfvpv QSpacerItem用法说明

### 表 table

```c++
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class StudentWidget : public QWidget {
    Q_OBJECT

public:
    StudentWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 创建表格控件
        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(3);  // 设置列数为3
        tableWidget->setHorizontalHeaderLabels({"姓名", "学号", "专业"});

        // 启用表头的排序功能
        tableWidget->setSortingEnabled(true);

        // 添加一些示例数据
        addStudent("张三", "2021001", "计算机科学");
        addStudent("李四", "2021002", "软件工程");
        addStudent("王五", "2021003", "信息安全");

        // 创建搜索框和按钮
        QLineEdit *searchBox = new QLineEdit(this);
        searchBox->setPlaceholderText("输入姓名、学号或专业进行搜索...");
        QPushButton *searchButton = new QPushButton("搜索", this);

        // 创建布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(searchBox);
        layout->addWidget(searchButton);
        layout->addWidget(tableWidget);
        setLayout(layout);

        // 连接搜索按钮点击信号到槽函数
        connect(searchButton, &QPushButton::clicked, [this, searchBox]() {
            searchStudents(searchBox->text());
        });
    }

private:
    QTableWidget *tableWidget;

    void addStudent(const QString &name, const QString &id, const QString &major) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        tableWidget->setItem(row, 1, new QTableWidgetItem(id));
        tableWidget->setItem(row, 2, new QTableWidgetItem(major));
    }

    void searchStudents(const QString &keyword) {
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            bool match = false;
            for (int j = 0; j < tableWidget->columnCount(); ++j) {
                QTableWidgetItem *item = tableWidget->item(i, j);
                if (item->text().contains(keyword, Qt::CaseInsensitive)) {
                    match = true;
                    break;
                }
            }
            tableWidget->setRowHidden(i, !match);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StudentWidget studentWidget;
    studentWidget.setWindowTitle("学生信息管理");
    studentWidget.resize(600, 400);
    studentWidget.show();

    return app.exec();
}

#include "main.moc"
```

### 全屏

```c++
AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //全屏
    this->showMaximized();
    this->setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
	//······
}
```

> http://t.csdnimg.cn/2LYEq

### 部件替换

> http://t.csdnimg.cn/eqBLD

### 插入按钮

```c++
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QSpacerItem>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QHBoxLayout *layout = new QHBoxLayout(&window);

    // 创建三个按钮作为示例
    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");
    QPushButton *button3 = new QPushButton("Button 3");

    // 将按钮添加到布局中
    layout->addWidget(button1);
    layout->addWidget(button2);

    // 添加 QSpacerItem 替代 addStretch
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);

    layout->addWidget(button3);

    // 在Button2后面插入新按钮
    QPushButton *newButton = new QPushButton("New Button");
    layout->insertWidget(2, newButton);

    // spacer仍然有效，将Button3推到最右边
    window.show();

    return app.exec();
}
```

### 删除组件

```c++
widget->setParent(nullptr);    //记得移除前将widget的parent置空，不然删不掉
Layout->removeWidget(widget);
delete widget;                //移除并释放
```



> [QLayout增加控件、删除控件_layout->removewidget(-CSDN博客](https://blog.csdn.net/Carry_Qt/article/details/120040665)

### 切换界面

```c++
#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QStackedWidget *stackedWidget = new QStackedWidget(this);

        // 创建第一个页面
        QWidget *page1 = new QWidget();
        QVBoxLayout *layout1 = new QVBoxLayout(page1);
        QPushButton *button1 = new QPushButton("Go to Page 2", page1);
        layout1->addWidget(button1);

        // 创建第二个页面
        QWidget *page2 = new QWidget();
        QVBoxLayout *layout2 = new QVBoxLayout(page2);
        QPushButton *button2 = new QPushButton("Go to Page 1", page2);
        layout2->addWidget(button2);

        // 将页面添加到QStackedWidget中
        stackedWidget->addWidget(page1); // index 0
        stackedWidget->addWidget(page2); // index 1

        setCentralWidget(stackedWidget);

        // 连接按钮的点击信号到切换页面的槽
        connect(button1, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentIndex(1); // 切换到第2页
        });

        connect(button2, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentIndex(0); // 切换到第1页
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
```

### 右键上下文菜单

```c++
#include <QApplication>
#include <QTableWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QMessageBox>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        tableWidget = new QTableWidget(5, 3, this); // 创建一个5行3列的表格

        // 填充一些示例数据
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 3; ++col) {
                tableWidget->setItem(row, col, new QTableWidgetItem(QString("Item %1").arg(row * 3 + col + 1)));
            }
        }

        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

        layout->addWidget(tableWidget);
        setLayout(layout);
    }

private slots:
    void showContextMenu(const QPoint &pos) {
        // 获取点击的行
        QModelIndex index = tableWidget->indexAt(pos);
        if (!index.isValid()) {
            return;
        }
        int row = index.row();

        // 创建上下文菜单
        QMenu contextMenu(this);
        QAction *deleteAction = contextMenu.addAction("Delete Row");

        // 显示菜单并捕获用户选择
        QAction *selectedAction = contextMenu.exec(tableWidget->viewport()->mapToGlobal(pos));
        if (selectedAction == deleteAction) {
            tableWidget->removeRow(row);  // 删除第i行
        }
    }

private:
    QTableWidget *tableWidget;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

#include "main.moc"
```

1. **设置上下文菜单策略**：

   ```cpp
   tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
   ```

   这一步设置了 `QTableWidget` 以接受自定义的上下文菜单。

2. **连接 `customContextMenuRequested` 信号**：

   ```cpp
   connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
   ```

   将 `customContextMenuRequested` 信号连接到槽函数 `showContextMenu`，在右键点击时触发。

3. **显示上下文菜单并删除行**：

   ```cpp
   void showContextMenu(const QPoint &pos) {
       QModelIndex index = tableWidget->indexAt(pos);
       if (!index.isValid()) {
           return;
       }
       int row = index.row();
   
       QMenu contextMenu(this);
       QAction *deleteAction = contextMenu.addAction("Delete Row");
   
       QAction *selectedAction = contextMenu.exec(tableWidget->viewport()->mapToGlobal(pos));
       if (selectedAction == deleteAction) {
           tableWidget->removeRow(row);
       }
   }
   ```

- `indexAt(pos)` 获取鼠标点击位置的行号，如果点击的不是有效单元格，函数将返回。
- 创建上下文菜单并添加“删除行”操作（`deleteAction`）。
- 使用 `exec()` 方法显示菜单，并返回用户选择的操作。
- 如果选择了“删除行”操作，使用 `removeRow(row)` 删除点击的行。

### 数据库->QTableWidget

> [将数据库表中信息显示在Qtablewidget - CSDN文库](https://wenku.csdn.net/answer/35a91d0240f04c97a8aa1abf061976eb#:~:text=要将数据库表中的,Widget中。)

### mouseEvent

> http://t.csdnimg.cn/8FnGi

### View可拖动

```c++
    view.setDragMode(QGraphicsView::ScrollHandDrag);
```

### View滚轮放大缩小

```c++
class ZoomableGraphicsView : public QGraphicsView
{
public:
    ZoomableGraphicsView(QGraphicsScene* scene) : QGraphicsView(scene) {}

protected:
    void wheelEvent(QWheelEvent* event) override
    {
        // 基于滚轮事件的 delta 值来设置缩放因子
        double scaleFactor = 1.15;
        if(event->angleDelta().y() > 0) {
            // 滚轮向前，放大
            this->scale(scaleFactor, scaleFactor);
        } else {
            // 滚轮向后，缩小
            this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
};
```

### QGraphicsItem 鼠标点击

```c++
#ifndef CLICKABLERECTITEM_H
#define CLICKABLERECTITEM_H
#include<QObject>
#include <QGraphicsRectItem>

class ClickableRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ClickableRectItem(qreal x, qreal y, qreal w, qreal h)
        : QGraphicsRectItem(x, y, w, h) {}

signals:
    void rectClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        emit rectClicked();
        QGraphicsRectItem::mousePressEvent(event);
    }
};


#endif // CLICKABLERECTITEM_H

```

### 直线相交

```c++
QLineF::BoundedIntersection
```

### 布局管理

* QWidget
  * `layout()`Returns the layout manager that is installed on this widget, or nullptr if no layout manager is installed.
  * `setLayout(QLayout *layout)`Sets the layout manager for this widget to layout.

* `QLayout`,`QHBoxLayout`,`QVBoxLayout`
  * `addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())`（该方法继承自父类）
  * `addLayout(QLayout *layout, int stretch = 0)`（该方法继承自父类）

### 标签页

```c++
#include <QApplication>
#include <QTabWidget>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建一个QTabWidget
    QTabWidget *tabWidget = new QTabWidget();

    // 创建一些标签页
    for(int i = 0; i < 3; i++) 
    {
        // 创建一个QTextEdit作为标签页的内容
        QTextEdit *textEdit = new QTextEdit();

        // 将QTextEdit添加到QTabWidget中
        tabWidget->addTab(textEdit, QString("Tab %1").arg(i + 1));
    }

    tabWidget->show();

    return a.exec();
}
```

### 获取路径下所有文件名

```c++
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir directory("/path/to/your/directory");
    QStringList files = directory.entryList(QDir::Files);

    for(auto fileName : files) {
        qDebug() << fileName;
    }

    return a.exec();
}
```

### 文件读写

```c++
#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("/path/to/your/file.cpp");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QTextEdit textEdit;
    textEdit.setText(content);
    textEdit.show();

    return a.exec();
}
```

### 数据库

QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed.

> http://t.csdnimg.cn/8D7DX

### 表格宽度

```c++
// //调整列宽以适应内容字的宽度
// tableWindow2->tableWidget->resizeColumnsToContents();
```

```c++
//设置列的大小调整模式以填充表格的宽度
tableWindow2->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
```

### 获取QTableWIdget中的某一项

item(int row,int col) 

itemAt(int ax,int ay)获取像素处

itemAt(QPoint *)获取鼠标处

### 获取文件路径

```c++
QStringList fileNames = QFileDialog::getOpenFileNames(
    this, 
    "Open Files", 
    "/home",
    "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"
);
```

### 文件复制

```c++
QString sourceFileName = "/path/to/source/file";
QString destFileName = "/path/to/destination/file";

if (QFile::exists(destFileName)) {
    // 如果目标文件已经存在，删除它
    QFile::remove(destFileName);
}

QFile::copy(sourceFileName, destFileName);
```

> 注意sourceFileName，destFileName都是文件名，不是路径名。

### 创建文件夹

```c++
#include <QDebug>
#include <QString>
#include <QDir>
 
 
QString folder_name("Images");    //要创建的文件夹名称
 
QDir dir(QDir::currentPath());    //初始化dir为当前目录
 
//假设当前目录下有一个test文件夹
 
dir.cd("./test");    //目录切换到test文件夹下
 
if(!dir.exists(folder_name))    //如果Images文件夹不存在
{
    dir.mkdir(folder_name);    //创建文件夹（名为Images）
 
    qDebug()<<QString("文件夹%1创建成功！").arg(folder_name);
}
else
{
    qDebug()<<QString("文件夹%1已存在！").arg(folder_name);
}
 
 
//这样就可以在当前目录下的test文件夹中创建一个Images文件夹
```

### QDate QTime

```c++
QDate date = dateEdit->date();
QTime time = timeEdit->time();

QString dateString = date.toString("yyyy-MM-dd");
QString timeString = time.toString("HH:mm:ss");
```

mysql

```mysql
INSERT INTO events (event_date, event_time) VALUES ('2024-08-29', '11:03:02');
```

### 删除table所有行

```c++
// 假设你的 QTableWidget 对象名为 tableWidget
tableWidget->setRowCount(0);
```

### Qprocess 操作文件读写

```c++
#include <QCoreApplication>  
#include <QProcess>  
#include <QDebug>  
#include <QTextStream>  

int main(int argc, char *argv[]) {  
    QCoreApplication a(argc, argv);  

    // 创建 QProcess 对象  
    QProcess process;  
    QString program = "path/to/your/my_program.exe"; // 替换为你的可执行文件路径  

    // 启动外部程序  
    process.start(program);  

    // 等待程序启动  
    if (!process.waitForStarted()) {  
        qDebug() << "Failed to start the process:" << process.errorString();  
        return 1;  
    }  

    // 输入参数 n  
    QTextStream in(stdin);  
    int n;  
    qDebug() << "Please enter n:";  
    in >> n; // 从标准输入读取 n  

    // 将 n 发送到外部程序  
    process.write(QString::number(n).toUtf8() + "\n");  
    process.closeWriteChannel(); // 关闭写通道，表示输入结束  

    // 等待程序执行完成  
    if (!process.waitForFinished()) {  
        qDebug() << "Execution failed:" << process.errorString();  
        return 1;  
    }  

    // 读取标准输出和错误输出  
    QByteArray output = process.readAllStandardOutput();  
    QByteArray errorOutput = process.readAllStandardError();  

    // 输出结果  
    qDebug() << "Output:" << output;  
    if (!errorOutput.isEmpty()) {  
        qDebug() << "Error Output:" << errorOutput;  
    }  

    return 0;  
}
```

### 允许table排序功能

```c++
setSortingEnabled(true);
```

### Table不允许编辑

```c++
tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers)
```

### 设置QLabel内部内容

```c++
searchEdit->setPlaceholderText("输入姓名、学号或专业进行搜索...");
```

### QTextEdit只读

```c++
    //只读
    this->setReadOnly(true);
```

### 只允许读整型数字

```c++
        edit->setValidator(new QIntValidator(edit));
```

### 获取当前时间

```c++
QDate::currentDate()
QTime::currentTime()
```

### message box

```c++
// 创建一个 QMessageBox 对象
QMessageBox messageBox;
// 设置消息框的标题
messageBox.setWindowTitle("输入验证");
// 设置消息框显示的文本
messageBox.setText("输入为空，请重新输入。");
// 设置消息框的图标类型
messageBox.setIcon(QMessageBox::Warning);
// 设置消息框的标准按钮
messageBox.setStandardButtons(QMessageBox::Ok);
// 显示消息框
messageBox.exec();
```

```c++
QMessageBox messageBox;
messageBox.setWindowIcon(QIcon("://img/icopng"));
messageBox.setWindowTitle("输入验证");
messageBox.setText("不存在该教师，删除失败,请重新输入。");
messageBox.setIcon(QMessageBox::Warning);
messageBox.setStandardButtons(QMessageBox::Ok);
messageBox.exec();
```



### 设置图标

```c++
->setWindowIcon(QIcon("://img/icopng"));
```

### 确认删除

```c++
#include <QMessageBox>
#include <QPushButton>

//...

// 创建一个 QMessageBox 对象
QMessageBox msgBox;
msgBox.setWindowTitle("删除确认");
msgBox.setText("你确定要删除这个文件吗？");

// 创建两个 QPushButton 对象，作为自定义的按钮
QPushButton *confirmButton = msgBox.addButton("确认", QMessageBox::YesRole);
QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::NoRole);

// 显示对话框，并等待用户点击一个按钮
msgBox.exec();

// 判断用户点击了哪个按钮
if (msgBox.clickedButton() == confirmButton) {
    // 用户点击了 "确认" 按钮
    // 在这里执行删除操作
} else if (msgBox.clickedButton() == cancelButton) {
    // 用户点击了 "取消" 按钮
    // 在这里执行取消操作
}
```

