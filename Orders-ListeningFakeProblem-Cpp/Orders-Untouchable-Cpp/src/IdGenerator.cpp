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

#include "IdGenerator.h"
#include "Database.h"
#include <sstream>
#include <stdlib.h>

std::string IdGenerator::getOrderId(const std::string& accountId)
{
	Database::touchDatabase();
	std::stringstream string_stream;
	string_stream << ::rand();
	return string_stream.str();
};
