#include "test_navigationwidget.h"

#include <QTextDocument>
#include <QtTest>

#include "libraries/qmarkdowntextedit/markdownhighlighter.h"
#include "services/scriptingservice.h"
#include "widgets/navigationwidget.h"

void TestNavigationWidget::testParseDocumentSupportsScriptedHeadings() {
    ScriptingService *scriptingService = ScriptingService::instance();
    scriptingService->initComponents();

    scriptingService->addHighlightingRule(QStringLiteral("^@ +.+? +@\\s*$"), QStringLiteral("@"),
                                          MarkdownHighlighter::H1);
    scriptingService->addHighlightingRule(QStringLiteral("^@@ +.+? +@@\\s*$"), QStringLiteral("@@"),
                                          MarkdownHighlighter::H2);
    scriptingService->addHighlightingRule(QStringLiteral("^@@@ +.+? +@@@\\s*$"),
                                          QStringLiteral("@@@"), MarkdownHighlighter::H3);

    QTextDocument document;
    document.setPlainText(
        QStringLiteral("@ Introduction @\n"
                       "\n"
                       "This heading uses the fictitious \"@ ... @\" syntax.\n"
                       "\n"
                       "@@ Background @@\n"
                       "\n"
                       "@@@ Details @@@\n"
                       "\n"
                       "Normal paragraph\n"
                       "\n"
                       "@ Conclusion @\n"));

    const auto nodes = NavigationWidget::parseDocument(&document);

    QCOMPARE(nodes.count(), 4);
    QCOMPARE(nodes.at(0).text, QStringLiteral("Introduction"));
    QCOMPARE(nodes.at(0).elementType, int(MarkdownHighlighter::H1));
    QCOMPARE(nodes.at(1).text, QStringLiteral("Background"));
    QCOMPARE(nodes.at(1).elementType, int(MarkdownHighlighter::H2));
    QCOMPARE(nodes.at(2).text, QStringLiteral("Details"));
    QCOMPARE(nodes.at(2).elementType, int(MarkdownHighlighter::H3));
    QCOMPARE(nodes.at(3).text, QStringLiteral("Conclusion"));
    QCOMPARE(nodes.at(3).elementType, int(MarkdownHighlighter::H1));

    scriptingService->initComponents();
}
