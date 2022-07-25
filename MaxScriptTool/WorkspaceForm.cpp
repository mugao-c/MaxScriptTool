#include "WorkspaceForm.h"
#include "ui_WorkspaceForm.h"
#include "App3dsMaxMgr.h"
#include "LogMacro.h"

DECLARE_LOG_CATEGORY(LogWorkspaceForm)

WorkspaceForm::WorkspaceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkspaceForm)
{
    ui->setupUi(this);
    mVersionListWidget = new QListWidget(ui->versionCBB);
    ui->versionCBB->setView(mVersionListWidget);
    initSelections();
}

WorkspaceForm::~WorkspaceForm()
{
    delete ui;
}

void WorkspaceForm::initSelections()
{
    ui->versionCBB->addItems(G3dsMgr->get3dsVersions());
}

void WorkspaceForm::on_versionCBB_currentIndexChanged(const QString &arg1)
{
    ui->languageCBB->clear();
    auto languages = G3dsMgr->getLanguageDirs(arg1);
    ui->languageCBB->addItem("所有语言版本");
    foreach (auto language, languages) {
        ui->languageCBB->addItem(language.displayName, QVariant::fromValue(language));
    }
    on_languageCBB_currentIndexChanged("");
}

void WorkspaceForm::on_languageCBB_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->workspaceCBB->clear();
    ui->workspaceCBB->addItem("所有工作空间");
    if (ui->languageCBB->currentIndex() > 0) {
        auto workspaces = G3dsMgr->get3dsWorkspaces(
                    ui->versionCBB->currentText(),
                    ui->languageCBB->currentData().value<F3dsSupportLanguage>());
        ui->workspaceCBB->addItems(workspaces);
    }
}
