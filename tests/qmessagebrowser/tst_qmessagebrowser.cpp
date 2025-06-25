#include <QtTest>
#include "qmessagebrowser.h"

class QMessageBrowserTest : public QObject
{
    Q_OBJECT
private slots:
    void insertWithoutScrolling();
};

void QMessageBrowserTest::insertWithoutScrolling()
{
    QMessageBrowser browser;
    browser.resize(200, 100);

    QString content;
    for(int i = 0; i < 100; ++i)
        content += QString("Line %1<br>").arg(i);
    browser.setHtml(content);

    browser.show();
    QTest::qWaitForWindowExposed(&browser);

    QScrollBar *sb = browser.verticalScrollBar();
    sb->setValue(sb->maximum());
    int before = sb->value();

    auto data = browser.beginInsertWithoutScrolling();
    browser.moveCursor(QTextCursor::Start);
    browser.insertHtml("<p>prepended</p>");
    browser.endInsertWithoutScrollig(data);

    QCOMPARE(sb->value(), before);
}

QTEST_MAIN(QMessageBrowserTest)
#include "tst_qmessagebrowser.moc"

