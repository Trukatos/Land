#pragma once
#include "list"

using namespace std;

class Landmass
{

    int land = 0, tree = 0, mountain = 0, building = 0;
    list<int> prev_line_indices;
    list<int> cur_line_indices;
public:
    struct border_coords {
        int x;
        int y;
    };
private:
    list<border_coords> vertical_border_pieces;
    list<border_coords> horizontal_border_pieces;
    /*
     * id is used to keep the border_color of the "oldest" landmass (the one with the lowest id)
     * in order to keep a landmass bordered in one color
     */

public:

    int get_land() {
        return land;
    }

    void inc_land() {
        land++;
    }

    int get_tree() {
        return tree;
    }

    void inc_tree() {
        tree++;
    }

    int get_mountain() {
        return mountain;
    }

    void inc_mountain() {
        mountain++;
    }

    int get_building() {
        return building;
    }

    void inc_building() {
        building++;
    }

    void add_cur_line_index(int i) {
        cur_line_indices.push_back(i);
    }

    void add_vertical_border_piece(int x, int y) {
        border_coords bc;
        bc.x=x;
        bc.y=y;
        vertical_border_pieces.push_back(bc);
    }

    list<border_coords> get_vertical_border_pieces() {
        return vertical_border_pieces;
    }

    void add_horizontal_border_piece(int x, int y) {
        border_coords bc;
        bc.x=x;
        bc.y=y;
        horizontal_border_pieces.push_back(bc);
    }

    list<border_coords> get_horizontal_border_pieces() {
        return horizontal_border_pieces;
    }

    list<int>& get_prev_line_indices() {
        return prev_line_indices;
    }

    list<int>& get_cur_line_indices() {
        return cur_line_indices;
    }

    bool prev_line_indices_contains(int val1, int val2, int val3) {
        for (list<int>::iterator it = prev_line_indices.begin(); it != prev_line_indices.end(); it++)
        {
            if ((*it == val1) | (*it == val2) | (*it == val3))
                return true;
        }
        return false;
    }

    void merge_values(Landmass lm) {
        cur_line_indices.splice(cur_line_indices.end(), lm.get_cur_line_indices());
        cur_line_indices.sort();
        prev_line_indices.splice(prev_line_indices.end(), lm.get_prev_line_indices());
        prev_line_indices.sort();
        vertical_border_pieces.splice(vertical_border_pieces.end(), lm.get_vertical_border_pieces());
        horizontal_border_pieces.splice(horizontal_border_pieces.end(), lm.get_horizontal_border_pieces());
        land += lm.get_land();
        tree += lm.get_tree();
        mountain += lm.get_mountain();
        building += lm.get_building();
    }

    void update_indices() {
        prev_line_indices.swap(cur_line_indices);
        cur_line_indices.clear();
    }
};

