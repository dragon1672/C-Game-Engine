#include "LogManager.h"
#include <fstream>

#ifdef LOG_ON

#define FOOTER "Created By:<br/>Anthony Corbin"

int LogManager::verbosityLevel = 0;//default

void LogManager::changeverbosityLevel(int toSet) {
	verbosityLevel = toSet;
}

std::vector <LogData> LogManager::logList;

LogManager::LogManager(void){}
LogManager::~LogManager(void){}

void LogManager::StringReplace(std::string& str, const std::string& from, const std::string& to) {
	size_t pos = 0;
	do {
		pos = str.find(from, pos);
		if( pos != std::string::npos ) {
			str.replace( pos, from.length(), to);
			pos += to.length();
		}
	} while (pos != std::string::npos);
}
void LogManager::Sanitize(LogData * toClean) {
	toClean->message  = Sanitize(toClean->message);
	toClean->location = Sanitize(toClean->location);
}
std::string LogManager::Sanitize(std::string str) {
	StringReplace( str, "<" , "&lt" );
	StringReplace( str, ">" , "&gt" );
	return str;
}

void LogManager::Log( Severity severity, const char* message, const char * logFile, int logLine, int verbosity) {
	if(verbosityLevel>=verbosity)
		logList.push_back(LogData(severity,logFile,logLine,message,verbosity));//timestamp auto added
}
void LogManager::shutDown() {
	WriteFile();
}
void LogManager::WriteFile() {
	std::ofstream myFile;
	myFile.open("../LogOutput.html");
	
	myFile << "<!DOCTYPE html>" << std::endl << "<html>" 
		<< std::endl << "<head>" << std::endl << "<title>Log File</title>" << std::endl << "</head>"
		<< std::endl << "<body bgcolor = '#FFFFFF' >" << std::endl << "<h2>Log File</h2>";
	myFile << "<table>\n<tr>\n"
		   << "<td><b>Log ID    </b></td>\n"
		   << "<td><b>Severity  </b></td>\n"
		   << "<td><b>Location  </b></td>\n"
		   << "<td><b>Message   </b></td>\n"
		   << "<td><b>TimeStamp </b></td>\n"
		   << "<td><b>Vebosity  </b></td>\n";
	for(unsigned int i = 0; i < logList.size(); i ++) {
		//copying mem so it can be parsed for HTML
		LogData toPrint = logList[i];
		Sanitize(&toPrint);//clean for HTML
		myFile << "<tr style=\" color : ";
		switch (toPrint.severity) {
			case Info:
				myFile << "#0099FF";
				break;
			case Warning:
				myFile << "#FFCC00";
				break;
			case Error:
				myFile << "#FF0000"; 
				break;
			case Severe:
				myFile << "#CC0000"; 
				break;
			default:
				myFile << "#000000";
				break;
		}
		myFile << ";\" >";//end <tr color = "??????">

		myFile <<  "<td>" << i                         << "</td>\n"
				<<  "<td>" << toPrint.severity         << "</td>\n"
				<< "<td>" << toPrint.location.c_str()  << "(" << toPrint.lineNumber << ")" "</td>\n"
				<< "<td>" << toPrint.message.c_str()   << "</td>\n"
				<< "<td>" << toPrint.timestamp         << "</td>\n"
				<< "<td>" << toPrint.verbosity         << "</td>\n";
		myFile << "</tr>\n";
	}
	myFile << "</table>\n";
	myFile << "<center>" << FOOTER << "</center>";
	myFile << "</body>" << std::endl << "</html>";
	myFile.close();
}

#endif