#ifndef INFOFRAMEDBUSADAPTOR_CPP
#define INFOFRAMEDBUSADAPTOR_CPP

#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Adaptor class for interface org.DaliBox.GUIInterface
 */
class InfoFrameDBusAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.DaliBox.GUIInterface")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.DaliBox.GUIInterface\">\n"
"    <method name=\"updateVariableValue\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"new_value\"/>\n"
"    </method>\n"
"    <method name=\"updateVariableValue2\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"new_value\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    InfoFrameDBusAdaptor(QObject *parent);
    virtual ~InfoFrameDBusAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void updateVariableValue(int new_value);
    void updateVariableValue2(int new_value);
Q_SIGNALS: // SIGNALS
};

#endif
