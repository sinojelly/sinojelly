#include "ILFileUtils.h"
#include "ILStringUtils.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctype.h>

#include <sys/stat.h> // stat()

using namespace std;

namespace IL
{

FileUtils::FileUtils()
{
}

FileUtils::~FileUtils()
{
}

FileList FileUtils::listFilesInDirWithSuffix(const std::string& sourceDirectory,
		const std::string& fileSuffix)
{
	FileList result;

	DIR *dir = opendir(sourceDirectory.c_str());
	if (dir == NULL)
		return result;

	struct dirent *entry;
	for(; NULL != (entry = readdir(dir)); )
	{
		FilePath filepath((sourceDirectory + entry->d_name).c_str());
		if (isDir(entry, filepath.c_str()))
			continue;
		if (stringEndsWithCaseInsensitive(entry->d_name, fileSuffix))
			result.push_back(entry->d_name);
	}
    closedir(dir);
    sort(result.begin(), result.end());
	return result;
}

vector<long> FileUtils::getModDatesForFiles(const FilePathList& files)
{
	vector<long> result;
	for (FilePathList::size_type i = 0; i < files.size(); i++)
	{
		result.push_back(files[i].GetModificationDateInSeconds());
	}
	return result;
}

bool FileUtils::isDir(dirent* entry, const char* filePathName) {
#ifdef __CYGWIN__
	struct stat entryStat;
	stat(filePathName, &entryStat);

	return S_ISDIR(entryStat.st_mode);
#elif defined(_MSC_VER)
	struct _stat entryStat;
	_stat(filePathName, &entryStat);
	return (entryStat.st_mode & S_IFDIR)==S_IFDIR;
#elif defined(_WIN32)
	struct stat entryStat;
	stat(filePathName, &entryStat);
	return (entryStat.st_mode & S_IFDIR)==S_IFDIR;
#else
	return (DT_DIR == entry->d_type);
#endif
}

FileList FileUtils::listFilesInDir(const std::string& sourceDirectory)
{
	FileList result;

	DIR *dir = opendir(sourceDirectory.c_str());
	if (dir == NULL)
		return result;

	struct dirent *entry;
	for(; NULL != (entry = readdir(dir)); )
	{
		FilePath filepath((sourceDirectory + entry->d_name).c_str());
		if (stringBeginsWith(entry->d_name, ".")  // skip invisible files
				|| isDir(entry, filepath.c_str()))
			continue;
		result.push_back(entry->d_name);
	}
    closedir(dir);
    sort(result.begin(), result.end());
	return result;
}

FileList FileUtils::listAllFilesInDir(const std::string& sourceDirectory)
{
	FileList result;

	DIR *dir = opendir(sourceDirectory.c_str());
	if (dir == NULL)
		return result;

	struct dirent *entry;
	for(; NULL != (entry = readdir(dir)); )
	{
		FilePath filepath(sourceDirectory + entry->d_name);
		if (isDir(entry, filepath.c_str()))
			continue;
		result.push_back(entry->d_name);
	}
    closedir(dir);
    sort(result.begin(), result.end());
	return result;
}

FileList FileUtils::listDirsInDir(const std::string& sourceDirectory)
{
	const std::string CVS = "CVS";

	FileList result;

	DIR *dir = opendir(sourceDirectory.c_str());
	if (dir == NULL)
		return result;

	struct dirent *entry;
	for(; NULL != (entry = readdir(dir)); )
	{
		FilePath filepath((sourceDirectory + entry->d_name).c_str());
		if (stringBeginsWith(entry->d_name, ".")  // skip invisibles
				|| CVS == entry->d_name) // skip CVS junk
			continue;
		if (isDir(entry, filepath.c_str()))
			result.push_back(entry->d_name);
	}
    closedir(dir);
    sort(result.begin(), result.end());
	return result;
}

FileList FileUtils::listAllDirsInDir(const std::string& sourceDirectory)
{
	const std::string DOT = ".";
	const std::string DOT_DOT = "..";

	FileList result;

	DIR *dir = opendir(sourceDirectory.c_str());
	if (dir == NULL)
		return result;

	struct dirent *entry;
	for(; NULL != (entry = readdir(dir)); )
	{
		FilePath filepath(sourceDirectory + entry->d_name);
		if (DOT == entry->d_name || DOT_DOT == entry->d_name)
			continue;
		if (isDir(entry, filepath.c_str()))
			result.push_back(entry->d_name);
	}
    closedir(dir);
    sort(result.begin(), result.end());
	return result;
}

FilePathList FileUtils::listFilePathsInDir(const std::string& sourceDirectory)
{
	FileList localNames = listFilesInDir(sourceDirectory);
	FilePathList absoluteNames;

	for (FileList::size_type i = 0; i < localNames.size(); i++)
	{
		string absName = sourceDirectory;
		if (!stringEndsWith(absName, PATH_SEP_STRING))
			absName += PATH_SEP_STRING;
		absName += localNames[i];
		absoluteNames.push_back(FilePath(absName.c_str()));
	}
	return absoluteNames;
}

FilePathList FileUtils::listAllFilePathsInDir(const std::string& sourceDirectory)
{
	FileList localNames = listAllFilesInDir(sourceDirectory);
	FilePathList absoluteNames;

	for (FileList::size_type i = 0; i < localNames.size(); i++)
	{
		string absName = sourceDirectory;
		if (!stringEndsWith(absName, PATH_SEP_STRING))
			absName += PATH_SEP_STRING;
		absName += localNames[i];
		absoluteNames.push_back(FilePath(absName.c_str()));
	}
	return absoluteNames;
}

bool FileUtils::fileListContains(const FileList& fileList,
		const std::string& nameToFind)
{
	for (FileList::size_type i = 0; i < fileList.size(); i++)
	{
		if (nameToFind == fileList[i])
			return true;
	}
	return false;
}

std::string FileUtils::fileListAsString(const FileList& fileList)
{
	string fileNames;
	for (FileList::size_type i = 0; i < fileList.size(); i++)
	{
		fileNames += fileList[i];
		fileNames += ", ";
	}
	return fileNames;
}

void FileUtils::makeSnapshot(FilePath& labDir, long timestamp)
{
	// timestamp is in seconds, but generate the directory name as milliseconds.
	// We don't want to mess with int64, since some compiler may not support that, so append
	// string instead of multiplying by 1000.
	//  data/editing.history/123456000/src
	//  data/editing.history/123456000/test

	FilePath snapshotDir(labDir.GetChildDirectory("data")
			.GetChildDirectory("editing.history")
			.GetChildDirectory((numToString(timestamp)+"000").c_str()));


	if (!snapshotDir.CreateDirectoriesRecursively())
		throw string("can't create ") + snapshotDir.c_str();

	FilePath labSrc = labDir.GetChildDirectory("src");
	FilePath srcInSnap = snapshotDir.GetChildDirectory("src");
	copyEntireDirectoryFromTo(labSrc, srcInSnap);
	suffixAllFilesIn(srcInSnap);

	FilePath labTest = labDir.GetChildDirectory("test");
	FilePath testInSnap = snapshotDir.GetChildDirectory("test");
	copyEntireDirectoryFromTo(labTest, testInSnap);
	suffixAllFilesIn(testInSnap);
}

void FileUtils::suffixAllFilesIn(IL::FilePath& srcInSnap)
{
	FilePathList files = FileUtils::listAllFilePathsInDir(srcInSnap.c_str());
	for (FilePathList::size_type i = 0; i < files.size(); i++)
		files[i].AddSuffixToFilename(".x");
}

void FileUtils::unsuffixAllFilesIn(IL::FilePath& srcInSnap)
{
	FilePathList files = FileUtils::listAllFilePathsInDir(srcInSnap.c_str());
	for (FilePathList::size_type i = 0; i < files.size(); i++)
		files[i].RemoveSuffixFromFilename(".x");
}

void FileUtils::copyEntireDirectoryFromTo(FilePath& sourceDir, FilePath& destDir)
{
	destDir.CreateDirectoriesRecursively();
	sourceDir.CopyContentsTo(destDir);
}

const std::string ILConfig::TESTING_HISTORY = "TESTING_HISTORY";
const std::string ILConfig::EDITING_HISTORY = "EDITING_HISTORY";
const std::string ILConfig::ARCHIVE_NAME = "ARCHIVE_NAME";
const std::string ILConfig::ARCHIVE_DIRS = "ARCHIVE_DIRS";

ILConfig::ILConfig(const FilePath& fileIn)
	: file(fileIn)
{ }

ILConfig::~ILConfig()
{ }

std::string ILConfig::extractProperty(const std::string& propName)
{
	if (properties.size() == 0)
		readFile();
	return properties[propName];
}

bool ILConfig::extractBoolProperty(const std::string& propName)
{
	string prop = extractProperty(propName);
	return (prop == "1");
}

void ILConfig::readFile()
{
	string line;
	ifstream infile(file.c_str());

	if (!infile.is_open())
		throw string("can't read file ") + file.c_str();

	while (!infile.eof())
	{
		getline(infile, line);
		for (size_t i = 0; i < line.length(); i++)
			if (isspace(line[i]) || iscntrl(line[i]))
				line[i] = ' ';

		if (line.length() == 0 || line[0] == '#'
				|| !stringContains(line, "="))
			continue;
		int index = line.find('=');

		string key = line.substr(0, index);
		key = trimSpaces(key);

		string value = line.substr(index + 1);
		value = trimSpaces(value);
		properties[key] = value;
	}
	infile.close();
}

void FileUtils::addFilesWithSuffixInDir(FilePathList& pathList,
		const FilePath& dir, const std::string& suffix)
{
	FileList fileList = FileUtils::listFilesInDirWithSuffix(dir.c_str(), suffix);
	for (FileList::size_type i = 0; i < fileList.size(); i++)
	{
		FilePath projectFileToAdd(dir.GetChildFile(fileList[i].c_str()));
		pathList.push_back(projectFileToAdd);
	}
}

IL::FilePath FileUtils::getDataDirOf(const IL::FilePath& currentDir)
{
	IL::FilePath result;
	string curDir = currentDir.c_str();

	if (stringEndsWithCaseInsensitive(curDir, PATH_SEP_STRING + "bin" + PATH_SEP_STRING)
		|| stringEndsWithCaseInsensitive(curDir, PATH_SEP_STRING + "build" + PATH_SEP_STRING)
		|| stringEndsWithCaseInsensitive(curDir, "\\VS2008\\")
		|| stringEndsWithCaseInsensitive(curDir, "\\VS2005\\"))
	{
		result = currentDir.GetParentDirectory();
	}
	else
	{
		result = currentDir;
	}
	return result.GetChildDirectory("data");
}

FilePathList FileUtils::getFilesForModDates(const FilePath& labDir)
{
	FilePathList result;

	addFilesWithSuffixInDir(result, labDir, ".project");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("VS2005"), ".ncb");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("VS2008"), ".ncb");

	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("build"), ".o");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("src"), ".h");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("src"), ".cpp");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("test"), ".h");
	addFilesWithSuffixInDir(result, labDir.GetChildDirectory("test"), ".cpp");
	return result;
}

} // namespace IL
