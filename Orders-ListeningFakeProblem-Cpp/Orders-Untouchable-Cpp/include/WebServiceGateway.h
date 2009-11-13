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

#ifndef WEB_SERVICE_GATEWAY_H_
#define WEB_SERVICE_GATEWAY_H_

#include <map>
#include <string>

class WebServiceGateway
{
public:
	virtual double execute(const std::map<std::string, std::string>& parameters);
};

#endif

