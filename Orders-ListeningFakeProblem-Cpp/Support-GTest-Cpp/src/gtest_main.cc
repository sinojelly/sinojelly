// Copyright 2006, Google Inc.
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

#include "ILTestListener.h"
#include "ILFileUtils.h"
#include "ILStringUtils.h"

#include <gtest/gtest.h>
#include <gtest/internal/gtest-filepath.h>

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;
using testing::internal::FilePath;
using IL::ILConfig;
using IL::FileUtils;
using IL::FileList;
using IL::PATH_SEP_STRING;

typedef std::vector<std::string> FileList;

const std::string IL_CONFIG = ".ilconfig";

bool findLabDirectoriesFromCurrentDir(FilePath & labDirOut,
		bool* shouldWriteEditingHistory,
		bool* shouldWriteTestHistory)
{
	FilePath curDir = FilePath::GetCurrentDir();
	bool foundLabDir = false;

	*shouldWriteEditingHistory = false;
	*shouldWriteTestHistory = false;

	while (!foundLabDir)
	{
		FileList files = FileUtils::listAllFilesInDir(curDir.c_str());

		if (FileUtils::fileListContains(files, IL_CONFIG))
		{
			foundLabDir = true;
			ILConfig config(FilePath((curDir.c_str() + PATH_SEP_STRING
					+ IL_CONFIG).c_str()));
			*shouldWriteTestHistory = config.extractBoolProperty(ILConfig::TESTING_HISTORY);
			*shouldWriteEditingHistory = config.extractBoolProperty(ILConfig::EDITING_HISTORY);
		}

		if (!foundLabDir)
		{
			curDir = curDir.GetParentDirectory();
			if (curDir.IsRootDirectory())
			{
				return false;
			}
		}
	}
	if (foundLabDir)
	{
		labDirOut = curDir;
	}
	return true;
}


static void createDataDirIfNeeded(const FilePath & labDir)
{
    FilePath dataDir = labDir.GetChildDirectory("data");
    if(!dataDir.DirectoryExists())
    {
        dataDir.CreateFolder();
    }
}

const char CR = (char) 13;
const char LF = (char) 10;

static void writeProjectHistoryIfNeeded(const FilePath& labDir, long testTimestamp)
{
    FilePath projectHistoryFile = labDir.GetChildDirectory("data").GetChildFile("project.history");
    if (!projectHistoryFile.FileExists())
    {
		ofstream output(projectHistoryFile.c_str());

		long projectStartTimeInSecs = 0;

		IL::FilePathList pathList = FileUtils::getFilesForModDates(labDir);
		std::vector<long> timestamps = FileUtils::getModDatesForFiles(pathList);

		for (int i = 0; i < timestamps.size(); i++)
		{
			if (timestamps[i] > testTimestamp)
				continue;
			if (timestamps[i] > projectStartTimeInSecs)
			{
				projectStartTimeInSecs = timestamps[i];
			}
		}
		if (projectStartTimeInSecs == 0)
			projectStartTimeInSecs = testTimestamp;

		output << projectStartTimeInSecs << "000" << CR << LF;
		output.close();
    }
}

static std::string testingHistoryPathname(const FilePath& labDir)
{
    FilePath dataDir = labDir.GetChildDirectory("data");
    string result = dataDir.c_str() + string("testing.history");
	return result;
}

extern "C" int main(int argc, char **argv)
{
	std::cout << "Running main() from gtest_main.cc\n";
	testing::InitGoogleTest(&argc, argv);

	FilePath labDir;

	bool shouldWriteEditingHistory = false;
	bool shouldWriteTestHistory = false;

	if (findLabDirectoriesFromCurrentDir(labDir, &shouldWriteEditingHistory,
			&shouldWriteTestHistory))
	{
		long timestamp = (long) time(NULL);

		if (shouldWriteEditingHistory)
		{
			try
			{
				FileUtils::makeSnapshot(labDir, timestamp);
			}
			catch(const std::string& str)
			{
				cout << "exception string = '" << str << "'" << endl;
			}
			catch(const std::exception& ex)
			{
				cout << "exception.what = '" << ex.what() << "'" << endl;
			}
		}
		if (shouldWriteTestHistory)
		{
			createDataDirIfNeeded(labDir);
			writeProjectHistoryIfNeeded(labDir, timestamp);
			std::string outPath = testingHistoryPathname(labDir);
			ofstream* output = new ofstream(outPath.c_str(), ios_base::app);
			::testing::UnitTest::GetInstance()->AddListener(
				new IL::TestEventListener(output, timestamp));
		}
	}
	return RUN_ALL_TESTS();
}
