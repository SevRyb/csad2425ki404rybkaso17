#include <QTest>
#include <QSignalSpy>
#include "../GameHost.h"

class SwClientUT : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        m_magickNumber = 5;
        g_GameHost::Instance();
    }

    void cleanupTestCase() {}

    void testConnection()
    {
        g_GameHost::Instance()->reqTestConnection(m_magickNumber);

        QSignalSpy signalSpy(g_GameHost::Instance(), &GameHost::sigTestConnection);
        QVERIFY(signalSpy.wait(5000));
        QCOMPARE(signalSpy.count(), 1);

        QList<QVariant> arguments = signalSpy.takeFirst();
        QVERIFY(arguments.count() == 2);
        QVERIFY(arguments.at(0).type() == QVariant::Int);
        QVERIFY(arguments.at(1).type() == QVariant::String);

        QCOMPARE((arguments.at(0).toInt() - 123) / 2, m_magickNumber);
        QCOMPARE(arguments.at(1).toString(), "TicTacToe#3x3");
    }

private:
    int m_magickNumber;
};

QTEST_MAIN(SwClientUT)

#include "UTSwClient.moc"
