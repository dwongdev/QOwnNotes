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

#include "markdownlspsettingswidget.h"

#include <QRegularExpression>

#include "services/settingsservice.h"
#include "ui_markdownlspsettingswidget.h"

MarkdownLspSettingsWidget::MarkdownLspSettingsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MarkdownLspSettingsWidget) {
    ui->setupUi(this);
}

MarkdownLspSettingsWidget::~MarkdownLspSettingsWidget() { delete ui; }

void MarkdownLspSettingsWidget::initialize() {}

void MarkdownLspSettingsWidget::readSettings() {
    SettingsService settings;

    ui->markdownLspEnabledCheckBox->setChecked(
        settings.value(QStringLiteral("Editor/markdownLspEnabled"), false).toBool());
    ui->markdownLspCommandLineEdit->setText(
        settings.value(QStringLiteral("Editor/markdownLspCommand"), QStringLiteral("marksman"))
            .toString());
    ui->markdownLspArgumentsLineEdit->setText(
        settings.value(QStringLiteral("Editor/markdownLspArguments"))
            .toStringList()
            .join(QLatin1Char(' ')));
    ui->markdownLspVerboseLoggingCheckBox->setChecked(
        settings.value(QStringLiteral("Editor/markdownLspVerboseLogging"), false).toBool());

    on_markdownLspEnabledCheckBox_toggled(ui->markdownLspEnabledCheckBox->isChecked());
}

void MarkdownLspSettingsWidget::storeSettings() {
    SettingsService settings;

    settings.setValue(QStringLiteral("Editor/markdownLspEnabled"),
                      ui->markdownLspEnabledCheckBox->isChecked());
    settings.setValue(QStringLiteral("Editor/markdownLspCommand"),
                      ui->markdownLspCommandLineEdit->text().trimmed());
    settings.setValue(QStringLiteral("Editor/markdownLspArguments"),
                      ui->markdownLspArgumentsLineEdit->text().split(
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
                          QRegularExpression(QStringLiteral("\\s+")), QString::SkipEmptyParts));
#else
                          QRegularExpression(QStringLiteral("\\s+")), Qt::SkipEmptyParts));
#endif
    settings.setValue(QStringLiteral("Editor/markdownLspVerboseLogging"),
                      ui->markdownLspVerboseLoggingCheckBox->isChecked());
}

void MarkdownLspSettingsWidget::on_markdownLspEnabledCheckBox_toggled(bool checked) {
    ui->markdownLspCommandLineEdit->setEnabled(checked);
    ui->markdownLspArgumentsLineEdit->setEnabled(checked);
    ui->markdownLspCommandLabel->setEnabled(checked);
    ui->markdownLspArgumentsLabel->setEnabled(checked);
    ui->markdownLspVerboseLoggingCheckBox->setEnabled(checked);
}
