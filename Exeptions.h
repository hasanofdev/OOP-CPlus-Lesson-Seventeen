#pragma once
struct DateTime {
	short year;
	short month;
	short day;
	short hour;
	short min;
	short sec;

	DateTime()
	{

		time_t now;
		struct tm nowLocal;
		now = time(NULL);
		nowLocal = *localtime(&now);

		year = nowLocal.tm_year + 1900;
		month = nowLocal.tm_mon + 1;
		day = nowLocal.tm_mday;
		hour = nowLocal.tm_hour;
		min = nowLocal.tm_min;
		sec = nowLocal.tm_sec;
	}

	void to_string() {
		cout << day << "." << month << "." << year << "  " << hour << ":" << min << ":" << sec << endl;
	}
};

class Exception {
protected:
	string text;
	size_t line;
	string source;
	DateTime time;


public:
	Exception(string text, size_t line,string source):text(text),line(line),source(source){}

	virtual void what() {
		cout << "Ex: " << text << endl
			<< "Line: " << line << endl
			<< "Source: " << source << endl
			<< "Time: ";
		time.to_string();
		cout << endl;
	}
};

class DatabaseException :public Exception {
	string message  = "Username already exists!";

public:
	DatabaseException() = default;

	DatabaseException(string message) :Exception("DatabaseException", __LINE__, __FILE__) {
		this->message = message;
	}
	
	void what() override {
		cout << "Message: " << message << endl
			<< "Ex: " << text << endl
			<< "Line: " << line << endl
			<< "Source: " << source << endl
			<< "Time: ";
		time.to_string();
		cout << endl;
	}
};

class NullArgumentException : public Exception {
	string message;
public:
	NullArgumentException(string message) :Exception("NullArgumentException", __LINE__, __FILE__) {
		this->message = message;
	}

	void what() override {
		cout << "Message: " << message << endl
			<< "Ex: " << text << endl
			<< "Line: " << line << endl
			<< "Source: " << source << endl
			<< "Time: ";
		time.to_string();
		cout << endl;
	}
};
