/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef LXQTPLUGININFO_H
#define LXQTPLUGININFO_H

#include <xdgqt/XdgDesktopFile>
#include <QtCore/QString>
#include <QtCore/QList>

#include <QtCore/QFileInfo>
#include <QtCore/QtAlgorithms>
#include <QtCore/QDebug>

class QLibrary;

namespace LxQt
{

/*!
Every plugin needs a .desktop file that describes it. The basename of this file must
be same as the basename of the plugin library.

razorpanel_clock2.desktop file

[Desktop Entry]
  Type=Service
  ServiceTypes=RazorPanel/Plugin
  Name=Clock
  Comment=Clock and calendar

PluginInfo class gives the interface for reading the values from the plugin .desktop file.
This is a pure virtual class, you must implement libraryDir(), translationDir(), and instance() methods.
*/
class PluginInfo: public XdgDesktopFile
{
public:
    /// Constructs a PluginInfo object for accessing the info stored in the .desktop file.
    explicit PluginInfo();

    //! Reimplemented from XdgDesktopFile.
    virtual bool load(const QString& fileName);


    //! Reimplemented from XdgDesktopFile.
    //PluginInfo& operator=(const PluginInfo& other);


    //! Returns identification string of this plugin, identified plugin type. Now id is part of the filename.
    QString id() const { return mId; }

    //! This function is provided for convenience. It's equivalent to calling value("ServiceTypes").toString().
    QString serviceType() const  { return value("ServiceTypes").toString(); }

    //! Reimplemented from XdgDesktopFile.
    virtual bool isValid() const;

    /*! Loads the library and returns QLibrary object if the library was loaded successfully; otherwise returns 0.
        @parm libDir directory where placed the plugin .so file. */
    QLibrary* loadLibrary(const QString& libDir) const;


    /*! Returns a list of PluginInfo objects for the matched files in the directories.
      @param desktopFilesDirs - scanned directories names.
      @param serviceType - type of the plugin, for example "RazorPanel/Plugin".
      @param nameFilter  - wildcard filter that understands * and ? wildcards.

      If the same filename is located under multiple directories only the first file should be used.
    */
    static QList<PluginInfo> search(const QStringList& desktopFilesDirs, const QString& serviceType, const QString& nameFilter="*");

    /// This function is provided for convenience. It's equivalent to new calling search(QString(desktopFilesDir), serviceType, nameFilter)
    static QList<PluginInfo> search(const QString& desktopFilesDir, const QString& serviceType, const QString& nameFilter="*");

private:
    QString mId;
};

typedef QList<PluginInfo> PluginInfoList;

} // namespace LxQt

QDebug operator<<(QDebug dbg, const LxQt::PluginInfo& pi);
QDebug operator<<(QDebug dbg, const LxQt::PluginInfo* const pi);

QDebug operator<<(QDebug dbg, const LxQt::PluginInfoList& list);
QDebug operator<<(QDebug dbg, const LxQt::PluginInfoList* const pluginInfoList);

#endif // LXQTPLUGININFO_H
