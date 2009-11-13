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
// Authors: keith.ray@gmail.com (Keith Ray)

#include <gtest/internal/gtest-filepath.h>
#include <gtest/internal/gtest-port.h>

#ifdef _WIN32_WCE
	#include <windows.h>
#elif defined(_WIN32)
	#include <windows.h>
	#include <direct.h>
	#include <io.h>
	#include <sys/stat.h>

	#undef DeleteFile
#else
	#include <sys/stat.h>
	#include <unistd.h>
	//#include <fcntl.h>
#endif // _WIN32_WCE or _WIN32

#include "ILFileUtils.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <gtest/internal/gtest-string.h>

namespace testing {
namespace internal {

#ifdef _WIN32
	const char kPathSeparator = '\\';
	const char kPathSeparatorString[] = "\\";

	#ifdef _WIN32_WCE
		// Windows CE doesn't have a current directory. You should not use
		// the current directory in tests on Windows CE, but this at least
		// provides a reasonable fallback.
		const char kCurrentDirectoryString[] = "\\";
		// Windows CE doesn't define INVALID_FILE_ATTRIBUTES
		const DWORD kInvalidFileAttributes = 0xffffffff;
	#else
		const char kCurrentDirectoryString[] = ".\\";
	#endif  // _WIN32_WCE
#else
	const char kPathSeparator = '/';
	const char kPathSeparatorString[] = "/";
	const char kCurrentDirectoryString[] = "./";
#endif  // _WIN32

// Returns the current working directory, or "" if unsuccessful.
FilePath FilePath::GetCurrentDir() {
#ifdef _WIN32_WCE
// Windows CE doesn't have a current directory, so we just return
// something reasonable.
  return FilePath(kCurrentDirectoryString);
#elif defined(GTEST_OS_WINDOWS) || defined(_WIN32)
  char cwd[_MAX_PATH + 1] = {};
  if (NULL != _getcwd(cwd, sizeof(cwd)))
  {
	  return FilePath(String::Format("%s%s", cwd, "\\"));
  }
  else
	  return FilePath("");
#else
  char cwd[PATH_MAX + 1] = {};
  if (NULL != getcwd(cwd, sizeof(cwd)))
  {
	  return FilePath(String::Format("%s%s", cwd, "/"));
  }
  else
	  return FilePath("");
#endif
}

// Returns /tmp, c:/temp, or whatever temp dir should be.
FilePath FilePath::TempDir()
{
#ifdef _WIN32_WCE
    return FilePath(kPathSeparatorString + "temp" + kPathSeparatorString);

#elif defined(_WIN32)
    // MSVC 8 deprecates getenv(), so we want to suppress warning 4996
    // (deprecated function) there.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
    const char* temp_dir = getenv("TEMP");
#pragma warning(pop)           // Restores the warning state.

    if (temp_dir == NULL || temp_dir[0] == '\0')
    {
    	return FilePath(String::Format("%s%s%s",
    			kPathSeparatorString, "temp", kPathSeparatorString));
    }
    else if (temp_dir[strlen(temp_dir)-1] == kPathSeparator)
      return FilePath(temp_dir);
    else
      return FilePath(String::Format("%s%s", temp_dir, kPathSeparatorString));
#else
    return FilePath("/tmp/");
#endif
}

void FilePath::SetCurrentDir()
{
	#ifdef _WIN32_WCE
		// do nothing.
	#elif defined(_WIN32)
		chdir(this->pathname_.c_str());
	#else
		chdir(this->pathname_.c_str());
	#endif
}

FilePath::FilePath()
	: pathname_("")
{
	Normalize();
}

FilePath::FilePath(const FilePath& rhs)
	: pathname_(rhs.pathname_)
{ }

FilePath::FilePath(const char* pathname)
	: pathname_(pathname)
{
	if (pathname == NULL)
		pathname_ = "";
	Normalize();

	if (pathname_ == ".")
		pathname_ = FilePath::GetCurrentDir().c_str();

	if (pathname_ == kCurrentDirectoryString)
		pathname_ = FilePath::GetCurrentDir().c_str();
}

FilePath::FilePath(const std::string& pathname)
	: pathname_(pathname.c_str())
{
	Normalize();

	if (pathname_ == ".")
		pathname_ = FilePath::GetCurrentDir().c_str();

	if (pathname_ == kCurrentDirectoryString)
		pathname_ = FilePath::GetCurrentDir().c_str();
}

FilePath::FilePath(const String& pathname)
	: pathname_(pathname)
{
	Normalize();

	if (pathname_ == ".")
		pathname_ = FilePath::GetCurrentDir().c_str();

	if (pathname_ == kCurrentDirectoryString)
		pathname_ = FilePath::GetCurrentDir().c_str();
}

FilePath& FilePath::operator=(const FilePath& rhs)
{
	  Set(rhs);
	  return *this;
}

bool FilePath::operator==(const FilePath& rhs) const
{
	return this->pathname_ == rhs.pathname_.c_str();
}

bool FilePath::operator<(const FilePath& rhs) const
{
	return this->pathname_ < rhs.pathname_;
}

void FilePath::Set(const FilePath& rhs)
{
	pathname_ = rhs.pathname_;
}

const char* FilePath::c_str() const
{
	return pathname_.c_str();
}

// Returns a copy of the FilePath with the case-insensitive extension removed.
// Example: FilePath("dir/file.exe").RemoveExtension("EXE") returns
// FilePath("dir/file"). If a case-insensitive extension is not
// found, returns a copy of the original FilePath.
FilePath FilePath::RemoveExtension(const char* extension) const {
  String dot_extension(String::Format(".%s", extension));
  if (pathname_.EndsWithCaseInsensitive(dot_extension.c_str())) {
    return FilePath(String(pathname_.c_str(), pathname_.GetLength() - 4));
  }
  return *this;
}

// Returns a copy of the FilePath with the directory part removed.
// Example: FilePath("path/to/file").RemoveDirectoryName() returns
// FilePath("file"). If there is no directory part ("just_a_file"), it returns
// the FilePath unmodified. If there is no file part ("just_a_dir/") it
// returns an empty FilePath ("").
// On Windows platform, '\' is the path separator, otherwise it is '/'.
FilePath FilePath::RemoveDirectoryName() const {
  const char* const last_sep = strrchr(c_str(), kPathSeparator);
  return last_sep ? FilePath(String(last_sep + 1)) : *this;
}

// RemoveFileName returns the directory path with the filename removed.
// Example: FilePath("path/to/file").RemoveFileName() returns "path/to/".
// If the FilePath is "a_file" or "/a_file", RemoveFileName returns
// FilePath("./") or, on Windows, FilePath(".\\"). If the filepath does
// not have a file, like "just/a/dir/", it returns the FilePath unmodified.
// On Windows platform, '\' is the path separator, otherwise it is '/'.
FilePath FilePath::RemoveFileName() const {
  const char* const last_sep = strrchr(c_str(), kPathSeparator);
  return FilePath(last_sep ? String(c_str(), last_sep + 1 - c_str())
                           : String(kCurrentDirectoryString));
}

// Helper functions for naming files in a directory for xml output.

// Given directory = "dir", base_name = "test", number = 0,
// extension = "xml", returns "dir/test.xml". If number is greater
// than zero (e.g., 12), returns "dir/test_12.xml".
// On Windows platform, uses \ as the separator rather than /.
FilePath FilePath::MakeFileName(const FilePath& directory,
                                const FilePath& base_name,
                                int number,
                                const char* extension) {
  FilePath dir(directory.RemoveTrailingPathSeparator());
  if (number == 0) {
    return FilePath(String::Format("%s%c%s.%s", dir.c_str(), kPathSeparator,
                                   base_name.c_str(), extension));
  }
  return FilePath(String::Format("%s%c%s_%d.%s", dir.c_str(), kPathSeparator,
                                 base_name.c_str(), number, extension));
}

// Returns true if pathname describes something findable in the file-system,
// either a file, directory, or whatever.
bool FilePath::FileOrDirectoryExists() const {
#ifdef _WIN32
#ifdef _WIN32_WCE
  LPCWSTR unicode = String::AnsiToUtf16(pathname_.c_str());
  const DWORD attributes = GetFileAttributes(unicode);
  delete [] unicode;
  return attributes != kInvalidFileAttributes;
#else
  struct _stat file_stat = {};
  return _stat(pathname_.c_str(), &file_stat) == 0;
#endif  // _WIN32_WCE
#else
  struct stat file_stat = {};
  return stat(pathname_.c_str(), &file_stat) == 0;
#endif  // GTEST_OS_WINDOWS
}

// Returns true if pathname describes a directory in the file-system
// that exists.
bool FilePath::DirectoryExists() const {
  bool result = false;
#ifdef _WIN32
  FilePath removed_sep(this->RemoveTrailingPathSeparator());
#ifdef _WIN32_WCE
  LPCWSTR unicode = String::AnsiToUtf16(removed_sep.c_str());
  const DWORD attributes = GetFileAttributes(unicode);
  delete [] unicode;
  if ((attributes != kInvalidFileAttributes) &&
      (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
    result = true;
  }
#else
  struct _stat file_stat = {};
  result = _stat(removed_sep.c_str(), &file_stat) == 0 &&
      (_S_IFDIR & file_stat.st_mode) != 0;
#endif  // _WIN32_WCE
#else
  struct stat file_stat = {};
  result = stat(pathname_.c_str(), &file_stat) == 0 &&
      S_ISDIR(file_stat.st_mode);
#endif  // _WIN32
  return result;
}

#ifdef _WIN32
bool FilePath::FileExists() const
{
	if (this->IsDirectory())
		return false;
	struct _stat file_stat = {};
	bool result = _stat(this->c_str(), &file_stat) == 0 &&
		(_S_IFREG & file_stat.st_mode) != 0;
	return result;
}
#else
bool FilePath::FileExists() const
{
	if (this->IsDirectory())
		return false;
	struct stat file_stat = {};
	bool result = stat(pathname_.c_str(), &file_stat) == 0 &&
		S_ISREG(file_stat.st_mode);
	return result;
}
#endif

bool FilePath::IsRootDirectory() const {
#ifdef _WIN32
  const char* const name = pathname_.c_str();
  return pathname_.GetLength() == 3 &&
     ((name[0] >= 'a' && name[0] <= 'z') ||
      (name[0] >= 'A' && name[0] <= 'Z')) &&
     name[1] == ':' &&
     name[2] == kPathSeparator;
#else
  return pathname_ == kPathSeparatorString;
#endif
}

// Returns a pathname for a file that does not currently exist. The pathname
// will be directory/base_name.extension or
// directory/base_name_<number>.extension if directory/base_name.extension
// already exists. The number will be incremented until a pathname is found
// that does not already exist.
// Examples: 'dir/foo_test.xml' or 'dir/foo_test_1.xml'.
// There could be a race condition if two or more processes are calling this
// function at the same time -- they could both pick the same filename.
FilePath FilePath::GenerateUniqueFileName(const FilePath& directory,
                                          const FilePath& base_name,
                                          const char* extension) {
  FilePath full_pathname;
  int number = 0;
  do {
    full_pathname.Set(MakeFileName(directory, base_name, number++, extension));
  } while (full_pathname.FileOrDirectoryExists());
  return full_pathname;
}

// Returns true if FilePath ends with a path separator, which indicates that
// it is intended to represent a directory. Returns false otherwise.
// This does NOT check that a directory (or file) actually exists.
bool FilePath::IsDirectory() const {
  return pathname_.EndsWith(kPathSeparatorString);
}

// Create directories so that path exists. Returns true if successful or if
// the directories already exist; returns false if unable to create directories
// for any reason.
bool FilePath::CreateDirectoriesRecursively() const {
  if (!this->IsDirectory()) {
    return false;
  }

  if (pathname_.GetLength() == 0 || this->DirectoryExists()) {
    return true;
  }

  const FilePath parent(this->RemoveTrailingPathSeparator().RemoveFileName());
  return parent.CreateDirectoriesRecursively() && this->CreateFolder();
}

void FilePath::DeleteFile() const
{
  if (!this->IsDirectory())
    ::remove(pathname_.c_str());
}

void FilePath::DeleteDirectory() const
{
  #ifdef _WIN32
    _rmdir(pathname_.c_str());
  #else
    rmdir(pathname_.c_str());
  #endif  // _WIN32
}

// Deletes directory represented by this path, and all of its contents.
void FilePath::DeleteAllFilesInDirectory() const {
  if (!this->IsDirectory())
  {
    return;
  }
  IL::FilePathList contents = IL::FileUtils::listAllFilePathsInDir(pathname_.c_str());
  for (IL::FilePathList::size_type i = 0; i < contents.size(); i++)
    contents[i].DeleteFile();
}

void FilePath::DeleteDirectoryRecursively() const {
  DeleteAllFilesInDirectory();
  IL::FileList dirs = IL::FileUtils::listAllDirsInDir(pathname_.c_str());
  for (IL::FileList::size_type i = 0; i < dirs.size(); i++)
  {
	  FilePath sub(this->GetChildDirectory(dirs[i].c_str()));
	  sub.DeleteDirectoryRecursively();
  }
  DeleteDirectory();
}

void FilePath::CopyFileTo(FilePath & dest) const
{
  FilePath destFile(dest);
  if (dest.IsDirectory())
    destFile = dest.GetChildFile(this->GetFileName());

#if _WIN32

  ::CopyFileA( this->c_str(), destFile.c_str(), true );

#else

	// original code was copied from the posix portion of boost filecopy,
    // modified to use FILE because failures were closing stdout.

	const std::size_t buf_sz = 2048;
	char buf[buf_sz] = { 0 };

	FILE* infile = fopen(pathname_.c_str(), "rb");
	FILE* outfile = fopen(destFile.pathname_.c_str(), "wb");

	if (infile == 0 || outfile == 0)
	{
		if (infile != NULL)
			fclose(infile);
		if (outfile != NULL)
			fclose(outfile);
		return; // error_code( errno, system_category );
	}

	ssize_t sz = 0;
	ssize_t sz_read = 1;
	ssize_t sz_write = 0;

	while (sz_read > 0 && (sz_read = fread(buf, 1, buf_sz, infile)) > 0)
	{
		// Allow for partial writes - see Advanced Unix Programming (2nd Ed.),
		// Marc Rochkind, Addison-Wesley, 2004, page 94
		sz_write = 0;
		do
		{
			if ((sz = fwrite(buf + sz_write, 1, sz_read - sz_write, outfile)) < 0)
			{
				sz_read = sz; // cause read loop termination
				break; //  and error to be thrown after closes
			}
			sz_write += sz;
		} while (sz_write < sz_read);
	}

	fclose(infile);
	fclose(outfile);
#endif
}

void FilePath::CopyContentsTo(FilePath & destDir) const
{
  IL::FilePathList files = IL::FileUtils::listAllFilePathsInDir(pathname_.c_str());
  for (size_t i = 0; i < files.size(); i++)
    files[i].CopyFileTo(destDir);

  IL::FileList dirs = IL::FileUtils::listAllDirsInDir(pathname_.c_str());
  for (size_t i = 0; i < dirs.size(); i++)
  {
    FilePath sourceSubDir(GetChildDirectory(dirs[i].c_str()));
    FilePath destSubDir(destDir.GetChildDirectory(dirs[i].c_str()));
	destSubDir.CreateDirectoriesRecursively();
    sourceSubDir.CopyContentsTo(destSubDir);
  }
}

// Create the directory so that path exists. Returns true if successful or
// if the directory already exists; returns false if unable to create the
// directory for any reason, including if the parent directory does not
// exist. Not named "CreateDirectory" because that's a macro on Windows.
bool FilePath::CreateFolder() const {
#ifdef _WIN32
#ifdef _WIN32_WCE
  FilePath removed_sep(this->RemoveTrailingPathSeparator());
  LPCWSTR unicode = String::AnsiToUtf16(removed_sep.c_str());
  int result = CreateDirectory(unicode, NULL) ? 0 : -1;
  delete [] unicode;
#else
  int result = _mkdir(pathname_.c_str());
#endif  // !WIN32_WCE
#else
  int result = mkdir(pathname_.c_str(), 0777);
#endif  // _WIN32
  if (result == -1) {
    return this->DirectoryExists();  // An error is OK if the directory exists.
  }
  return true;  // No error.
}

// If input name has a trailing separator character, remove it and return the
// name, otherwise return the name string unmodified.
// On Windows platform, uses \ as the separator, other platforms use /.
FilePath FilePath::RemoveTrailingPathSeparator() const {
  return pathname_.EndsWith(kPathSeparatorString)
      ? FilePath(String(pathname_.c_str(), pathname_.GetLength() - 1))
      : *this;
}

// Normalize removes any redundant separators that might be in the pathname.
// For example, "bar///foo" becomes "bar/foo". Does not eliminate other
// redundancies that might be in a pathname involving "." or "..".
void FilePath::Normalize() {
  if (pathname_.c_str() == NULL) {
    pathname_ = "";
    return;
  }
  const char* src = pathname_.c_str();
  char* const dest = new char[pathname_.GetLength() + 1];
  char* dest_ptr = dest;
  memset(dest_ptr, 0, pathname_.GetLength() + 1);

  while (*src != '\0') {
    *dest_ptr++ = *src;
    if (*src != kPathSeparator)
      src++;
    else
      while (*src == kPathSeparator)
        src++;
  }
  *dest_ptr = '\0';
  pathname_ = dest;
  delete[] dest;
}

FilePath FilePath::GetParentDirectory() const
{
	if (IsRootDirectory())
		return *this;
	FilePath temp1 = RemoveTrailingPathSeparator();
	FilePath temp2 = temp1.RemoveFileName();
	return FilePath(String::Format("%s%s", temp2.c_str(), kPathSeparatorString));
}

FilePath FilePath::GetChildDirectory(const String& childName) const
{
	String result;
	if (IsDirectory())
		result = this->pathname_;
	else
		result = RemoveFileName().pathname_;
	return FilePath(String::Format("%s%c%s%c",
			result.c_str(), kPathSeparator, childName.c_str(), kPathSeparator));
}

FilePath FilePath::GetChildFile(const String& childName) const
{
	String name;
	if (IsDirectory())
		name = this->pathname_;
	else
		name = RemoveFileName().pathname_;
	FilePath result = FilePath(String::Format("%s%c%s",
			name.c_str(), kPathSeparator, childName.c_str()));
	return result;
}

String FilePath::GetFileName() const
{
	if (IsDirectory())
		return "";
	FilePath result = RemoveDirectoryName();
	return result.c_str();
}

String FilePath::GetLastDirName() const
{
	if (IsRootDirectory())
		return pathname_;
	if (pathname_ == kPathSeparatorString)
		return pathname_;

	FilePath dir(*this);
	if (!dir.IsDirectory())
	{
		dir = dir.RemoveFileName();
	}
	dir = dir.RemoveTrailingPathSeparator().RemoveDirectoryName();
	return dir.c_str();
}

FilePath FilePath::RenameFileTo(const std::string& newName) const
{
	if (!FileExists())
		return *this;

	FilePath newFullName(GetParentDirectory().GetChildFile(newName.c_str()));

#ifdef _WIN32
	::MoveFileA(pathname_.c_str(), newFullName.c_str());
#else
	::rename(pathname_.c_str(), newFullName.c_str());
#endif

	return newFullName;
}

FilePath FilePath::AddSuffixToFilename(const std::string& suffix) const
{
	std::string newName = GetFileName().c_str() + suffix;
	return RenameFileTo(newName.c_str());
}

FilePath FilePath::RemoveSuffixFromFilename(const std::string& suffix) const
{
	FilePath result = RemoveExtension(suffix.c_str());
	return RenameFileTo(result.GetFileName().c_str());
}



#ifdef _WIN32
long FilePath::GetModificationDateInSeconds() const
{
	FilePath fileToStat(*this);
	if (this->IsDirectory())
	{
		fileToStat = this->RemoveTrailingPathSeparator();
	}

	struct _stat file_stat = {};
	if (_stat(fileToStat.c_str(), &file_stat) != 0)
		return -1;
	return file_stat.st_mtime;
}
#else
long FilePath::GetModificationDateInSeconds() const
{
	FilePath fileToStat(*this);
	if (this->IsDirectory())
	{
		fileToStat = this->RemoveTrailingPathSeparator();
	}

	struct stat file_stat = {};
	if (stat(fileToStat.c_str(), &file_stat) != 0)
		return -1;

	return file_stat.st_mtime;
}
#endif

}  // namespace internal
}  // namespace testing
