/**
 * \file ImageEntry.hpp
 * \brief The ImageEntry class definition.
 * \sa ImageEntry.cpp
 */

#ifndef IMAGE_ENTRY
#define IMAGE_ENTRY

#include <string>

/** \class ImageEntry
 * \brief Class for manipulating icon references as they appear in the registry.
 *
 * An ImageEntry consists of a path to a file which conatains an icon and,
 * optionally, an index to select a particular icon from that file.
 *
 * \note If the delimiters change, then files already written by IconMagic
 * will become unreadable.
 *
 * \sa ExtensionHistory RegistryHistory
 */
class ImageEntry
{
public:
  /** \name Delimiters
   * These strings define delimiters used when an image entry is represented as a
   * string.
   */
  ///@{
  /** Separate file path from index */
  const static std::string seperator;
  /** Delimit the start of a block */
  const static std::string blockOpen;
  /** Delimit the end of a block */
  const static std::string blockShut;
  ///@}

  /// Default constructor.
  ImageEntry();

  /// Build an ImageEntry object from component data.
  /**
   * This method expects a valid path to a file and a string which must be
   * parseable to an integer. The second parameter can be the empty string if
   * the file path points to a file which only contains a single image.
   *
   * This method will only update the internal state of the object if the input
   * is considered valid.
   *
   * \param image_path Path to a file which contains icon data.
   * \param image_index Index into the image file.
   *
   * \sa ImageEntry::createFromFormatted(std::string) ImageEntry::isValid()
   */
  void createFromData(std::string image_path, std::string image_index);

  /// Build an ImageEntry object from a formatted string.
  /**
   * Expects a string which is block delimited left and right, and contains an
   * image path and the image index (even if it is the empty string) separated by
   * the seperator delimter.
   *
   * This method will only update the internal state of the object if the input
   * is considered valid.
   *
   * \param entry The string to be parsed to an ImageEntry object.
   *
   * \sa ImageEntry::createFromData(std::string, std::string) ImageEntry::isValid()
   */
  void createFromFormatted(std::string entry);

  /// Get the image path.
  std::string getImagePath() const;

  /// Get the image index.
  std::string getImageIndex() const;

  /// Create a string representation of the object.
  /**
   * Of the form
   *
   * \code blockOpen + imagePath + seperator + imageIndex + blockShut \endcode
   *
   * \return String representation of the object.
   */
  std::string toString() const;

  /// Check if the image entry is valid.
  /**
   * The object is valid if there is a non-empty value for the image path.
   *
   * The image path is only set if
   * - The object is not already valid, overwiting is not allowed.
   * - IconMagic can read from the file path.
   * - The given index string is parseable to an integer in the allowed range.
   *
   * \todo The index range needs to be configurable.
   */
  bool isValid();

private:
  void create(std::string image_path, std::string image_index);

  std::string imagePath;
  std::string imageIndex;
};

#endif
