#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <entities/cloudconnection.h>
#include <entities/notefolder.h>
#include <entities/script.h>

#include "masterdialog.h"

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
class Script;
class QCheckBox;
class NoteFolder;
class QSplitter;
class CloudConnection;

struct CalDAVCalendarData;

class SettingsDialog : public MasterDialog {
    Q_OBJECT

   public:
    enum OKLabelStatus {
        Unknown,
        Warning,
        OK,
        Failure,
    };

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

    void on_connectButton_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_ownCloudServerAppPageButton_clicked();

    void on_reinitializeDatabaseButton_clicked();

    void on_clearAppDataAndExitButton_clicked();

    void on_setExternalEditorPathToolButton_clicked();

    void on_noteFolderListWidget_currentItemChanged(QListWidgetItem *current,
                                                    QListWidgetItem *previous);

    void on_noteFolderAddButton_clicked();

    void on_noteFolderRemoveButton_clicked();

    void on_noteFolderNameLineEdit_editingFinished();

    void on_noteFolderRemotePathLineEdit_editingFinished();

    void on_noteFolderLocalPathButton_clicked();

    void on_noteFolderActiveCheckBox_stateChanged(int arg1);

    void on_noteFolderRemotePathButton_clicked();

    void on_noteFolderRemotePathTreeWidget_currentItemChanged(QTreeWidgetItem *current,
                                                              QTreeWidgetItem *previous);

    void on_useOwnCloudPathButton_clicked();

    void addLocalScript();

    void on_scriptRemoveButton_clicked();

    void on_scriptPathButton_clicked();

    void on_scriptListWidget_currentItemChanged(QListWidgetItem *current,
                                                QListWidgetItem *previous);

    void on_scriptNameLineEdit_editingFinished();

    void on_scriptSearchLineEdit_textChanged(const QString &arg1);

    void on_scriptValidationButton_clicked();

    void on_scriptReloadEngineButton_clicked();

    void on_addCustomNoteFileExtensionButton_clicked();

    void on_removeCustomNoteFileExtensionButton_clicked();

    void on_defaultNoteFileExtensionListWidget_itemChanged(QListWidgetItem *item);

    void on_noteFolderShowSubfoldersCheckBox_toggled(bool checked);

    void on_noteFolderAllSubfoldersCheckBox_toggled(bool checked);

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

    void on_ownCloudSupportCheckBox_toggled();

    void on_noteFolderGitCommitCheckBox_toggled(bool checked);

    void searchScriptInRepository(bool checkForUpdates = false);

    void checkForScriptUpdates();

    void on_scriptListWidget_itemChanged(QListWidgetItem *item);

    void on_interfaceStyleComboBox_currentTextChanged(const QString &arg1);

    void on_showSystemTrayCheckBox_toggled(bool checked);

    void on_resetMessageBoxesButton_clicked();

    void onLayoutStored(const QString &layoutUuid);

    void keySequenceEvent(const QString &objectName);

    void on_exportSettingsButton_clicked();

    void on_importSettingsButton_clicked();

    void on_ignoreNoteSubFoldersResetButton_clicked();

    void on_interfaceFontSizeSpinBox_valueChanged(int arg1);

    void on_overrideInterfaceFontSizeGroupBox_toggled(bool arg1);

    void on_mcpServerEnabledCheckBox_toggled(bool checked);

    void on_mcpServerPortResetButton_clicked();

    void on_mcpServerShowTokenButton_clicked();

    void on_mcpServerCopyTokenButton_clicked();

    void on_mcpServerGenerateTokenButton_clicked();

    void on_cloudConnectionComboBox_currentIndexChanged(int index);

    void on_cloudConnectionAddButton_clicked();

    void on_cloudConnectionRemoveButton_clicked();

    void on_noteFolderCloudConnectionComboBox_currentIndexChanged(int index);

    void storeSelectedCloudConnection();

    void on_ownCloudServerAppPasswordPageButton_clicked();

    void on_allowDifferentNoteFileNameCheckBox_toggled(bool checked);

    void on_languageSearchLineEdit_textChanged(const QString &arg1);

    void on_databaseIntegrityCheckButton_clicked();

    void on_scriptReloadEngineButton2_clicked();

    void on_loginFlowButton_clicked();

    void on_loginFlowCancelButton_clicked();

    void on_defaultNoteFileExtensionListWidget_itemSelectionChanged();

    void on_appNextcloudDeckCheckBox_toggled(bool checked);

    void onSettingsConnectionTestFinished();

    void on_showStatusBarNotePathCheckBox_toggled(bool checked);

    void on_overrideInterfaceScalingFactorGroupBox_toggled(bool arg1);

    void on_interfaceScalingFactorSpinBox_valueChanged(int arg1);

   private:
    Ui::SettingsDialog *ui;
    QStatusBar *noteFolderRemotePathTreeStatusBar;
    bool appIsValid;
    QString appVersion;
    QString serverVersion;
    QString notesPathExistsText;
    QString connectionErrorMessage;
    NoteFolder _selectedNoteFolder;
    Script _selectedScript;
    static const int _defaultMarkdownHighlightingInterval = 200;
    QSplitter *_mainSplitter;
    QButtonGroup *_noteNotificationButtonGroup;
    QCheckBox *_noteNotificationNoneCheckBox;
    QString _newScriptName;
    CloudConnection _selectedCloudConnection;
    int _loginFlowPollCount = 0;
    QHash<int, bool> _pageInitialized;
    QString _installInfoTextLabel1Html;
    QString _installInfoTextLabel2Html;
    QString _installInfoTextLabel3Html;
    bool _initialDarkMode = false;
    bool _initialDarkModeColors = false;
    bool _initialDarkModeTrayIcon = false;
    bool _initialDarkModeIconTheme = false;
    QString _initialSchemaKey;
    bool _connectionTestInProgress = false;
    QList<QWidget *> _searchMatchedWidgets;
    QHash<QWidget *, QString> _searchMatchedWidgetOriginalTexts;

    void storeSettings();

    void startConnectionTest();

    void setConnectionTestInProgress(bool inProgress);

    void cancelConnectionTest();

    static void selectListWidgetValue(QListWidget *listWidget, const QString &value);

    static bool listWidgetValueExists(QListWidget *listWidget, const QString &value);

    static QString getSelectedListWidgetValue(QListWidget *listWidget);

    void setupNoteFolderPage();

    static bool scriptMatchesSearchFilter(const Script &script, const QString &searchText);

    QTreeWidgetItem *findNoteFolderRemotePathTreeWidgetItem(QTreeWidgetItem *parent,
                                                            const QString &text);

    void addPathToNoteFolderRemotePathTreeWidget(QTreeWidgetItem *parent, const QString &path);

    QString generatePathFromCurrentNoteFolderRemotePathItem(QTreeWidgetItem *item);

    void setNoteFolderRemotePathTreeWidgetFrameVisibility(bool visi);

    void setupScriptingPage();

    void storeScriptListEnabledState();

    void validateCurrentScript();

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

    bool connectionTestCanBeStarted() const;

    void reloadScriptList() const;

    void reloadCurrentScriptPage();

    void readPanelSettings();

    void storePanelSettings();

    void loadInterfaceStyleComboBox() const;

    void initSearchEngineComboBox() const;

    QKeySequenceWidget *findKeySequenceWidget(const QString &objectName);

    void storeOwncloudDebugData() const;

    void initCloudConnectionComboBox(int selectedId = -1);

    void handleDarkModeCheckBoxToggled(bool updateCheckBoxes = false, bool updateSchema = false);

    void resetOKLabelData();

    void updateSearchLineEditIcons();

    bool hasDarkModeSettingChanges() const;

    void applyDarkModeSettings();

    void populateSubfolderTree();

    void populateSubfolderTreeFromDir(QTreeWidgetItem *parentItem, const QString &path,
                                      const QString &relativePath);
    void applySubfolderTreeCheckStates(QTreeWidget *tree, const QStringList &excludedPaths);
    void applyCheckStateToItem(QTreeWidgetItem *item, const QStringList &excludedPaths);

    void updateSubfolderVisibility();

    void collectExcludedSubfolderPaths(QTreeWidgetItem *item, QStringList &excludedPaths);

    void saveSubfolderTreeSelection();

    bool initializePage(int index);
};

#endif    // SETTINGSDIALOG_H
