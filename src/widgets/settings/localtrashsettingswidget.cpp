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

#include "localtrashsettingswidget.h"

#include <services/settingsservice.h>

#include "ui_localtrashsettingswidget.h"

LocalTrashSettingsWidget::LocalTrashSettingsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::LocalTrashSettingsWidget) {
    ui->setupUi(this);
}

LocalTrashSettingsWidget::~LocalTrashSettingsWidget() { delete ui; }

void LocalTrashSettingsWidget::readSettings() {
    SettingsService settings;

    ui->localTrashEnabledCheckBox->setChecked(
        settings.value(QStringLiteral("localTrash/supportEnabled"), true).toBool());
    ui->localTrashClearCheckBox->setChecked(
        settings.value(QStringLiteral("localTrash/autoCleanupEnabled"), true).toBool());
    ui->localTrashClearTimeSpinBox->setValue(
        settings.value(QStringLiteral("localTrash/autoCleanupDays"), 30).toInt());
}

void LocalTrashSettingsWidget::storeSettings() {
    SettingsService settings;

    settings.setValue(QStringLiteral("localTrash/supportEnabled"),
                      ui->localTrashEnabledCheckBox->isChecked());
    settings.setValue(QStringLiteral("localTrash/autoCleanupEnabled"),
                      ui->localTrashClearCheckBox->isChecked());
    settings.setValue(QStringLiteral("localTrash/autoCleanupDays"),
                      ui->localTrashClearTimeSpinBox->value());
}

void LocalTrashSettingsWidget::on_localTrashEnabledCheckBox_toggled(bool checked) {
    ui->localTrashGroupBox->setEnabled(checked);
}

void LocalTrashSettingsWidget::on_localTrashClearCheckBox_toggled(bool checked) {
    ui->localTrashClearFrame->setEnabled(checked);
}
