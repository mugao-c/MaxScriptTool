#ifndef WORKSPACEFORM_H
#define WORKSPACEFORM_H

#include <QWidget>

namespace Ui {
class WorkspaceForm;
}

class WorkspaceForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkspaceForm(QWidget *parent = nullptr);
    ~WorkspaceForm();

private:
    Ui::WorkspaceForm *ui;
};

#endif // WORKSPACEFORM_H
