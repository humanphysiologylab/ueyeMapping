/*!
 * \file    main.cpp
 * \date    22.01.2010
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   Qt uEye demo main source file
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 *      
 * \li  28.05.2013 - Add Encoding for CStrings
 */

#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include "mainview.h"
#include "version.h"

int main (int argc,char *argv[])
{
    QApplication a (argc, argv);
    QString strStartID = "";

#ifdef QT4
    // Set Encoding to Utf-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif /* QT4 */

    // using cmd line arguments
    if (argc > 1)
    {
        QString strArgs = QString(argv[1]);
        if(strArgs.left(2) == "-s" ) // auto start ID option
        {
            strStartID = strArgs.remove(0,2);
        }
    }
    Mainview w(0,strStartID);

    //check libueye_api Version if working with demo
    DWORD ver = is_GetDLLVersion ();
    bool bDllVersion = false;
    int nDllMajor = ver >> 24;
    int nDllMinor = ver >> 16 & 0xff;
    if (nDllMajor > DLL_VER_MAJOR)
        bDllVersion = true;
    else if (nDllMajor == DLL_VER_MAJOR)
    {
        if (nDllMinor >= DLL_VER_MINOR)
            bDllVersion = true;
    }

    // if DLL version is to old, show a user message and exit the demo
    if (!bDllVersion)
    {
        QMessageBox msgbox;
        msgbox.setText(QString("Demo Version %1 don't work with\n"
                               "libueye_api < %2.%3!\n"
                               "use a newer libueye!")
                               .arg(DEMO_VERSION_STR)
                               .arg(DLL_VER_MAJOR)
                               .arg(DLL_VER_MINOR));
        msgbox.setIcon(QMessageBox::Critical);
        msgbox.exec();
        return 0;
    }

    w.show ();
    return a.exec ();
}
