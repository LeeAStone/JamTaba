#include "gui/mainframe.h"
#include "MainController.h"
#include "JamtabaFactory.h"
#include "persistence/Settings.h"
#include <QApplication>
#include <QLoggingCategory>
#include <QDir>
#include <QStandardPaths>


void customLogHandler(QtMsgType, const QMessageLogContext &, const QString &);

//#include "audio/vst/vsthost.h"
//#include "audio/vst/VstPlugin.h"


int main(int argc, char* args[] ){


//    Vst::VstHost* host = Vst::VstHost::getInstance();
//    Vst::VstPlugin plugin(host);
//    bool ok = false;
//    ok = test(plugin);

//    qWarning() << "loading finished";
//    if(!ok){
//        qWarning() << "loading fail!";
//    }
//    else{
//        qWarning() << "loading ok!";
//    }


    QApplication::setApplicationName("Jamtaba 2");
    QApplication::setApplicationVersion(APP_VERSION);

    qputenv("QT_LOGGING_CONF", ":/qtlogging.ini");//log cconfigurations is in resources at moment

    qInstallMessageHandler(customLogHandler);

    JamtabaFactory* factory = new ReleaseFactory();
    Persistence::Settings settings;//read from file in constructor
    settings.load();

    Controller::MainController mainController(factory, settings, argc, args);//MainController extends QApplication

    MainFrame mainFrame(&mainController);
    mainFrame.show();

    delete factory;
    int returnCode = mainController.exec();
    mainController.saveLastUserSettings(mainFrame.getInputsSettings());

    return returnCode;

 }

//++++++++++++++++++++++++++++++++++

void customLogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString stringMsg;
    QString fullFileName(context.file);
    QString file;
    int lastPathSeparatorIndex = fullFileName.lastIndexOf(QDir::separator());
    if(lastPathSeparatorIndex){
        file = fullFileName.right(fullFileName.size() - lastPathSeparatorIndex - 1);//.toStdString().c_str();
    }
    else{
        file = fullFileName;//.toStdString().c_str();
    }

    QTextStream stream(&stringMsg);
    switch (type) {
    case QtDebugMsg:
        stream << "\nDEBUG:" << localMsg.constData() << " "  << " in " << file << " " << context.line << endl;
        break;
    case QtWarningMsg:
        stream << "\n\nWARNING: " << localMsg.constData() <<  context.function <<  " " << file << context.line << endl;
        break;
    case QtCriticalMsg:
        stream << "\n\nCRITICAL:" << localMsg.constData() <<  context.function << " " << file << context.line << endl <<endl;
        break;
    case QtFatalMsg:
        stream << "\n\nFATAL:" << localMsg.constData() << context.function << file << context.line << endl << endl;
        //abort();
        break;
    default:
       stream << "\n\nINFO:" << localMsg.constData() << file << context.line << endl << endl;
    }
    QTextStream(stdout) << stringMsg << endl;

    if(type != QtDebugMsg){//write the critical messages to log file
        QDir logDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
        if(!logDir.exists()){
            logDir.mkpath(".");
        }
        QFile outFile( logDir.absoluteFilePath("log.txt"));
        if(outFile.open(QIODevice::WriteOnly | QIODevice::Append)){
           QTextStream ts(&outFile);
           ts << stringMsg << endl;
        }
    }

    if(type == QtFatalMsg){
        abort();
    }
}


