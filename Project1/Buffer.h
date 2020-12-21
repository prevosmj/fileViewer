#ifndef _Buffer_h_
#define _Buffer_h_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

class Buffer
{
public:
    void display() const;
    const std::string& file_name() const { return file_name_; }
    const std::map<int, std::string>& anchors() const { return anchor_map_; }
    inline void move_to_next_page();
    inline void move_to_previous_page();
    bool open(const std::string& file_name);
    void set_window_height(int h) { window_height_ = h; }
    void set_window_width(int w) { window_width_ = w; }

private:
    std::vector<std::string> v_lines_;
    std::map<int, std::string> anchor_map_;
    std::string history;
    int ix_top_line_ = 0;
    std::string file_name_;
    int window_height_ = 0;
    int window_width_ = 0;
};

inline void Buffer::move_to_next_page()
{
    ix_top_line_ += window_height_;
    if (ix_top_line_ >= v_lines_.size())
        ix_top_line_ -= window_height_;
}

inline void Buffer::move_to_previous_page()
{
    ix_top_line_ -= window_height_;
    if (ix_top_line_ < 0)
        ix_top_line_ = 0;
}


#endif //_Buffer_h_
