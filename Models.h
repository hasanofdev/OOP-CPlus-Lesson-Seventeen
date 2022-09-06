#pragma once

class User {
	int _id;
	string _username;
	string _password;
	string _name;
	string _surname;

public:
	User() { _id = 0; }

	User(int id, string username, string password, string name, string surname) {
		_id = id;
		set_username(username);
		set_password(password);
		set_name(name);
		set_surname(surname);
	}

	void set_username(string username) {
		if (username.size() < 6)
			throw new NullArgumentException("Username is shorter than 6 characters!");
		if (96 < int(username[0]) && int(username[0]) < 123)
			throw new NullArgumentException("The first character must be uppercase!");

		_username = username;
	}

	void set_password(string password) {
		if (password.size() < 6)
			throw new NullArgumentException("Password is shorter than 6 characters!");

		_password = password;
	}

	void set_name(string name) {
		if (name.size() < 3)
			throw new NullArgumentException("Name is shorter than 3 characters!");

		_name = name;
	}

	void set_surname(string surname) {
		if (surname.size() < 4)
			throw new NullArgumentException("Surname is shorter than 4 characters!");

		_surname = surname;
	}

	void show() {
		cout << "Id: " << _id << endl
			<< "Username: " << _username << endl
			<< "Passowrd: " << _password << endl
			<< "Name: " << _name << endl
			<< "Surname " << _surname << endl;
	}

	int get_id() const { return _id; }

	string get_username() const { return _username; }

	string get_password() const { return _password; }

	string get_name() const { return _name; }

	string get_surname()const { return _surname; }

	bool operator==(User other) {
		if (other._id == _id)
			if (other._username == _username)
				if (other._password == _password)
					if (other._name == _name)
						if (other._surname == _surname)
							return true;
		return false;
	}

	User& operator=(const User& other) {
		_id = other._id;
		_username = other._username;
		_password = other._password;
		_name = other._name;
		_surname = other._surname;

		return *this;
	}
};

class Database {
	User* users;
	int user_count;
public:
	static int id;

	Database() { user_count = 0; }

	void AddUser(User& user) {
		for (size_t i = 0; i < user_count; i++)
		{
			if (users[i].get_username() == user.get_username())
				throw new DatabaseException("Username Already Exists!");
		}
		User* temp = new User[user_count + 1]{};

		for (size_t i = 0; i < user_count; i++)
			temp[i] = users[i];

		temp[user_count++] = user;
		delete[] users;
		users = temp;
	}

	User* GetUserByUsername(string username) {
		for (size_t i = 0; i < user_count; i++)
		{
			if (users[i].get_username() == username)
				return &users[i];
		}

		throw new DatabaseException("User not found!");
	}

	void updateUser(User& olduser, const User& newuser) {
		for (size_t i = 0; i < user_count; i++)
		{
			if (users[i] == olduser) {
				users[i] = newuser;
				return;
			}
		}
	}

	Database& operator=(const Database& other) {
		User* temp = new User[other.user_count]{};
		for (size_t i = 0; i < other.user_count; i++)
		{
			temp[i] = other.users[i];
		}

		delete[] users;
		users = temp;

		this->user_count = other.user_count;

		return *this;
	}

	~Database()
	{
		delete[] users;
		user_count = 0;
	}
};

int Database::id = 0;

class Registration {
public:
	Database _database;
	Registration(const Database& database) {
		_database = database;
	}

	void signIn(string username, string password) {
		if (_database.GetUserByUsername(username)->get_password() == password)
			cout << "Succesfuly Login!" << endl;
		else
			throw new DatabaseException("Username or Password Incorrect!");
	}

	void signUp(string username, string password, string name, string surname) {
		User* user = new User(Database::id++, username, password, name, surname);
		_database.AddUser(*user);
	}
};

class StartUp {
public:
	static void Start() {

		try
		{
			User* user = new User(0, "Elshad", "Hasanov", "asdsdf", "sdfsdf");
			User* user2 = new User(0, "Eslshad", "Hasanov", "asdsdf", "sdfsdf");
			Database database;
			database.AddUser(*user);

			Registration twitter(database);

			twitter.signIn("Elshad", "Hasanov");
			twitter.signUp("Elxans", "Hasanov", "sadfsdf", "sdfsf");

			twitter._database.GetUserByUsername("Elxans")->show();

		}
		catch (Exception* ex)
		{
			ex->what();
		}
	}
};