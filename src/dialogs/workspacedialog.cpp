/*
 * Copyright (c) 2014-2026 Patrizio Bekerle -- <patrizio@bekerle.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 */

#include "workspacedialog.h"

#include <services/settingsservice.h>
#include <utils/gui.h>
#include <utils/misc.h>

#include <QInputDialog>
#include <QMessageBox>

#include "ui_workspacedialog.h"

WorkspaceDialog::WorkspaceDialog(QWidget *parent)
    : MasterDialog(parent), ui(new Ui::WorkspaceDialog) {
    ui->setupUi(this);
    afterSetupUI();
    reloadWorkspaceList();
}

WorkspaceDialog::~WorkspaceDialog() { delete ui; }

/**
 * Reloads the workspace list widget from settings
 */
void WorkspaceDialog::reloadWorkspaceList() {
    SettingsService settings;
    const QStringList uuids = settings.value(QStringLiteral("workspaces")).toStringList();
    const QString currentUuid = settings.value(QStringLiteral("currentWorkspace")).toString();

    ui->workspaceListWidget->clear();

    for (const QString &uuid : uuids) {
        const QString name =
            settings.value(QStringLiteral("workspace-") + uuid + QStringLiteral("/name"))
                .toString();

        auto *item = new QListWidgetItem(name);
        item->setData(Qt::UserRole, uuid);
        ui->workspaceListWidget->addItem(item);

        if (uuid == currentUuid) {
            ui->workspaceListWidget->setCurrentItem(item);
        }
    }

    updateButtonStates();
}

/**
 * Updates button enabled states based on current selection and list size
 */
void WorkspaceDialog::updateButtonStates() {
    const int count = ui->workspaceListWidget->count();
    const int currentRow = ui->workspaceListWidget->currentRow();
    const bool hasSelection = currentRow >= 0;

    // Cannot remove the last remaining workspace
    ui->removeButton->setEnabled(hasSelection && count > 1);
    ui->renameButton->setEnabled(hasSelection);
    ui->moveUpButton->setEnabled(hasSelection && currentRow > 0);
    ui->moveDownButton->setEnabled(hasSelection && currentRow < count - 1);
}

/**
 * Persists the current order of workspaces in the list widget to settings
 */
void WorkspaceDialog::persistWorkspaceOrder() {
    QStringList uuids;
    uuids.reserve(ui->workspaceListWidget->count());

    for (int i = 0; i < ui->workspaceListWidget->count(); ++i) {
        uuids << ui->workspaceListWidget->item(i)->data(Qt::UserRole).toString();
    }

    SettingsService settings;
    settings.setValue(QStringLiteral("workspaces"), uuids);
}

/**
 * Adds a new workspace
 */
void WorkspaceDialog::on_addButton_clicked() {
    const QString name =
        QInputDialog::getText(this, tr("Add workspace"), tr("Workspace name:")).trimmed();

    if (name.isEmpty()) {
        return;
    }

    SettingsService settings;
    const QString uuid = Utils::Misc::createUuidString();
    QStringList uuids = settings.value(QStringLiteral("workspaces")).toStringList();
    uuids.append(uuid);

    settings.setValue(QStringLiteral("workspaces"), uuids);
    settings.setValue(QStringLiteral("workspace-") + uuid + QStringLiteral("/name"), name);

    reloadWorkspaceList();

    // Select the newly added item
    for (int i = 0; i < ui->workspaceListWidget->count(); ++i) {
        if (ui->workspaceListWidget->item(i)->data(Qt::UserRole).toString() == uuid) {
            ui->workspaceListWidget->setCurrentRow(i);
            break;
        }
    }
}

/**
 * Removes the selected workspace
 */
void WorkspaceDialog::on_removeButton_clicked() {
    QListWidgetItem *item = ui->workspaceListWidget->currentItem();
    if (item == nullptr) {
        return;
    }

    if (ui->workspaceListWidget->count() < 2) {
        return;
    }

    if (Utils::Gui::question(this, tr("Remove workspace"), tr("Remove the selected workspace?"),
                             QStringLiteral("remove-workspace")) != QMessageBox::Yes) {
        return;
    }

    const QString uuid = item->data(Qt::UserRole).toString();
    SettingsService settings;
    QStringList uuids = settings.value(QStringLiteral("workspaces")).toStringList();
    uuids.removeAll(uuid);
    settings.setValue(QStringLiteral("workspaces"), uuids);

    // Remove all settings for this workspace
    settings.beginGroup(QStringLiteral("workspace-") + uuid);
    settings.remove(QLatin1String(""));
    settings.endGroup();

    // Switch away if this was the current workspace
    const QString currentUuid = settings.value(QStringLiteral("currentWorkspace")).toString();
    if (currentUuid == uuid) {
        settings.setValue(QStringLiteral("currentWorkspace"),
                          uuids.isEmpty() ? QString() : uuids.at(0));
    }

    reloadWorkspaceList();
}

/**
 * Renames the selected workspace
 */
void WorkspaceDialog::on_renameButton_clicked() {
    QListWidgetItem *item = ui->workspaceListWidget->currentItem();
    if (item == nullptr) {
        return;
    }

    const QString uuid = item->data(Qt::UserRole).toString();
    SettingsService settings;
    const QString oldName =
        settings.value(QStringLiteral("workspace-") + uuid + QStringLiteral("/name")).toString();

    const QString newName = QInputDialog::getText(this, tr("Rename workspace"),
                                                  tr("Workspace name:"), QLineEdit::Normal, oldName)
                                .trimmed();

    if (newName.isEmpty() || newName == oldName) {
        return;
    }

    settings.setValue(QStringLiteral("workspace-") + uuid + QStringLiteral("/name"), newName);

    item->setText(newName);
    updateButtonStates();
}

/**
 * Moves the selected workspace up in the list
 */
void WorkspaceDialog::on_moveUpButton_clicked() {
    const int row = ui->workspaceListWidget->currentRow();
    if (row <= 0) {
        return;
    }

    QListWidgetItem *item = ui->workspaceListWidget->takeItem(row);
    ui->workspaceListWidget->insertItem(row - 1, item);
    ui->workspaceListWidget->setCurrentRow(row - 1);

    persistWorkspaceOrder();
    updateButtonStates();
}

/**
 * Moves the selected workspace down in the list
 */
void WorkspaceDialog::on_moveDownButton_clicked() {
    const int row = ui->workspaceListWidget->currentRow();
    if (row < 0 || row >= ui->workspaceListWidget->count() - 1) {
        return;
    }

    QListWidgetItem *item = ui->workspaceListWidget->takeItem(row);
    ui->workspaceListWidget->insertItem(row + 1, item);
    ui->workspaceListWidget->setCurrentRow(row + 1);

    persistWorkspaceOrder();
    updateButtonStates();
}

/**
 * Updates button states when the selection changes
 */
void WorkspaceDialog::on_workspaceListWidget_currentRowChanged(int currentRow) {
    Q_UNUSED(currentRow)
    updateButtonStates();
}

/**
 * Opens the rename dialog on double click
 */
void WorkspaceDialog::on_workspaceListWidget_itemDoubleClicked() { on_renameButton_clicked(); }
