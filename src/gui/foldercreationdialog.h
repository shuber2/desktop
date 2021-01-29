#ifndef FOLDERCREATIONDIALOG_H
#define FOLDERCREATIONDIALOG_H

#include <QDialog>

namespace Ui {
class FolderCreationDialog;
}

class FolderCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FolderCreationDialog(QWidget *parent = nullptr);
    ~FolderCreationDialog();

    void setDestination(const QString &destination);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void accept() override;

    void on_newFolderNameEdit_textEdited(const QString &);

private:
    Ui::FolderCreationDialog *ui;

    QString _destination;
};

#endif // FOLDERCREATIONDIALOG_H
