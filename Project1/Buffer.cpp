#include "Buffer.h"

using namespace std;

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
        if (i < v_lines_.size())
            cout << std::setw(6) << i + 1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string& new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file)
        return false;

    v_lines_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.
    anchor_map_.clear();

    string line = "";
    string total = "";
    stringstream ss;
    int anchoridx = 1;
    bool break_new;
    bool break_para = false;
    bool first = true;
    string anchoridxstr;

    while (!file.eof())
    { 
        break_new = false;

        while ((total.size() + line.size() + 1 /*to account for the space*/) < window_width_)
        {
            if (break_para == true)
            {
                break_para = false;
                break;
            }

            file >> line;

            if (line == "<a")
            {
                file >> line;
                anchor_map_[anchoridx] = line;
                file >> line;
                ss << anchoridx;
                ss >> anchoridxstr;
                total += ("<" + line + "[" + anchoridxstr + "] ");
                ss.clear();
                anchoridx++;
                file >> line;
            }

            if (line == "<br>")
            {
                break_new = true;
            }
            else if (line == "<p>")
            {
                break_new = true;
                break_para = true;
            }

            if (break_new == true)
            {
                break;
            }
            else if (file.eof())
                break;
            else { 
                total += (line + ' ');
            }
            
        }
        v_lines_.push_back(total);
        total = "";
    }
  

    file_name_ = new_file_name;
    ix_top_line_ = 0;
    return true;
}