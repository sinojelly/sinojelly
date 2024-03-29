// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: keith.ray@gmail.com (Keith Ray)
//
// Google Test filepath utilities
//
// This header file declares classes and functions used internally by
// Google Test.  They are subject to change without notice.
//
// This file is #included in testing/base/internal/gtest-internal.h
// Do not include this header file separately!

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_FILEPATH_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_FILEPATH_H_

#include <gtest/internal/gtest-string.h>
#include <string>

namespace testing {
namespace internal {

// FilePath - a class for file and directory pathname manipulation which
// handles platform-specific conventions (like the pathname separator).
// Used for helper functions for naming files in a directory for xml output.
// Except for Set methods, all methods are const or static, which provides an
// "immutable value object" -- useful for peace of mind.
// A FilePath with a value ending in a path separator ("like/this/") represents
// a directory, otherwise it is assumed to represent a file. In either case,
// it may or may not represent an actual file or directory in the file system.
// Names are NOT checked for syntax correctness -- no checking for illegal
// characters, malformed paths, etc.

class FilePath {
 public:
  FilePath();

  FilePath(const FilePath& rhs);

  explicit FilePath(const char* pathname);
  explicit FilePath(const std::string& pathname);
  explicit FilePath(const String& pathname);

  FilePath& operator=(const FilePath& rhs);

  bool operator==(const FilePath& rhs) const;

  bool operator<(const FilePath& rhs) const;

  void Set(const FilePath& rhs);

  String ToString() const { return pathname_; }

  const char* c_str() const;

  // Returns the current working directory, or "" if unsuccessful.
  static FilePath GetCurrentDir();

  // Returns /tmp, c:/temp, or whatever temp dir should be.
  static FilePath TempDir();

  // Changes current working directory to this path.
  void SetCurrentDir();

  // Assuming the FilePath is a directory/path/like/this, removes the
  // last directory in the path and return a filespec for that parent
  // directory. If the filespec is "." or the root directory, does nothing.
  FilePath GetParentDirectory() const;

  // If filepath is "foo/", returns "foo/childName/".
  // If filepath is "foo/bar" (a file), returns "foo/childName/"
  FilePath GetChildDirectory(const String& childName) const;

  // If filepath is "foo/", returns "foo/childName".
  // If filepath is "foo/bar" (a file), returns "foo/childName"
  FilePath GetChildFile(const String& childName) const;

  // Return "" if FilePath is a directory. Returns filename without the parent
  // directories if FilePath is a file.
  String GetFileName() const;
  String GetLastDirName() const;

  // Given directory = "dir", base_name = "test", number = 0,
  // extension = "xml", returns "dir/test.xml". If number is greater
  // than zero (e.g., 12), returns "dir/test_12.xml".
  // On Windows platform, uses \ as the separator rather than /.
  static FilePath MakeFileName(const FilePath& directory,
                               const FilePath& base_name,
                               int number,
                               const char* extension);

  // Returns a pathname for a file that does not currently exist. The pathname
  // will be directory/base_name.extension or
  // directory/base_name_<number>.extension if directory/base_name.extension
  // already exists. The number will be incremented until a pathname is found
  // that does not already exist.
  // Examples: 'dir/foo_test.xml' or 'dir/foo_test_1.xml'.
  // There could be a race condition if two or more processes are calling this
  // function at the same time -- they could both pick the same filename.
  static FilePath GenerateUniqueFileName(const FilePath& directory,
                                         const FilePath& base_name,
                                         const char* extension);

  // Returns true iff the path is NULL or "".
  bool IsEmpty() const { return c_str() == NULL || *c_str() == '\0'; }

  // If input name has a trailing separator character, removes it and returns
  // the name, otherwise return the name string unmodified.
  // On Windows platform, uses \ as the separator, other platforms use /.
  FilePath RemoveTrailingPathSeparator() const;

  // Returns a copy of the FilePath with the directory part removed.
  // Example: FilePath("path/to/file").RemoveDirectoryName() returns
  // FilePath("file"). If there is no directory part ("just_a_file"), it returns
  // the FilePath unmodified. If there is no file part ("just_a_dir/") it
  // returns an empty FilePath ("").
  // On Windows platform, '\' is the path separator, otherwise it is '/'.
  FilePath RemoveDirectoryName() const;

  // RemoveFileName returns the directory path with the filename removed.
  // Example: FilePath("path/to/file").RemoveFileName() returns "path/to/".
  // If the FilePath is "a_file" or "/a_file", RemoveFileName returns
  // FilePath("./") or, on Windows, FilePath(".\\"). If the filepath does
  // not have a file, like "just/a/dir/", it returns the FilePath unmodified.
  // On Windows platform, '\' is the path separator, otherwise it is '/'.
  FilePath RemoveFileName() const;

  // Returns a copy of the FilePath with the case-insensitive extension removed.
  // Example: FilePath("dir/file.exe").RemoveExtension("EXE") returns
  // FilePath("dir/file"). If a case-insensitive extension is not
  // found, returns a copy of the original FilePath.
  FilePath RemoveExtension(const char* extension) const;

  // Creates directories so that path exists. Returns true if successful or if
  // the directories already exist; returns false if unable to create
  // directories for any reason. Will also return false if the FilePath does
  // not represent a directory (that is, it doesn't end with a path separator).
  bool CreateDirectoriesRecursively() const;

  // Delete directory represented by this path, and all of its contents.
  void DeleteAllFilesInDirectory() const;
  void DeleteFile() const;
  void DeleteDirectory() const;
  void DeleteDirectoryRecursively() const;

  void CopyFileTo(FilePath & destDir) const;

  // source is a directory, copy its contents to dest directory.
  void CopyContentsTo(FilePath & destDir) const;

  // Create the directory so that path exists. Returns true if successful or
  // if the directory already exists; returns false if unable to create the
  // directory for any reason, including if the parent directory does not
  // exist. Not named "CreateDirectory" because that's a macro on Windows.
  bool CreateFolder() const;

  // Returns true if FilePath describes something in the file-system,
  // either a file, directory, or whatever, and that something exists.
  bool FileOrDirectoryExists() const;

  // Returns true if pathname describes a directory in the file-system
  // that exists.
  bool DirectoryExists() const;

  // Returns true if pathname describes a file in the file-system
  // that exists.
  bool FileExists() const;

  // Returns true if FilePath ends with a path separator, which indicates that
  // it is intended to represent a directory. Returns false otherwise.
  // This does NOT check that a directory (or file) actually exists.
  bool IsDirectory() const;

  bool IsRootDirectory() const;

  // renames the file on disk
  FilePath RenameFileTo(const std::string& newName) const;

  // renames the file on disk
  FilePath AddSuffixToFilename(const std::string& suffix) const;

  // renames the file on disk - don't specify the "." part of the suffix.
  FilePath RemoveSuffixFromFilename(const std::string& suffix) const;

  long GetModificationDateInSeconds() const;

 private:
  String pathname_;

  void Normalize();
};  // class FilePath

}  // namespace internal
}  // namespace testing

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_FILEPATH_H_
