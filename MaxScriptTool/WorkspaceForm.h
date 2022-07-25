#ifndef WORKSPACEFORM_H
#define WORKSPACEFORM_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class WorkspaceForm;
}

class WorkspaceForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkspaceForm(QWidget *parent = nullptr);
    ~WorkspaceForm();

private slots:
    void on_versionCBB_currentIndexChanged(const QString &arg1);

    void on_languageCBB_currentIndexChanged(const QString &arg1);

private:
    // 初始化选择框
    void initSelections();

private:
    Ui::WorkspaceForm *ui;
    QListWidget* mVersionListWidget;
};

#endif // WORKSPACEFORM_H
