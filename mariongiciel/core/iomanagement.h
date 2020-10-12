/**
 * \file iomanagement.cpp
 * \brief Manage inputs output
 * \author Auzou
 * \version 0.1
 * \date last update : 29/09/2007
 *
 * This file contains all the logic for managing inputs and outputs via several static classes as well as log management
 *
 */


#ifndef IOMANAGEMENT_H
#define IOMANAGEMENT_H
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include <QFileInfo>
#include <QVector>
#include <QDateTime>

#include "../global.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

/**
 * \namespace mariongiciel::core
 * \brief Application core inline namespace
 *
 */

namespace mariongiciel::core {

// not implemented
enum class ressourceDirError {
    _MAIN_RCS_ = 0, // RCS not exists (all not exist config/icon/css...)
    _ICON_     = 1, // ICON not exists (your app style is dead)
    _CSS_      = 2, // CSS not exists (your style is dead)
    //_CONFIG_ = 3,
};

/**
 * \class DirManagement
 * \brief Static folder management class
 *
 */
class DirManagement
{
    private :
    public :
        DirManagement() = delete;
        DirManagement(DirManagement&) = delete;
        DirManagement(const DirManagement&&) = delete;

    public :

        /**
          * \fn static void initDirsEnv(void)
          * \brief Initializes the folder environment
          *
          * \param void
          * \return void
          */
        static void initDirsEnv();

        /**
          * \fn static bool exist(const QString &path)
          * \brief check folder if exist
          *
          * \param const QString &path
          * \return true if exist or false if not exist
          */
        static bool exist(const QString &path);

        /**
          * \fn static bool create(const QString &path)
          * \brief Create folder
          *
          * \param const QString &path
          * \return true if create or false if not create
          */
        static bool create(const QString &path);

        /**
          * \fn static bool isNotExistCreate(const QString &path)
          * \brief Create folder if not exist
          *
          * \param const QString &path
          * \return true if create or false if not create
          */
        static bool isNotExistCreate(const QString &path);

        /**
          * \fn static QVector<QFileInfo> getFile(const QString &path)
          * \brief get QVector of QFileInfo of whole folder
          *
          * \param const QString &path
          * \return QVector<QFileInfo>
          */
        static QVector<QFileInfo> getFile(const QString &path);
};

/**
 * \class FileManagement
 * \brief Static file management class
 *
 */
class FileManagement
{
    private :
    public :
        FileManagement() = delete;
        FileManagement(FileManagement&) = delete;
        FileManagement(const FileManagement&&) = delete;

    public :

        /**
          * \fn static bool isExist(const QString &path)
          * \brief
          *
          * \param const QString &path
          * \return bool
          */
        static bool isExist(const QString &path);


        /**
          * \fn static const QString readFile(const QString &path)
          * \brief Read file and return the content in const QString
          *
          * \param const QString &path
          * \return const QString
          */
        static const QString readFile(const QString &path);

        /**
          * \fn static bool write(const QString &path, const QString &data)
          * \brief get QVector of QFileInfo of whole folder
          *
          * \param const QString &path, const QString &data
          * \return true if write or false if can't not open file
          */
        static bool write(const QString &path, const QString &data);

        /**
          * \fn static bool writeAppend(const QString &path, const QString &data)
          * \brief Append data into file
          *
          * \param const QString &path, const QString &data
          * \return true if append data or false if can't not open file
          */
        static bool writeAppend(const QString &path, const QString &data);

        /**
          * \fn static bool remove(const QString &path, bool archive = true)
          * \brief remove/archive file (default archive = true)
          *
          * \param const QString &path, bool archive = true
          * \return bool
          */
        static bool remove(const QString &path);

        /**
          * \fn static bool moveToArchive(const QString &path, const QString &target, bool remove = true)
          * \brief remove/archive file (default archive = true)
          *
          * \param const QString &path, bool archive = true
          * \return bool
          */
        static bool moveToArchive(const QString &path, const QString &target, bool remove = true);
};

// name version CRLF
// [date] [level] [localisation:class] [text] CRLF

enum level_E {
    _ERROR_ = 0,
    _INFO_  = 1,
    _WARN_  = 2,
    _ALERT_ = 3,
};

/**
 * \class LogManagement
 * \brief Static log management class
 *
 */
class LogManagement
{
    private :
        static const QString head();
        static QString formate(const QString &message, const QString &localisation, const QString &level);
        static QString getLevelStr(level_E level_e);

    public :
        LogManagement() = delete;
        ~LogManagement() = delete;

    public :
        static void log(const QString &message, const QString &localisation, level_E level_e);
        static void clear(bool archive = true);
};



} // END NAMESPACE mariongiciel::core

#endif // IOMANAGEMENT_H
