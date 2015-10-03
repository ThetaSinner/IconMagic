/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#ifndef REGISTYMANAGER_HPP_INCLUDED
#define REGISTYMANAGER_HPP_INCLUDED

#include <Windows.h>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

class Manager
{
  /// Notes

  // Have two cache files and only use one at a time

  /// Shared functionality

  // select an image
  // copy selected image into IconMagic directory. file sizes will cause some issues here?
  // Icon extraction? https://msdn.microsoft.com/en-us/library/ms648067%28v=VS.85%29.aspx

  /// When the file type already exists (has an entry with a default icon.

  // check if there is an existing cache of registry entries
  // if there's no cache then read the registry, and create one
  // otherwise just load the cache

  // option to reload the cache

  // basic matching to lookup existing entries from the loaded cache
  // dynamic menu displays for each file type
  // display current value
  // new image / roll back (if available) options
  // under new have one input for the icon, and one for icon position in file
  // under roll back give you can either roll back once, or restore default
  // on attempting for add or roll back check the file exists.

  // clean up option in front menu, look through history from most recent back to find the first image which isn't missing
  // add that image to the most recent end of the list and update the registry.

  /// Add a new file type

  // request the file type extension, and ask the user at least twice if they are sure of the spelling
  // use shared image selection and image copying
  // update relevant files

  /// Rebuild system icon cache option

  // this should be done automatically after a change by IconMagic anyway, but can't hurt.

  /// Menu design

  // front :
  //  - change entry for existing file type
  //  - create entry for new file type
  //  - refresh system icon cache
  //  - quit

  // change entry (requires a search interface before menu)
  //  - change icon for this type
  //  - roll back changes (if available)
  //  - remove this file type from the registry (not recommended)
  //  - back to main menu

public:
  static const std::string ICON_MAGIC_CACHE_NAME;
  static const std::string ICON_MAGIC_CACHE_FILE_EXTENSION;

  void cacheBuild();

private:

  // need an internal file manager to decide where to write, or where to read from.
};

#endif // REGISTYMANAGER_HPP_INCLUDED
