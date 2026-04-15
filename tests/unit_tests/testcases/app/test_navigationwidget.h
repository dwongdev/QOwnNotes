#ifndef TESTNAVIGATIONWIDGET_H
#define TESTNAVIGATIONWIDGET_H

#include <QObject>

class TestNavigationWidget : public QObject {
    Q_OBJECT

   private Q_SLOTS:
    void testParseDocumentSupportsScriptedHeadings();
};

#endif    // TESTNAVIGATIONWIDGET_H
