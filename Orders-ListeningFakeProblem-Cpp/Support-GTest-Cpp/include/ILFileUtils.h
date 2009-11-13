/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <gtest/internal/gtest-filepath.h>
#include <string>
#include <vector>
#include <map>

#if defined(_WIN32) && !defined(__MINGW32__)
	#include "win32Dirent.h"
#else
	#include <dirent.h>
#endif

namespace IL
{

using testing::internal::FilePath;

typedef std::vector<std::string> FileList;
typedef std::vector<FilePath> FilePathList;

#ifdef _WIN32
	const char PATH_SEP = '\\';
	const std::string PATH_SEP_STRING = "\\";
#else
	const char PATH_SEP = '/';
	const std::string PATH_SEP_STRING = "/";
#endif

class FileUtils
{
public:
	FileUtils();
	~FileUtils();

	// Lists only files, skips directories.
	static FileList listFilesInDirWithSuffix(
			const std::string& sourceDirectory,
			const std::string& fileSuffix);

	static std::vector<long> getModDatesForFiles(const FilePathList& files);

	// Lists only visible files, skips directories
	static FileList listFilesInDir(const std::string& sourceDirectory);

	// Lists all files, skips directories
	static FileList listAllFilesInDir(const std::string& sourceDirectory);

	// lists all directories, skips files.
	static FileList listAllDirsInDir(const std::string& sourceDirectory);

	// list dirs, skips files, skips invisible directories,
	// skips CVS directories
	static FileList listDirsInDir(const std::string& sourceDirectory);

	// Lists only visible files, skips directories
	static FilePathList listFilePathsInDir(
			const std::string& sourceDirectory);

	// Lists all files, skips directories
	static FilePathList listAllFilePathsInDir(
			const std::string& sourceDirectory);

	static bool fileListContains(const FileList& fileList,
			const std::string& nameToFind);

	static std::string fileListAsString(const FileList& fileList);

	// writes snapshot of src and test directories, replacing existing
	// snapshot if that exists.
	static void makeSnapshot(FilePath& labDir, long timestamp);

	static void suffixAllFilesIn(FilePath& srcInSnap);
	static void unsuffixAllFilesIn(FilePath& srcInSnap);

	static void copyEntireDirectoryFromTo(FilePath& sourceDir, FilePath& destDir);

	static IL::FilePath getDataDirOf(const FilePath& currentDir);

	static void addFilesWithSuffixInDir(FilePathList& pathList,
			const FilePath& dir, const std::string& suffix);

	static FilePathList getFilesForModDates(const FilePath& labDir);

private:
	static bool isDir(dirent* entry, const char* filePathName);
};

class ILConfig
{
public:
	static const std::string TESTING_HISTORY;
	static const std::string EDITING_HISTORY;
	static const std::string ARCHIVE_NAME;
	static const std::string ARCHIVE_DIRS;

	ILConfig(const FilePath& file);
	virtual ~ILConfig();

	std::string extractProperty(const std::string& propName);

	bool extractBoolProperty(const std::string& propName);

private:
	std::map<std::string, std::string> properties;
	FilePath file;

	void readFile();
};

}  // namespace IL

#endif
