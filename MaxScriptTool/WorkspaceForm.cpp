#include "WorkspaceForm.h"
#include "ui_WorkspaceForm.h"
#include "App3dsMaxMgr.h"
#include <QDebug>

WorkspaceForm::WorkspaceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkspaceForm)
{
    ui->setupUi(this);
    ui->versionCBB->addItems(G3dsMgr->get3dsVersions());
}

WorkspaceForm::~WorkspaceForm()
{
    delete ui;
}
