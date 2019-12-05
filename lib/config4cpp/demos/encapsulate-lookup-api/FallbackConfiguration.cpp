//----------------------------------------------------------------------
// WARNING: This file was generated by config2cpp. Do not edit.
//----------------------------------------------------------------------

#include "FallbackConfiguration.h"





//--------
// Define the singleton object
//--------
FallbackConfiguration FallbackConfiguration::s_singleton;


FallbackConfiguration::FallbackConfiguration()
{
	m_schema[0] = "host = string";
	m_schema[1] = "port = int";
	m_schema[2] = "timeout = durationSeconds";
	m_schema[3] = 0;

	m_str << "#-------------------------------------------------";
	m_str << "----------------------\n";
	m_str << "# File:        FallbackConfiguration.cfg\n";
	m_str << "#\n";
	m_str << "# Description: Fallback configuration values.\n";
	m_str << "#-------------------------------------------------";
	m_str << "----------------------\n";
	m_str << "\n";
	m_str << "host = exec(\"hostname\", \"localhost\");\n";
	m_str << "port = \"12345\";\n";
	m_str << "timeout = \"30 seconds\";\n";
	m_str << "";
}





FallbackConfiguration::~FallbackConfiguration()
{
	// Nothing to do
}

