#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <entities/notefolder.h>
#include <enums/oklabelstatus.h>

#include "masterdialog.h"
#include "widgets/settings/mcpserversettingswidget.h"
#include "widgets/settings/notefoldersettingswidget.h"
#include "widgets/settings/owncloudsettingswidget.h"
#include "widgets/settings/panelssettingswidget.h"
#include "widgets/settings/scriptingsettingswidget.h"

namespace Ui {
class SettingsDialog;
}

class QAbstractButton;
class QListWidgetItem;
class QListWidget;
class QKeySequenceWidget;
class QTreeWidgetItem;
class QTreeWidget;
class QLineEdit;
class QStatusBar;
class QButtonGroup;
class QCheckBox;
class NoteFolder;
class QSplitter;

struct CalDAVCalendarData;

class SettingsDialog : public MasterDialog {
    Q_OBJECT

   public:
    // OKLabelStatus is a global enum defined in enums/oklabelstatus.h
    using OKLabelStatus = ::OKLabelStatus;
    // Expose enum values for backward compatibility (owncloudservice.cpp uses SettingsDialog::OK
    // etc.)
    static constexpr OKLabelStatus Unknown = ::Unknown;
    static constexpr OKLabelStatus Warning = ::Warning;
    static constexpr OKLabelStatus OK = ::OK;
    static constexpr OKLabelStatus Failure = ::Failure;

    enum SettingsPages {
        NoteFolderPage,
        OwnCloudPage,
        NetworkPage,
        TodoPage,
        InterfacePage,
        ShortcutPage,
        ScriptingPage,
        GeneralPage,
        DebugPage,
        EditorFontColorPage,
        PortableModePage,
        PreviewFontPage,
        ToolbarPage,
        DebugOptionPage,
        EditorPage,
        GitPage,
        PanelsPage,
        LocalTrashPage,
        LayoutPresetsPage,
        WebCompanionPage,
        WebApplicationPage,
        ExperimentalPage,
        AiPage,
        LanguageToolPage,
        ColorModesPage,
        McpServerPage
    };

    explicit SettingsDialog(int page = 0, QWidget *parent = 0);

    ~SettingsDialog();

    void connectTestCallback(bool appIsValid, QString appVersion, QString serverVersion,
                             QString notesPathExistsText, QString connectionErrorMessage);

    void setOKLabelData(int number, const QString &text, OKLabelStatus status);

    void refreshTodoCalendarList(const QList<CalDAVCalendarData> &items,
                                 bool forceReadCheckedState = false);

    void setNoteFolderRemotePathList(QStringList pathList);

    void setCurrentPage(int page);

    void readSettings();

   protected:
    void closeEvent(QCloseEvent *event) override;

   private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_reinitializeDatabaseButton_clicked();

    void on_databaseIntegrityCheckButton_clicked();

    void on_clearAppDataAndExitButton_clicked();

    void on_setExternalEditorPathToolButton_clicked();

    void on_addCustomNoteFileExtensionButton_clicked();

    void on_removeCustomNoteFileExtensionButton_clicked();

    void on_defaultNoteFileExtensionListWidget_itemChanged(QListWidgetItem *item);

    void on_shortcutSearchLineEdit_textChanged(const QString &arg1);

    void on_settingsTreeWidget_currentItemChanged(QTreeWidgetItem *current,
                                                  QTreeWidgetItem *previous);

    void on_settingsStackedWidget_currentChanged(int index);

    void on_toolbarIconSizeResetButton_clicked();

    void on_itemHeightResetButton_clicked();

    void on_applyToolbarButton_clicked();

    void on_resetToolbarPushButton_clicked();

    void on_imageScaleDownCheckBox_toggled(bool checked);

    void on_enableReadOnlyModeCheckBox_toggled(bool checked);

    void on_searchLineEdit_textChanged(const QString &arg1);

    void noteNotificationButtonGroupPressed(QAbstractButton *button);

    void noteNotificationNoneCheckBoxCheck();

    void needRestart();

    void on_interfaceStyleComboBox_currentTextChanged(const QString &arg1);

    void on_showSystemTrayCheckBox_toggled(bool checked);

    void on_resetMessageBoxesButton_clicked();

    void onLayoutStored(const QString &layoutUuid);

    void keySequenceEvent(const QString &objectName);

    void on_exportSettingsButton_clicked();

    void on_importSettingsButton_clicked();

    void on_interfaceFontSizeSpinBox_valueChanged(int arg1);

    void on_overrideInterfaceFontSizeGroupBox_toggled(bool arg1);

    void on_languageSearchLineEdit_textChanged(const QString &arg1);

    void on_defaultNoteFileExtensionListWidget_itemSelectionChanged();

    void on_showStatusBarNotePathCheckBox_toggled(bool checked);

    void on_overrideInterfaceScalingFactorGroupBox_toggled(bool arg1);

    void on_interfaceScalingFactorSpinBox_valueChanged(int arg1);

   private:
    Ui::SettingsDialog *ui;
    static const int _defaultMarkdownHighlightingInterval = 200;
    QSplitter *_mainSplitter;
    QButtonGroup *_noteNotificationButtonGroup;
    QCheckBox *_noteNotificationNoneCheckBox;
    QHash<int, bool> _pageInitialized;
    bool _initialDarkMode = false;
    bool _initialDarkModeColors = false;
    bool _initialDarkModeTrayIcon = false;
    bool _initialDarkModeIconTheme = false;
    QString _initialSchemaKey;
    QList<QWidget *> _searchMatchedWidgets;
    QHash<QWidget *, QString> _searchMatchedWidgetOriginalTexts;

    void storeSettings();

    static void selectListWidgetValue(QListWidget *listWidget, const QString &value);

    static bool listWidgetValueExists(QListWidget *listWidget, const QString &value);

    static QString getSelectedListWidgetValue(QListWidget *listWidget);

    QListWidgetItem *addCustomNoteFileExtension(QString fileExtension);

    void loadShortcutSettings();

    void storeShortcutSettings();

    QTreeWidgetItem *findSettingsTreeWidgetItemByPage(int page);

    void initMainSplitter();

    void storeSplitterSettings();

    void initPortableModePage();

    int findSettingsPageIndexOfWidget(QWidget *widget);

    void addToSearchIndexList(QWidget *widget, QList<int> &pageIndexList,
                              const QString &searchText = QString());

    void highlightSearchMatchedWidget(QWidget *widget, const QString &searchText);

    void clearSearchHighlights();

    void replaceOwnCloudText() const;

    void loadInterfaceStyleComboBox() const;

    void initSearchEngineComboBox() const;

    QKeySequenceWidget *findKeySequenceWidget(const QString &objectName);

    void handleDarkModeCheckBoxToggled(bool updateCheckBoxes = false, bool updateSchema = false);

    void updateSearchLineEditIcons();

    bool hasDarkModeSettingChanges() const;

    void applyDarkModeSettings();

    bool initializePage(int index);
};

#endif    // SETTINGSDIALOG_H
