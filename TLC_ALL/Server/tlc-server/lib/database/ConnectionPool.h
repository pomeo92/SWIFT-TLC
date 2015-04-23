/* Copyright (c) 2012 BDT Media Automation GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ConnectionPool.h
 *
 *  Created on: Feb 26, 2014
 *      Author: Sam Chen
 */
#pragma once
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/exception.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include "stdafx.h"

using namespace sql;
class ConnectionPool
{
public:
	ConnectionPool(int maxSize=40);

	virtual
	~ConnectionPool(void);

	Connection *
	GetConnection();

	void
	ReleaseConnection(Connection * conn);

private:
	Connection *
	CreateConnection();
	Connection *
	CreateConnection(const string& passwd, bool bLogErr = true);

	void
	TerminateConnection(Connection * conn);

	void
	Init(int initialSize);

    void
	Destroy();

private:
	boost::mutex mutex_;
	Driver * driver_;
	deque<Connection *> connections_;
	ConnectOptionsMap connectionProperties_;
	int curSize_;
    int maxSize_;
};

