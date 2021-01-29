#include "foldercreationdialog.h"
#include "ui_foldercreationdialog.h"

#include <limits>

#include <QDir>
#include <QMessageBox>

namespace  {
  const QString SuggestedFolderNamePrefix = QObject::tr("New folder");
};

FolderCreationDialog::FolderCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderCreationDialog)
{
    ui->setupUi(this);

    ui->labelErrorMessage->setVisible(false);
}

FolderCreationDialog::~FolderCreationDialog()
{
    delete ui;
}

void FolderCreationDialog::setDestination(const QString& destination)
{
    _destination = destination;
}

void FolderCreationDialog::showEvent(QShowEvent *event)
{
    const auto newFolderFullPath = _destination + "/" + SuggestedFolderNamePrefix;
    if (!QDir(newFolderFullPath).exists()) {
        ui->newFolderNameEdit->setText(SuggestedFolderNamePrefix);
    } else {
        for (unsigned int i = 2; i < std::numeric_limits<unsigned int>::max(); ++i) {
            const QString suggestedPostfix = QString(" (%1)").arg(i);

            if (!QDir(newFolderFullPath + suggestedPostfix).exists()) {
                ui->newFolderNameEdit->setText(SuggestedFolderNamePrefix + suggestedPostfix);
                break;
            }
        }
    }

    ui->newFolderNameEdit->setFocus();
    ui->newFolderNameEdit->selectAll();

    QDialog::showEvent(event);
}

void FolderCreationDialog::accept()
{
    if (QDir(_destination + "/" + ui->newFolderNameEdit->text()).exists()) {
        ui->labelErrorMessage->setVisible(true);
        return;
    }

    if (!QDir(_destination).mkdir(ui->newFolderNameEdit->text())) {
        QMessageBox messageBox;
        messageBox.critical(0, tr("Error"), tr("Could not create a folder!"));
        messageBox.setFixedSize(500,200);
    }

    QDialog::accept();
}

void FolderCreationDialog::on_newFolderNameEdit_textEdited(const QString &)
{
    if (!ui->newFolderNameEdit->text().isEmpty() && QDir(_destination + "/" + ui->newFolderNameEdit->text()).exists()) {
        ui->labelErrorMessage->setVisible(true);
    } else {
        ui->labelErrorMessage->setVisible(false);
    }
}
