#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;
 ostream& upper_and_oct( ostream& os) {
    os.setf( ios::uppercase);
    os.setf( ios::oct,  ios::basefield);
    return os;
}

 ostream& lower_and_replace_space( ostream& os) {
    os.unsetf( ios::uppercase);
    return os;
}

 ostream& hex_no_space( ostream& os) {
    os.setf( ios::hex,  ios::basefield);
    os.unsetf( ios::showbase |  ios::uppercase);
    os.fill(' ');
    return os;
}

int main() {
    int example_numbers[] = { 255, 16, 42, 1024 };
    const int count = sizeof(example_numbers) / sizeof(example_numbers[0]);
     string example_string = "Hello World";

     cout << "Custom manipulator examples:\n";

     cout << "Uppercase and OCT: ";
     cout << upper_and_oct;
    for (char c : example_string) {
        if ( isdigit(c)) {
             cout <<  oct << static_cast<int>(c) << " ";
        }
        else {
             cout << static_cast<char>( toupper(c));
        }
    }
     cout <<  endl;

     cout << "Lowercase and replace spaces: ";
     cout << lower_and_replace_space;
    for (char c : example_string) {
        if (c == ' ') {
             cout << '#';
        }
        else {
             cout << static_cast<char>( tolower(c));
        }
    }
     cout <<  endl;

     cout << "HEX no spaces: ";
     cout << hex_no_space;
    for (int i = 0; i < count; ++i) {
         cout << example_numbers[i];
    }
     cout <<  endl;

    return 0;
}
