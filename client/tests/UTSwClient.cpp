#include <QTest>
#include "../GameHost.h"

class SwClientUT : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {}

    void cleanupTestCase() {}

    void testJsonParser()
    {
        const QByteArray rawJson = QByteArray("{\"msg\":\"hello\"}");
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(rawJson);
        QCOMPARE(g_GameHost::Instance()->parseJson(jsonDoc.object()), "hello");
    }
};

QTEST_MAIN(SwClientUT)

#include "UTSwClient.moc"
