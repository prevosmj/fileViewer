#include "fileDir.h"
using namespace std;

void fileDir::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    system(clear_command);

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  go  back  open  quit\n";
    cout << short_separator << endl;
    for (const auto& p : buffer_.anchors())
        cout << p.first << " " << p.second << endl;
}

void fileDir::execute_command(char command, bool& done)
{
    switch (command) {
    case 'n': {
        buffer_.move_to_next_page();
        break;
    }

    case 'o': {
        cout << "file name: ";
        string file_name;
        cin >> file_name;
        back.push_back(file_name);
        if (!buffer_.open(file_name))
            error_message_ = "Could not open " + file_name;
        break;
    }

    case 'b': {
        if (back.size() > 1)
        {
            string s = *(back.end() - 2);
            back.pop_back();
            if (!buffer_.open(s))
                error_message_ = "Could not open " + s;
            break;
        }
        else
        {
            error_message_ = "Cannot go back any farther";
            break;
        }
    }

    case 'g': {
        cout << "anchor number: ";
        int chosen_anchor;
        cin >> chosen_anchor;
        map<int, std::string> m;
        m = buffer_.anchors();
        string g = m[chosen_anchor];
        back.push_back(g);
        if (!buffer_.open(g))
            error_message_ = "Could not open " + g;
        break;
    }
    case 'p': {
        buffer_.move_to_previous_page();
        break;
    }

    case 'q': {
        done = true;
        break;
    }
    }
}

void fileDir::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);

    cout << "Window width? ";
    cin >> window_width_;
    cin.get(); // '\n'
    cout << '\n';
    buffer_.set_window_width(window_width_);


    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}


