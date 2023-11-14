#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> splitString(const string& input, char delimiter) {
	vector<string> tokens;
	istringstream tokenStream(input);
	string token;

	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

class Field {
private:
	string name;
	string type;
	int size;
	int usages;
	bool offloaded = true;
public:
	Field(string t, string n, int s) {
		type = t;
		name = n;
		size = s;
		usages = 0;
	};

	void set_field_size(int new_size) { size = new_size; }

	int get_field_size() { return size; }

	int get_usages() const { return usages; }

	string get_field_name() { return name; }

	string get_field_type() { return type; }

	void inc_usage() { usages++; }

	void do_not_offload() { offloaded = false; }

	bool is_offloaded() { return offloaded; }
};

bool compareFields(const Field a, const Field& b) {
	return a.get_usages() < b.get_usages();
}


class Class {
private:
	int size;
	string name;
	vector<Field> fields;
	vector<Field> safed_fields;
	vector<string> copies;
	bool offload_flag = false;

	bool need_offload() {
		for (Field f : fields) {
			if (f.is_offloaded()) return true;
		}
		return false;
	}

	int get_fields_size(vector<Field> new_fields) {
		int sum = 0;
		for (Field& f : new_fields) {
			sum += f.get_field_size();
		}
		return sum;
	}

public:
	Class(string n) {
		name = n;
		size = 0;
	}

	bool get_offload_flag() { 
		return offload_flag;
	}

	void set_offload_flag() {
		offload_flag = true;
	}

	void set_class_size(int new_size) {
		size = new_size;
	}

	void set_fields(vector<Field> new_fields) {
		fields = new_fields;
	}

	string get_type_field(string field_name) {
		for (Field& f : fields) {
			if (f.get_field_name() == field_name) return f.get_field_type();
		}
		cout << "Cann't find field with this name" << endl;
		exit(0);
	}

	string get_class_name() { return name; }

	int get_class_size() { return size; }

	vector<Field>& get_fields() { return fields; }

	void add_field(Field f) {
		fields.push_back(f);
		size += f.get_field_size();
	}

	void add_copy(string copy_name) {
		copies.push_back(copy_name);
	}

	bool is_primitive() {
		return (name == "null" || name == "byte" || name == "int" || name == "short" || name == "float" || name == "address");
	}

	void class_info() {
		cout << "Name: " << name << " " << "Size: " << size << endl;
		for (auto f : fields) {
			cout << f.get_field_name() << ": " << f.get_field_size() << endl;
		}
		cout << endl;
	}

	void inc_field_usage(string field_name) {
		for (Field& field : fields) {
			if (field.get_field_name() == field_name) {
				field.inc_usage();
				return;
			}
		}
		cout << "Cann't find field with this name to increment" << endl;
		exit(0);
	}

	void print_non_offloaded_fields() {
		for (Field f : fields) {
			if (!f.is_offloaded()) cout << name << " " << f.get_field_name() << endl;
		}
	}

	void reverse_class_fields() {
		reverse(fields.begin(), fields.end());
	}

};

class Classes {
public:
	void add_class(Class c) {
		classes.push_back(c);
	}

	int get_count_classes() {
		return classes.size();
	}

	Class& get_class(string name) {
		if (name.back() == '*') name = "address";
		for (Class& c : classes) {
			if (c.get_class_name() == name) return c;
		}
		return classes[0];	//NULL
	}

	Classes() {
		Class _null = Class("null");
		Class _byte = Class("byte");
		Class _short = Class("short");
		Class _integer = Class("int");
		Class _float = Class("float");
		Class _address = Class("address");

		_null.add_field(Field("null", "-", 0));
		_byte.add_field(Field("byte", "-", 1));
		_short.add_field(Field("short", "-", 2));
		_integer.add_field(Field("int", "-", 4));
		_float.add_field(Field("float", "-", 8));
		_address.add_field(Field("address", "-", 8));

		classes.push_back(_null);
		classes.push_back(_byte);
		classes.push_back(_short);
		classes.push_back(_integer);
		classes.push_back(_float);
		classes.push_back(_address);
	};


	void debug_log() {
		for (Class c : classes) {
			c.class_info();
		}
	}

	void print_non_offloaded_fields() {
		for (Class& c : classes) {
			c.print_non_offloaded_fields();
		}
	}

	vector<Class> get_classes() {
		return classes;
	}

	int get_class_size(Class c) {
		for (Class& _c : classes) {
			if (_c.get_class_name() == c.get_class_name()) {
				int sum = 0;
				for (Field f : _c.get_fields()) {
					string name = f.get_field_type();
					Class a = get_class(name);
					sum += a.get_class_size();
				}
				return sum;
			}
		}
	}

	//vector<Class> get_classes() {
	//	return classes;
	//}

	void set_class_size(string name, int new_size) { 
		for (Class& c : classes) {
			if (c.get_class_name() == name) {
				c.set_class_size(new_size);
			}
		}
	}

	void set_class_fields(vector<Field> new_fields, Class _c) {
		for (Class& c : classes) {
			if (c.get_class_name() == _c.get_class_name()) {
				c.set_fields(new_fields);
			}
		}
	}

	void reverse_fields(Class& _c) {
		for (Class& c : classes) {
			if (c.get_class_name() == _c.get_class_name()) {
				c.reverse_class_fields();
			}
		}
	}

	void need_to_offload(Class _c) {
		for (Class& c : classes) {
			if (_c.get_class_name() == c.get_class_name()) {
				c.set_offload_flag();
			}
		}
	}

private:
	vector<Class> classes;
};


void dynamic(Class& _class, Classes& classes, int max_size) {
	vector<vector<int>> dp(_class.get_fields().size() + 1, vector<int>(max_size));

	int size = classes.get_class_size(_class);
	for (int i = 0; i < max_size; i++) {
		dp[0][i] = 0;
	}

	if (size > max_size) {
		max_size -= 8;

		classes.need_to_offload(_class);
		//cout << "Add offload\n" << size << " " << max_size << endl;
	}
	else {


		return;
	}

	classes.need_to_offload(_class);

	for (int i = 1; i < _class.get_fields().size() + 1; i++) {
		for (int x = 0; x < max_size + 1; x++) {

			pair<int, int> size_usages = make_pair(_class.get_fields()[i - 1].get_field_size(), _class.get_fields()[i - 1].get_usages());
			int size = size_usages.first;
			int usages = size_usages.second;

			if (x - size >= 0) dp[i][x] = max(dp[i - 1][x], dp[i - 1][x - size] + usages);
			else dp[i][x] = dp[i - 1][x];

		}
	}

	//cout << dp[fields.size() - 1][max_size - 1] << endl;
	//for (int i = 0; i < _class.get_fields().size(); i++) {
	//	for (int x = 0; x < max_size + 1; x++) {
	//		cout << dp[i][x] << " ";
	//	}
	//	//cout << endl;
	//}


	int i = _class.get_fields().size();
	int x = max_size;

	vector<Field> new_fields;

	while (i > 0 && x > 0) {
		pair<int, int> size_usages = make_pair(_class.get_fields()[i - 1].get_field_size(), _class.get_fields()[i - 1].get_usages());
		int size = size_usages.first;
		int usages = size_usages.second;


		if (x - size >= 0 && dp[i][x] == dp[i - 1][x - size] + usages) {
			//cout << "Class: " << _class.get_class_name() << " Field: " << _class.get_fields()[i - 1].get_field_name() << " " << _class.get_fields()[i - 1].get_field_type() << endl;
			new_fields.push_back(_class.get_fields()[i - 1]);
			x -= size;
		}

		i--;
	}
	reverse(new_fields.begin(), new_fields.end());

	auto it = new_fields.begin();
	while (it != new_fields.end()) {
		if (it->get_usages() == 0) {
			it = new_fields.erase(it);
		}
		else {
			++it;
		}
	}

	classes.set_class_fields(new_fields, _class);
	int new_size = 0;


	for (Field f : new_fields) {
		new_size += f.get_field_size();
	}

	classes.set_class_size(_class.get_class_name(), new_size + 8);

	cout << endl;

	return;
}



int main() {

	string filename_in = "1.txt";
	string filename_out = "1o.txt";

	ifstream file_in(filename_in);


	int count_classes, capacity, predictions;
	bool shouldAlign;

	string line;
	getline(file_in, line);
	istringstream iss(line);
	iss >> count_classes >> capacity >> predictions;

	getline(file_in, line);
	shouldAlign = true ? line == "True" : false;

	Classes classes;

	for (int i = 0; i < count_classes; i++) {
		string data;
		getline(file_in, data);
		vector<string> fields = splitString(data, ',');
		pair<string, string> p = make_pair(splitString(fields[0], ':')[0], splitString(fields[0], ':')[1]);

		string name = p.first;
		fields[0] = p.second;

		Class c = Class(name);
		for (string f : fields) {
			f = f.substr(2, f.length() - 3);
			pair<string, string> type_name = make_pair(splitString(f, ' ')[0], splitString(f, ' ')[1]);

			string type = type_name.first;
			string name = type_name.second;
			if (name.back() == '>') name = name.substr(0, name.length() - 1);


			if (!classes.get_class(type).is_primitive()) {
				classes.get_class(type).add_copy(name);
			}
			Field field = Field(type, name, classes.get_class(type).get_class_size());


			c.add_field(field);

		}
		classes.add_class(c);

	}

	//classes.debug_log();

	for (int j = 0; j < predictions; j++) {
		string data;
		getline(file_in, data);

		vector<string> tokens = splitString(data, '.');
		for (int i = 1; i < tokens.size(); i++) {
			string _class = tokens[i - 1];
			string field = tokens[i];
			classes.get_class(_class).inc_field_usage(field);
			tokens[i] = classes.get_class(_class).get_type_field(field);
		}

	}

	for (Class& c : classes.get_classes()) {
		dynamic(c, classes, capacity);
	}

	classes.print_non_offloaded_fields();

	for (Class a : classes.get_classes()) {
		if (a.is_primitive()) continue;
		cout << a.get_class_name() << ": ";
		for (Field f : a.get_fields()) {
			cout << "<"<<f.get_field_type()<< " " << f.get_field_name()<<"> " << " ";
		}
		
		if (a.get_offload_flag()) cout << "Address offload";
		cout << endl;
	}

	int i = 0;

}
