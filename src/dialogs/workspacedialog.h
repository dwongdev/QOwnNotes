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

#pragma once

#include "masterdialog.h"

namespace Ui {
class WorkspaceDialog;
}

class WorkspaceDialog : public MasterDialog {
    Q_OBJECT

   public:
    explicit WorkspaceDialog(QWidget *parent = nullptr);
    ~WorkspaceDialog();

   private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_renameButton_clicked();
    void on_moveUpButton_clicked();
    void on_moveDownButton_clicked();
    void on_workspaceListWidget_currentRowChanged(int currentRow);
    void on_workspaceListWidget_itemDoubleClicked();

   private:
    Ui::WorkspaceDialog *ui;

    void reloadWorkspaceList();
    void updateButtonStates();
    void persistWorkspaceOrder();
};
